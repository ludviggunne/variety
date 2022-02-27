#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

out vec3 vPosition;
out vec3 vNormal;

uniform mat4 uView;
uniform mat4 uProj;

void main() 
{
    gl_Position = uProj * uView * vec4(aPosition, 1.0);

    vPosition = aPosition;
    vNormal = aNormal;
}