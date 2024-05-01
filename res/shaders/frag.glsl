#version 330 core

in vec3 frag_normal;
out vec3 out_color;

void main()
{
	vec3 fn = normalize(frag_normal);
	out_color = abs(fn);
}
