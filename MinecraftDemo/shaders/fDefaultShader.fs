#version 420 core

out vec4 FragColor;

uniform sampler2D texAtlas;

// Centroid is needed to not cause texture bleed with multisampling enabled
centroid in vec2 texCoords1;
centroid in vec2 texCoords2;
centroid in vec2 texCoords3;
in vec3 texColor1;
in vec3 texColor2;
in vec3 texColor3;

void main()
{
    vec3 color = vec3(0.956, 0, 0.631);
    
    if(texCoords1.x >= 0.0) {
        if(texture(texAtlas, texCoords1).a < 0.1)
            discard;
        color = texColor1 * texture(texAtlas, texCoords1).rgb;
    }
    
    if (texCoords2.x >= 0.0) {
        vec4 tmpColor = texture(texAtlas, texCoords2);
        if(tmpColor.a > 0.0 && (tmpColor.r > 0.0 || tmpColor.g > 0.0 || tmpColor.b > 0.0)) {
            color = texColor2 * tmpColor.rgb;
        }
    }

    if (texCoords3.x >= 0.0) {
        vec4 tmpColor = texture(texAtlas, texCoords3);
        if(tmpColor.a > 0.0 && (tmpColor.r > 0.0 || tmpColor.g > 0.0 || tmpColor.b > 0.0)) {
            color = texColor3 * tmpColor.rgb;
        }
    }
    FragColor = vec4(color, 1.0);
}