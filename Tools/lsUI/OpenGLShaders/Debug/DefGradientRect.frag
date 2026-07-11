#version 330 core

in  vec2 TexCoord;
in  vec4 VertColor;
out vec4 FragColor;

uniform float zLayer;       // zLayer used to determine frag depth
void main() {
    gl_FragDepth = zLayer;
    FragColor    = VertColor;
}
