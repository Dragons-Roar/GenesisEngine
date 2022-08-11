#version 330 core

layout(location = 0) out vec4 o_color;
in vec3 v_pos;
in vec2 v_uv;

void main() {
	o_color = vec4(0.f, v_uv, 1.0f);
}
