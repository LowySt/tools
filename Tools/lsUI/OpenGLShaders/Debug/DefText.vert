#version 330 core

layout(location = 0) in vec2 localPositions;   // Vertex position (0 to glyph pixel's Width/Height)
layout(location = 1) in vec2 inTexCoord;       // Texture coordinates
layout(location = 2) in vec2 yOffset;          // y0,y1 font pixel offsets

uniform vec2 viewportSize; // Screen pixel dimensions
uniform mat4 transform;

out vec2 TexCoord;

void main() {
    float scaledY1 = yOffset.y / viewportSize.y;

    vec2 realPos = localPositions / viewportSize;
    realPos.y   -= scaledY1;

    gl_Position = transform * vec4(realPos, 0.0, 1.0);  // Transform into clip space
    TexCoord    = inTexCoord;                           // Pass texture coordinates to fragment shader
}
