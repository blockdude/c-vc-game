#version 450 core
#define SIZE 128

layout ( location = 0 ) in vec2 position;
layout ( location = 9 ) uniform int state[ SIZE * SIZE ];
out int cstate;

void main()
{
	int i = gl_InstanceID;
	int x = i % SIZE;
	int y = ( i - x ) / SIZE;

	vec2 offset = vec2( x, y );
	vec2 position_ = ( position + ( offset * 2 ) ) / SIZE - 1.0 + ( 1.0 / SIZE );

	gl_Position = vec4( position_, 0.0, 1.0 );
	cstate = state[ gl_InstanceID ];
}
