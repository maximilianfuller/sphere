#version 330 core

in vec4 gl_FragCoord;
out vec4 fragColor;

uniform vec2 res;
uniform sampler2D tex;

void main()
{
    fragColor = texture(tex, gl_FragCoord.xy / res);
}
