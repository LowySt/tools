#pragma once

const char *__ls_ui_default_vert_shader_src = R"LONGLONG(
    #version 330 core

    layout(location = 0) in vec2 inPosition;      // Vertex position
    layout(location = 1) in vec2 inTexCoord;      // Texture coordinates

    out vec2 TexCoord;

    uniform mat4 transform;

    void main() {
        gl_Position = transform * vec4(inPosition, 0.0, 1.0);  // Transform into clip space
        TexCoord = inTexCoord;  // Pass texture coordinates to fragment shader
    }
    )LONGLONG";


const char *__ls_ui_default_rect_frag_shader_src = R"LONGLONG(
    #version 330 core

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform uvec4 color;        // Premultiplied RGBA color
    uniform float zLayer;       // zLayer used to determine frag depth

    vec4 convertIntColToFloat(uvec4 inC) {
        vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
        result.rgba /= 255.0;
        return result;
    }

    void main() {
        vec4 converted = convertIntColToFloat(color);
        if(converted.a < 0.01) { discard; }

        gl_FragDepth = zLayer;
        FragColor = converted;
    }
    )LONGLONG";

