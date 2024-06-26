#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in int aVertexTexCoordsIndex;
layout (location = 2) in int aVertexTexColorIndex;
layout (location = 3) in int aVertexSecondaryTexCoordsIndex;

centroid out vec2 texCoords1;
centroid out vec2 texCoords2;
centroid out vec2 texCoords3;
out vec3 texColor1;
out vec3 texColor2;
out vec3 texColor3;
centroid out vec2 secondaryTexCoords;

uniform mat4 mvp;
uniform samplerBuffer vertexesTexData;
uniform samplerBuffer vertexesColorData;
uniform samplerBuffer vertexesSecondaryTexData;

void populateTexData();

void main()
{
    populateTexData();

    gl_Position = mvp * vec4(aPos, 1.0);
}

void populateTexData() {
    if(aVertexTexCoordsIndex >= 0) {
        texCoords1.x = texelFetch(vertexesTexData, aVertexTexCoordsIndex).r;
        texCoords2.x = texelFetch(vertexesTexData, aVertexTexCoordsIndex + 1).r;
        texCoords3.x = texelFetch(vertexesTexData, aVertexTexCoordsIndex + 2).r;
        texCoords1.y = texelFetch(vertexesTexData, aVertexTexCoordsIndex + 3).r;
        texCoords2.y = texelFetch(vertexesTexData, aVertexTexCoordsIndex + 4).r;
        texCoords3.y = texelFetch(vertexesTexData, aVertexTexCoordsIndex + 5).r;
    } else {
        texCoords1.x = -1.0;
        texCoords2.x = -1.0;
        texCoords3.x = -1.0;
        texCoords1.y = -1.0;
        texCoords2.y = -1.0;
        texCoords3.y = -1.0;
    }
    if(aVertexTexColorIndex >= 0) {
        texColor1.r = texelFetch(vertexesColorData, aVertexTexColorIndex).r;
        texColor1.g = texelFetch(vertexesColorData, aVertexTexColorIndex + 1).r;
        texColor1.b = texelFetch(vertexesColorData, aVertexTexColorIndex + 2).r;
        texColor2.r = texelFetch(vertexesColorData, aVertexTexColorIndex + 3).r;
        texColor2.g = texelFetch(vertexesColorData, aVertexTexColorIndex + 4).r;
        texColor2.b = texelFetch(vertexesColorData, aVertexTexColorIndex + 5).r;
        texColor3.r = texelFetch(vertexesColorData, aVertexTexColorIndex + 6).r;
        texColor3.g = texelFetch(vertexesColorData, aVertexTexColorIndex + 7).r;
        texColor3.b = texelFetch(vertexesColorData, aVertexTexColorIndex + 8).r;
    } else {
        texColor1.r = -1.0;
        texColor1.g = -1.0;
        texColor1.b = -1.0;
        texColor2.r = -1.0;
        texColor2.g = -1.0;
        texColor2.b = -1.0;
        texColor3.r = -1.0;
        texColor3.g = -1.0;
        texColor3.b = -1.0;
    }
    if(aVertexSecondaryTexCoordsIndex >= 0) {
        secondaryTexCoords.x = texelFetch(vertexesSecondaryTexData, aVertexSecondaryTexCoordsIndex).r;
        secondaryTexCoords.y = texelFetch(vertexesSecondaryTexData, aVertexSecondaryTexCoordsIndex + 1).r;
    } else {
        secondaryTexCoords.x = -1.0;
        secondaryTexCoords.y = -1.0;
    }
}