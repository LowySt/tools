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
