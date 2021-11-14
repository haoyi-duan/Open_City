#version 330 core
layout (location = 0) in vec3 picPos;
layout (location = 1) in vec2 picTexCoords;

out vec2 texCoords;

void main()
{
    texCoords = vec2(picTexCoords.x, 1 - picTexCoords.y);
    gl_Position = vec4(picPos, 1.0);
}