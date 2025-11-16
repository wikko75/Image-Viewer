#version 400 core

in vec4 vertexColor;
in vec2 tex_coors;

out vec4 FragColor;  

uniform sampler2D texture_sampler;
void main()
{
    FragColor = texture(texture_sampler, tex_coors);
} 
