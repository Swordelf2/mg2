#version 330 core

layout (location = 0) in vec2 pos;

out vec4 position;

void main()
{
    position = vec4(pos.xy, 0.0, 1.0);
    gl_Position = position;
}