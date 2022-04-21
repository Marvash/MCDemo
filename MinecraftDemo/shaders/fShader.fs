#version 420 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

void main()
{
    vec3 color = vec3(0.956, 0, 0.631);
    FragColor = vec4(color, 1.0);
}