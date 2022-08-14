#type vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec4 a_color;

uniform mat4 u_viewProjectionMatrix;

out vec2 v_uv;
out vec4 v_color;

void main() {
	v_uv = a_uv;
	v_color = a_color;
	gl_Position = u_viewProjectionMatrix * vec4(a_pos, 1.f);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_color;

in vec2 v_uv;
in vec4 v_color;

uniform sampler2D u_texture;
uniform vec2 u_tiling;

void main() {
	o_color = texture(u_texture, v_uv * u_tiling) * v_color;
}
