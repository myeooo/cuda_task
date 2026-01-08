
#version 330 core

in vec2 vLocalPos;
out vec4 FragColor;

uniform vec3 u_Color;

void main()
{
    float dist = length(vLocalPos); 
    if (dist > 1.0)
        discard;

    FragColor = vec4(u_Color, 1.0);
}
