#version 420 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float exposure;

void main()
{
    vec3 hdrColor = texture(screenTexture, TexCoords).rgb;
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
	float gamma = 2.2;
    FragColor.rgb = pow(mapped, vec3(1.0/gamma));
} 