#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec3 aNorm;
layout (location = 3) in vec2 aTex;

out vec3 vertCol;
out vec3 vertNorm;
out vec2 vertTex;
out float fogFactor;

uniform mat4 model;
uniform mat4 cameraMatrix;
uniform vec3 cameraPosition;

const float density = 0.015f;
const float gradient = 3.f;

void main()
{
  float distance = length(cameraPosition - vec3(model * vec4(aPos, 1.f)));
  float fogCalculation = exp(-pow(distance * density, gradient));
  fogCalculation = 1.f - clamp(fogCalculation, 0.f, 1.f);

  vertCol = aCol;
  vertNorm = aNorm;
  vertTex = aTex;
  fogFactor = fogCalculation;
  gl_Position = cameraMatrix * model * vec4(aPos, 1.f);
}
