#version 330 core

in vec3 vPosition;
in vec3 vNormal;

uniform vec3 uLightPos;

void main()
{
    vec3 ray     = normalize(uLightPos - vPosition);
    vec3 nNormal = normalize(vNormal);

    float lum = clamp(dot(ray, nNormal), .2, 1);
  
    gl_FragColor = lum * vec4(1.0, 0.0, 0.0, 1.0);
}