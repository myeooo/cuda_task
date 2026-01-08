
#version 330 core

layout (location = 0) in vec2 aPos;

uniform mat4 u_MVP;

out vec2 vLocalPos;

void main()
{
    vLocalPos = aPos;               // [-1, 1] space
    gl_Position = u_MVP * vec4(aPos, 0.0, 1.0);
}
