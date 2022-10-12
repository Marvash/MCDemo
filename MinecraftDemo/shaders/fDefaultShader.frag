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
centroid in vec2 secondaryTexCoords;

void main()
{
    vec4 color = vec4(0.956, 0, 0.631, 1.0);
    /*
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
    if (secondaryTexCoords.x >= 0.0) {
        vec4 tmpColor = texture(texAtlas, secondaryTexCoords);
        if(tmpColor.a > 0.0 && (tmpColor.r > 0.0 || tmpColor.g > 0.0 || tmpColor.b > 0.0)) {
            color = tmpColor.rgb;
        }
    }
    */
    if(texCoords1.x >= 0.0) {
        if ((secondaryTexCoords.x < 0.0 || texture(texAtlas, secondaryTexCoords).a < 0.1) && texture(texAtlas, texCoords1).a < 0.1) {
            discard;
        }
        color.rgb = texColor1 * texture(texAtlas, texCoords1).rgb;
    }

    if (texCoords2.x >= 0.0) {
        vec4 tmpColor = texture(texAtlas, texCoords2);
        if(tmpColor.a > 0.0 && (tmpColor.r > 0.0 || tmpColor.g > 0.0 || tmpColor.b > 0.0)) {
            color.rgb = texColor2 * tmpColor.rgb;
        }
    }

    if (texCoords3.x >= 0.0) {
        vec4 tmpColor = texture(texAtlas, texCoords3);
        if(tmpColor.a > 0.0 && (tmpColor.r > 0.0 || tmpColor.g > 0.0 || tmpColor.b > 0.0)) {
            color.rgb = texColor3 * tmpColor.rgb;
        }
    }

    if (secondaryTexCoords.x >= 0.0) {
        if(texture(texAtlas, secondaryTexCoords).a >= 0.1) {
            vec4 tmpColor = texture(texAtlas, secondaryTexCoords);
            if(texture(texAtlas, texCoords1).a < 0.1) {
                tmpColor.rgb = vec3(0.0,0.0,0.0);
                color = tmpColor;
            } else {
                color.rgb = (color.rgb * tmpColor.r);
            }
        }
    }
    

    FragColor = color;
}