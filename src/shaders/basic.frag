#version 330 core

layout (location = 0) out vec4 colour;

uniform vec4 change_color;
uniform vec2 light_pos;

in DATA
{
	in vec4 pos;
	in vec4 colour;
} fs_in;

void main()
{
	float intensity = 1.0 / length(fs_in.pos.xy - light_pos);
	colour = fs_in.colour * intensity;
}