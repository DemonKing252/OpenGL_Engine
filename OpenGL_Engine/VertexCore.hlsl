/*****************************
File: VertexCore.hlsl (Vertex Shader)
Author: Liam Blake
Created: 2020-02-12
Modified: 2020-03-12
*****************************/
#version 430 core
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 vertex_texture;
layout(location = 3) in vec3 vertex_normal;

out vec3 vs_color;
out vec2 vs_texture;
out vec3 vs_normal;
out vec3 fragPos;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	vs_normal = mat3(M) * vertex_normal;
	vs_texture = vertex_texture;
	vs_color = vertex_color;
	fragPos = (M * vec4(vertex_position, 1.0f)).xyz;

	// Convert 3D world space coordinates to 2D screen coordinates
	gl_Position = P * V * M * vec4(vertex_position, 1.0f);
}