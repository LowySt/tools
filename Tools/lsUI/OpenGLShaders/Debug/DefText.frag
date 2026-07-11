#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D tex;   // Atlas font texture
uniform uvec4 textColor; // Premultiplied RGBA color
uniform float zLayer;    // zLayer used to determine frag depth

vec4 convertIntColToFloat(uvec4 inC) {
    vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
    result.rgba /= 255.0;
    return result;
}

void main() {
    vec4 texColor = texture(tex, TexCoord);
    vec4 converted = convertIntColToFloat(textColor);

    vec4 finalColor = texColor * converted;
    if(finalColor.a < 0.01) { discard; }

    gl_FragDepth = zLayer;
    FragColor = finalColor;
}
