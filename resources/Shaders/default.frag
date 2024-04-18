#version 330 core

in vec3 vertCol;
in vec2 vertTex;
in float fogFactor;

out vec4 FragColor;

uniform sampler2D tex0;
uniform vec3 skyColor;

void main()
{
  vec4 texColor = texture(tex0, vertTex);
  vec3 fogColor = mix(texColor.rgb, skyColor, fogFactor);
  FragColor = vec4(fogColor, texColor.a);
} 
