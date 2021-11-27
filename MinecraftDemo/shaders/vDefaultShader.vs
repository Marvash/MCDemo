#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords1;
layout (location = 2) in vec2 aTexCoords2;
layout (location = 3) in vec3 aTexColor1;
layout (location = 4) in vec3 aTexColor2;

out vec2 texCoords1;
out vec2 texCoords2;
out vec3 texColor1;
out vec3 texColor2;

uniform mat4 mvp;

void main()
{
    texCoords1 = aTexCoords1;
    texCoords2 = aTexCoords2;
    texColor1 = aTexColor1;
    texColor2 = aTexColor2;
    gl_Position = mvp * vec4(aPos, 1.0);
}