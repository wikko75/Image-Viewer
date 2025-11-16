#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 in_tex_coors;

out vec4 vertexColor; 
out vec2 tex_coors;
void main()
{
    gl_Position = vec4(aPos, 1.0); 
    tex_coors = in_tex_coors;
}
