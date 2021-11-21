#version 420 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D texAtlas;

void main()
{
    vec3 color = texture(texAtlas, texCoords).rgb;
    FragColor = vec4(color, 1.0);
}