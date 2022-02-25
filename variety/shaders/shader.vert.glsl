#version 330 core

layout (location = 0) in vec3 aPosition;

uniform vec2 uPos;

void main() 
{
    gl_Position = vec4(aPosition, 1.0) + vec4(uPos, 0.0, 0.0);
}