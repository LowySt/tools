#pragma once

#if _DEBUG

LS_COMPILE_TIME_FILE_REL_PATH(__ls_ui_DefTextVertSrc, __FILE__, "Debug\\DefText.vert");
LS_COMPILE_TIME_FILE_REL_PATH(__ls_ui_DefTextFragSrc, __FILE__, "Debug\\DefText.frag");
LS_COMPILE_TIME_FILE_REL_PATH(__ls_ui_DefSDFTextFragSrc, __FILE__, "Debug\\DefSDFText.frag");

#else

const char *__ls_ui_DefTextVertSrc = R"LONGLONG(
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
)LONGLONG";


const char *__ls_ui_DefTextFragSrc = R"LONGLONG(
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
)LONGLONG";


const char *__ls_ui_DefSDFTextFragSrc = R"LONGLONG(
#version 330 core

    //#define SUPERSAMPLED_SUBPIXEL_AA
    //#define SUBPIXELAA
    //#define SUPERSAMPLING

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D tex;  // SDF font texture
    uniform uvec4 textColor;       // Premultiplied RGBA color
    uniform float smoothing;       // Smoothing factor for the SDF edge
    uniform float zLayer;          // zLayer used to determine frag depth

    const float gamma = 2.2;

    vec4 convertIntColToFloat(uvec4 inC) {
        vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
        result.rgba /= 255.0;
        return result;
    }

    void main() {
        // Convert color from integer to float and apply alpha
        vec4 fColor = convertIntColToFloat(textColor);

#ifdef SUPERSAMPLING

        //2X Supersampling
        vec2 offset = vec2(0.5) / textureSize(tex, 0);

        float sdfValues[4];
        sdfValues[0] = texture(tex, TexCoord + vec2(-offset.x, -offset.y)).r;
        sdfValues[1] = texture(tex, TexCoord + vec2( offset.x, -offset.y)).r;
        sdfValues[2] = texture(tex, TexCoord + vec2(-offset.x,  offset.y)).r;
        sdfValues[3] = texture(tex, TexCoord + vec2( offset.x,  offset.y)).r;

        // Compute the alpha value using a threshold (0.5 is the middle distance)
        float base  = 0.65;
        float alpha = 0.0;
        for (int i = 0; i < 4; ++i) {
        alpha += smoothstep(base - smoothing, base + smoothing, sdfValues[i]);
        }

        alpha /= 4.0; // Average the alphas

        // Output color with pre-multiplied alpha
        vec4 result = vec4(fColor.rgb * alpha, fColor.a * alpha);

#elif defined(SUBPIXELAA)

        vec2 redOff = vec2(-0.33, 0.0) / textureSize(tex, 0); // Left of Pixel
        vec2 greOff = vec2(  0.0, 0.0) / textureSize(tex, 0); // Center
        vec2 bluOff = vec2( 0.33, 0.0) / textureSize(tex, 0); // Right of Pixel

        // Sample the Texture at each subpixel offset and calc alpha
        float base = 0.65;
        float alphaRed = smoothstep(base - smoothing, base + smoothing, texture(tex, TexCoord + redOff).r);
        float alphaGre = smoothstep(base - smoothing, base + smoothing, texture(tex, TexCoord + greOff).r);
        float alphaBlu = smoothstep(base - smoothing, base + smoothing, texture(tex, TexCoord + bluOff).r);

        // Gamma-correct
        alphaRed = pow(alphaRed, 1.0 / gamma);
        alphaGre = pow(alphaGre, 1.0 / gamma);
         alphaBlu = pow(alphaBlu, 1.0 / gamma);

        // Blend to reduce noticeable fringing
        alphaRed = mix(alphaRed, alphaGre, 0.3);
        alphaBlu = mix(alphaBlu, alphaGre, 0.3);

        // Set each channel to its corresponding subpixel alpha intensity
        vec3 subpixelColor = vec3(fColor.r * alphaRed, fColor.g * alphaGre, fColor.b * alphaBlu);

        // Average alpha value for visibility control (not premultiplied alpha)
        float finalAlpha = (alphaRed + alphaGre + alphaBlu) / 3.0;

        vec4 result = vec4(subpixelColor, finalAlpha);

#elif defined(SUPERSAMPLED_SUBPIXEL_AA)

        //2X Supersampling
        vec2 offset = vec2(0.5) / textureSize(tex, 0);

        vec2 redOff = vec2(-0.33, 0.0) / textureSize(tex, 0); // Left of Pixel
        vec2 greOff = vec2(  0.0, 0.0) / textureSize(tex, 0); // Center
        vec2 bluOff = vec2( 0.33, 0.0) / textureSize(tex, 0); // Right of Pixel

        vec2 offsetFrags[4];
        offsetFrags[0] = TexCoord + vec2(-offset.x, -offset.y);
        offsetFrags[1] = TexCoord + vec2( offset.x, -offset.y);
        offsetFrags[2] = TexCoord + vec2(-offset.x,  offset.y);
        offsetFrags[3] = TexCoord + vec2( offset.x,  offset.y);

        float base = 0.65;
        float red;
        float green;
        float blue;
        vec3 subpix;
        float finalAlpha;
        for (int i = 0; i < 4; ++i) {
            red   = smoothstep(base - smoothing, base + smoothing, texture(tex, offsetFrags[i] + redOff).r);
            green = smoothstep(base - smoothing, base + smoothing, texture(tex, offsetFrags[i] + greOff).r);
            blue  = smoothstep(base - smoothing, base + smoothing, texture(tex, offsetFrags[i] + bluOff).r);

            red = pow(red, 1.0 / gamma);
            green = pow(green, 1.0 / gamma);
            blue = pow(blue, 1.0 / gamma);

            red = mix(red, green, 0.3);
            blue = mix(blue, green, 0.3);

            subpix += vec3(fColor.r * red, fColor.g * green, fColor.b * blue);

            // Average alpha value for visibility control (not premultiplied alpha)
            finalAlpha += (red + green + blue) / 3.0;
        }

        finalAlpha /= 4.0;
        subpix /= 4.0;

        vec4 result = vec4(subpix * finalAlpha, finalAlpha);

#else //NO FILTERS

        // Sample the SDF texture, values range from 0 to 1
        float sdfValue = texture(tex, TexCoord).r;
        float base  = 0.58;
        float alpha = smoothstep(base - smoothing, base + smoothing, sdfValue);

        // Output color with pre-multiplied alpha
        vec4 result = vec4(fColor.rgb * alpha, fColor.a * alpha);

#endif

        if(result.a < 0.01) { discard; }
        gl_FragDepth = zLayer;
        FragColor = result;
    }
)LONGLONG";

#endif
