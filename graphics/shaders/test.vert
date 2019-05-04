#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 fragColor;
out vec2 fragTexCoord;

void main()
{
    fragColor = color;
    fragTexCoord = texCoord;
    gl_Position = vec4(pos.xy, 0.0, 1.0);
}