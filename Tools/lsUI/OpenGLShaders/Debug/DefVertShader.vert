#version 330 core

layout(location = 0) in vec2 inPosition;      // Vertex position
layout(location = 1) in vec2 inTexCoord;      // Texture coordinates

out vec2 TexCoord;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(inPosition, 0.0, 1.0);  // Transform into clip space
    TexCoord = inTexCoord;  // Pass texture coordinates to fragment shader
}
