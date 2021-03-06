#include "app.h"
#include "settings.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <fstream>
#include <functional>

Application::Application() 
	: _program(nullptr), _vertexArray(nullptr),
	_running(false), _backgroundColor(Settings::BackgroundColor), _wireframe(false),
	_width(Settings::WindowInitWidth), _height(Settings::WindowInitHeight)
{
	assert(WindowInit());
	assert(GLInit());
	assert(ImguiInit());

	ResizeCallback(_window, _width, _height);
	strcpy(_equationBuffer, Settings::BuilderDefaultEquation);
}



Application::~Application()
{
	delete _vertexArray;
	delete _program;

	glfwTerminate();
}



void Application::Run()
{
	_running = true;

	while (_running) {

		glfwPollEvents();

		GLcall(glClearColor(
			_backgroundColor.r, 
			_backgroundColor.g, 
			_backgroundColor.b, 
			1.0f));
		GLcall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// New Imgui Frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Get mesh
		std::vector<gl::Vertex> const *verts = _meshBuilder.GetVertices();
		if (verts) {
			_vertexArray->VertexData(&(*verts)[0], verts->size());
		}

		// Uniforms
		_program->Use();
		_program->SetUniform("uView", _camera.GetProjection());
		_program->SetUniform("uLightPos", _camera.GetPosition());

		// Render graph
		_vertexArray->Draw(_wireframe ? GL_LINES : GL_TRIANGLES);

		// Imgui window
		ImguiWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(_window);

		// Input
		if (!ImGui::GetIO().WantCaptureMouse) {
			static bool mousePressed = false;

			if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

				double xpos, ypos;
				glfwGetCursorPos(_window, &xpos, &ypos);
				glm::vec2 mpos(
					static_cast<float>(xpos),
					static_cast<float>(ypos));

				auto action = (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ?
					Camera::Action::Pan : Camera::Action::Rotation;

				if (!mousePressed) {
					mousePressed = true;
					_camera.OnMousePress(mpos, true, action);
				}
				else {
					_camera.OnMousePress(mpos, false, action);
				}
			}
			else mousePressed = false;
		}

		if (glfwGetKey(_window, GLFW_KEY_C) == GLFW_PRESS) _camera.ResetCenter();

		if (glfwWindowShouldClose(_window)) _running = false;
	}
}



bool Application::WindowInit()
{
	// Init
	if(!glfwInit()) return false;

	glfwWindowHint(GLFW_SAMPLES, 8);
	if (!(_window = glfwCreateWindow(
		Settings::WindowInitWidth,
		Settings::WindowInitHeight,
		"3D grapher", NULL, NULL))) return false;

	// Context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);

	// Associate app with window for callbacks
	glfwSetWindowUserPointer(_window, this);

	// Callbacks
	glfwSetFramebufferSizeCallback(_window, ResizeCallback);
	glfwSetScrollCallback(_window, ScrollCallback);

	return true;
}



bool Application::GLInit()
{
	// Load addresses
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return false;

	// Global state
	GLcall(glEnable(GL_DEPTH_TEST));
	GLcall(glEnable(GL_MULTISAMPLE));

	// Shader program
	// Read shader source files
	std::ifstream vstream("shaders/shader.vert.glsl");
	if (!vstream) return false;

	std::ifstream fstream("shaders/shader.frag.glsl");
	if (!fstream) return false;

	std::stringstream vss, fss;
	std::string line;

	while (std::getline(vstream, line))
		vss << line << '\n';

	while (std::getline(fstream, line))
		fss << line << '\n';

	// Compile and link
	_program = new gl::Program;
	std::stringstream log;
	if (!_program->CompileAndLink(vss.str(), fss.str(), log)) return false;


	// Uniforms
	_program->Use();
	_program->SetUniform("uSurfaceColor",    Settings::SurfaceColor);
	_program->SetUniform("uLightColor",      Settings::LightColor);
	_program->SetUniform("uGraphColor",      Settings::GraphColor);
	_program->SetUniform("uAmbientColor",    Settings::AmbientColor);
	_program->SetUniform("uAmbientStrength", Settings::AmbientStrength);


	// Vertex array
	_vertexArray = new gl::VertexArray;


	// Viewport
	GLcall(glViewport(0, 0, Settings::WindowInitWidth, Settings::WindowInitHeight));

	return true;
}



bool Application::ImguiInit()
{
	// Init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsClassic();

	// Backends
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Style
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 6.0f);

	return true;
}



void Application::ImguiWindow()
{
	static bool parseFailed = false;
	ImGui::Begin("Controls");

	ImGui::DragFloat3("Min", _meshBuilder.min, 0.01f, -5.0f, -.5f, "%.1f", 1.0f);
	ImGui::DragFloat3("Max", _meshBuilder.max, 0.01f, .5f, 5.0f, "%.1f", 1.0f);
	ImGui::DragInt("Resolution", &_meshBuilder.resolution, 0.2f, 8, 256);
	ImGui::Spacing();
	ImGui::InputText("Equation", _equationBuffer, EQBUFSIZE);

	if (ImGui::Button("Generate mesh")) {
		parseFailed = !_meshBuilder.Compute(_equationBuffer);
	}

	if (parseFailed) {
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
		ImGui::Text("Failed to parse expression.");
		ImGui::PopStyleColor();
	}

	if (_meshBuilder.GetState() == MeshBuilder::State::Compute) {
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) _meshBuilder.Cancel();
		ImGui::ProgressBar(_meshBuilder.GetProgress(), { -1, 0 }, _meshBuilder.GetProgressString());
	}

	if (ImGui::CollapsingHeader("Advanced options")) {

		ImGui::Checkbox("Wireframe", &_wireframe);

		ImGui::Text("Colors");

		static glm::vec3 surfaceColor = Settings::SurfaceColor;
		if(ImGui::ColorEdit3("Surface", &surfaceColor[0]))
			_program->SetUniform("uSurfaceColor", surfaceColor);

		static glm::vec3 lightColor = Settings::LightColor;
		if (ImGui::ColorEdit3("Light", &lightColor[0]))
			_program->SetUniform("uLightColor", lightColor);

		static glm::vec3 ambientColor = Settings::AmbientColor;
		if (ImGui::ColorEdit3("Ambient", &ambientColor[0]))
			_program->SetUniform("uAmbientColor", ambientColor);

		ImGui::ColorEdit3("Background", &_backgroundColor[0]);
	}

	ImGui::End();
}



void Application::ResizeCallback(GLFWwindow *window, int width, int height)
{
	auto _this = (Application *)glfwGetWindowUserPointer(window);

	GLcall(glViewport(0, 0, width, height));
	_this->_width = width;
	_this->_height = height;

	_this->_program->SetUniform("uProj", glm::perspective(
		Settings::PerspectiveFOV,
		static_cast<float>(width) / static_cast<float>(height),
		0.01f, 100.0f));
}



void Application::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	auto _this = (Application *)glfwGetWindowUserPointer(window);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		yoffset *= 0.5;

	_this->_camera.OnScroll(yoffset);
}
