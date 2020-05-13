#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;
out vec2 v_TexCoord; // varying variable

void main() {
	gl_Position = vec4(position.xy, 0, 1);
	v_TexCoord = texCoord;
}