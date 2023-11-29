#version 330 core

in vec3 position;
in vec3 normal;

uniform float scale;
uniform vec3 center;
uniform float aspect;

out vec3 frag_normal;

void main()
{
	vec3 pos = (position - center) * scale;
	pos.x = pos.x / aspect;
	pos.z = -pos.z;

	gl_Position = vec4(pos, 1.0);
	frag_normal = normalize(normal);
}
