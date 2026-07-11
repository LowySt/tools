#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform uvec4 color;        // Premultiplied RGBA color
uniform float thickness;    // Thickness of the outline
uniform float zLayer;       // zLayer used to determine frag depth

vec4 convertIntColToFloat(uvec4 inC) {
    vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
    result.rgba /= 255.0;
    return result;
}

void main() {
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(TexCoord, center);
    float innerRadius = 0.5 - thickness;

    if (dist > 0.5 || dist < innerRadius) {
        discard;
    }

    vec4 converted = convertIntColToFloat(color);
    if(converted.a < 0.01) { discard; }

    gl_FragDepth = zLayer;
    FragColor = converted;
}
