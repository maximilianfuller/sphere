#version 330 core

out vec4 fragColor;

uniform vec4 color;
uniform sampler2D data;

in vec2 texc;

void main()
{
    fragColor = texture(data, texc);
}
