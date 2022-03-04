#version 330 core

in vec3 vPosition;
in vec3 vNormal;

uniform vec3 uLightPos;
uniform vec3 uSurfaceColor;
uniform vec3 uLightColor;
uniform vec3 uAmbientColor;
uniform float uAmbientStrength;

void main()
{
    vec3 ray     = normalize(uLightPos - vPosition);
    vec3 nNormal = normalize(vNormal);

    float lum = abs(dot(ray, nNormal));
  
    gl_FragColor = clamp(lum * vec4(uLightColor, 1.0) * vec4(uSurfaceColor, 1.0)
        + uAmbientStrength * vec4(uAmbientColor, 1.0), 0, 1);
    //gl_FragColor *= abs(vPosition);
}