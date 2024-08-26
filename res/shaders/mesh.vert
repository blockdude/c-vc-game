#version 330 core

in vec3 position;
in vec3 normal;

uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 model_matrix;

out vec3 frag_normal;

void main()
{
	// Transform the position from object space (a.k.a model space) to clip
	// space. The range of clip space is [-1,1] in all 3 dimensions.
	vec4 pos = proj_matrix * view_matrix * model_matrix * vec4(position, 1.0);
	gl_Position = pos;

	// Transform the normal from object (or model) space to world space
	mat4 normal_matrix = transpose(inverse(model_matrix));
	vec3 new_normal = (normal_matrix * vec4(normal, 0)).xyz;
	frag_normal = normalize(new_normal);
}
