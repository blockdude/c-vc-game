#version 450 core

layout ( location = 0 ) in vec2 position;

uniform vec2 offset;
uniform float size;

void main()
{
	vec2 position_ = ( position + ( offset * 2 ) ) / size - 1.0 + ( 1.0 / size );
	gl_Position = vec4( position_, 0.0, 1.0 );
}
