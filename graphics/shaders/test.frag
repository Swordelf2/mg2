#version 330 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D my_sampler;

void main()
{
    color = texture(my_sampler, fragTexCoord);
}