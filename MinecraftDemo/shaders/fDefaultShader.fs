#version 420 core

out vec4 FragColor;

in vec2 texCoords1;
in vec2 texCoords2;
in vec3 texColor1;
in vec3 texColor2;

uniform sampler2D texAtlas;

void main()
{
    vec3 color = texColor1 * texture(texAtlas, texCoords1).rgb;
    if (texCoords2.x >= 0.0) {
        vec4 tmpColor = texture(texAtlas, texCoords2);
        if(tmpColor.a > 0.0 && (tmpColor.r > 0.0 || tmpColor.g > 0.0 || tmpColor.b > 0.0)) {
            color = texColor2 * tmpColor.rgb;
        }
    }
    FragColor = vec4(color, 1.0);
}