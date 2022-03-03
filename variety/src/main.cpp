#include "app.h"

int main() {
	Application *app = new Application;
	app->Run();
	delete app;
}