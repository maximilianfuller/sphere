#version 330 core

in vec4 gl_FragCoord;
out vec4 fragColor;

uniform sampler2D tex;

in vec2 texc;

void main()
{
    fragColor = texture(tex, texc);
}
