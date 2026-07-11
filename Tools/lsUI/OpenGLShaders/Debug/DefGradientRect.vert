#version 330 core

layout(location = 0) in vec2 inPosition;      // Vertex position
layout(location = 1) in vec2 inTexCoord;      // Texture coordinates
layout(location = 2) in float gradientFactor; // 0.0 is Black, 1.0 is White

out vec2 TexCoord;
out vec4 VertColor;
uniform mat4 transform;
uniform uvec4 color;        // Premultiplied RGBA color

vec4 convertIntColToFloat(uvec4 inC) {
    vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
    result.rgba /= 255.0;
    return result;
}

void main() {
    gl_Position = transform * vec4(inPosition, 0.0, 1.0);  // Transform into clip space
    TexCoord = inTexCoord;  // Pass texture coordinates to fragment shader

    vec4 gradientColor = vec4(gradientFactor, gradientFactor, gradientFactor, 1.0);
    vec4 convertedColor = convertIntColToFloat(color);
    if (convertedColor.a > 0.0) {
        gradientColor *= convertedColor;
    }
    VertColor = gradientColor;
}
