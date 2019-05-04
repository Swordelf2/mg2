#version 330 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D my_sampler;

void main()
{
    //color = vec4(fragTexCoord, 0.0, 1.0);
    color = texture(my_sampler, fragTexCoord);
}