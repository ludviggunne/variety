#version 330 core

in vec3 vPosition;
in vec3 vNormal;

uniform vec3 uLightPos;

void main()
{
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}