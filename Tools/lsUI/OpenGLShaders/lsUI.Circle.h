#pragma once

#if _DEBUG

LS_COMPILE_TIME_FILE_REL_PATH(__ls_ui_DefCircleFragSrc, __FILE__, "Debug\\DefCircle.frag");
LS_COMPILE_TIME_FILE_REL_PATH(__ls_uiDefCircleColorWheelFragSrc, __FILE__, "Debug\\DefCircleColorWheel.frag");

#else

const char *__ls_ui_DefCircleFragSrc = R"LONGLONG(
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
)LONGLONG";

const char *__ls_uiDefCircleColorWheelFragSrc = R"LONGLONG(
    #version 330 core

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform vec2 centerInScreenSpace;
    uniform float radiusInScreenSpace;

    uniform float brightness;
    uniform float zLayer;       // zLayer used to determine frag depth

    void main() {
        float dist_from_center = distance(gl_FragCoord.xy, centerInScreenSpace);
        if (dist_from_center > radiusInScreenSpace) {
            discard;
        }

        vec2 delta = gl_FragCoord.xy - centerInScreenSpace;
        float angle = atan(delta.y, delta.x); // Angle in Radians
        float hue = (angle + 3.14159265) / (2.0 * 3.14159265); // Normalize to [0, 1]
        float saturation = dist_from_center / radiusInScreenSpace;

        //Convert HSV to RGB
        float c = brightness * saturation;
        float x = c * (1.0 - abs(mod(hue * 6.0, 2.0) - 1.0));
        float m = brightness - c;
        
        vec3 color;
        if (hue < 1.0 / 6.0)      { color = vec3(c, x, 0.0); }
        else if (hue < 2.0 / 6.0) { color = vec3(x, c, 0.0); }
        else if (hue < 3.0 / 6.0) { color = vec3(0.0, c, x); }
        else if (hue < 4.0 / 6.0) { color = vec3(0.0, x, c); }
        else if (hue < 5.0 / 6.0) { color = vec3(x, 0.0, c); }
        else                      { color = vec3(c, 0.0, x); }
        color += vec3(m);

        gl_FragDepth = zLayer;
        FragColor = vec4(clamp(color, 0.0, 1.0), 1.0);
    }
)LONGLONG";

#endif
