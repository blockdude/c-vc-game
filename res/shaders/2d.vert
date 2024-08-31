#version 330 core

in vec3 position;
in vec3 color;

uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 model_matrix;

out vec3 frag_color;

void main()
{
	gl_Position = proj_matrix * view_matrix * model_matrix * vec4( position, 1.0f );
	frag_color = color;
}
