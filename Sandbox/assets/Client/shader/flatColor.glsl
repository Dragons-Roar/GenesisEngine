#type vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_viewProjectionMatrix;
uniform mat4 u_transformMatrix;

void main() {
	gl_Position = u_viewProjectionMatrix * u_transformMatrix * vec4(a_pos, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_color;

uniform vec4 u_color;

void main() {
	o_color = u_color;
}
