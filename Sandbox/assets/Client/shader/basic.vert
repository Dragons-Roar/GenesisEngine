#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_uv;

uniform mat4 u_viewProjectionMatrix;
uniform mat4 u_transformMatrix;

out vec3 v_pos;
out vec2 v_uv;

void main() {
	v_pos = a_pos;
	v_uv = a_uv;
	gl_Position = u_viewProjectionMatrix * u_transformMatrix * vec4(a_pos, 1.0);
}
