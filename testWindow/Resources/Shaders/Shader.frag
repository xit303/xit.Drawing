#version 330 core

// Uniform variables (input from the application)
uniform vec4 iCornerRadius;     // Radius of the corners (x: top-left, y: top-right, z: bottom-right, w: bottom-left)
uniform vec4 iBorderThickness;  // Thickness of the border (x: left, y: bottom, z: right, w: top)
uniform vec2 iLocation;         // Location of the rectangle
uniform vec3 iRotation;         // Rotation of the rectangle
uniform vec2 iSize;             // Size of the rectangle
uniform vec2 iResolution;       // Resolution of the screen
uniform float iTime;            // Time in seconds
uniform float iIsTexture;       // Flag to indicate if a texture is used (0: no, 1: yes)
uniform float iTextureChannels; // Number of channels in the texture

uniform sampler2D text;         // Texture sampler

// Input from the vertex shader
in vec4 BackgroundColor;        // Background color of the rectangle
in vec4 BorderColor;            // Border color of the rectangle
in vec2 TexCoord;               // Texture coordinates

// Output color
out vec4 fragColor;             // Final fragment color

// Function declarations
vec4 borderedRectangle(void);   // Function to draw a bordered rectangle

// Global variables
vec2 halfSize;                  // Half of the size of the rectangle
vec2 center;                    // Center of the rectangle
float x, y;                     // Fragment coordinates relative to the rectangle

void main(void)
{
    vec2 st = gl_FragCoord.xy / iResolution; // Normalized screen coordinates

    // Calculate half the size of the rectangle
    halfSize = (iSize * 0.5);

    // Calculate the center of the rectangle
    center = halfSize + iLocation;

    // Adjust the center for OpenGL's coordinate system (flip the y-axis)
    center = vec2(center.x, iResolution.y - center.y);

    // Calculate the fragment's x-coordinate relative to the rectangle's location
    x = gl_FragCoord.x - iLocation.x;

    // Calculate the fragment's y-coordinate relative to the rectangle's location, adjusted for OpenGL's coordinate system
    y = gl_FragCoord.y - (iResolution.y - iLocation.y - iSize.y);

    if (iIsTexture == 0)
    {
        // Rotate the fragment coordinates around the center of the rectangle
        // float angle = iRotation.x;
        // float s = sin(angle);
        // float c = cos(angle);
        // vec2 rotated = vec2(c * x - s * y, s * x + c * y);
        // x = rotated.x;
        // y = rotated.y;
        
        fragColor = borderedRectangle(); // Draw a bordered rectangle
    }
    else
    {
        // rotate the texture coordinates
        // float angle = iRotation.x;
        // float s = sin(angle);
        // float c = cos(angle);

        // // Center the texture coordinates around (0.5, 0.5) before rotation
        // vec2 centeredTexCoord = TexCoord - 0.5;
        // vec2 rotated = vec2(c * centeredTexCoord.x - s * centeredTexCoord.y, s * centeredTexCoord.x + c * centeredTexCoord.y);

        // // Move the texture coordinates back to their original position
        // TexCoord = rotated + 0.5;

        // // Clamp the texture coordinates to the range [0, 1]
        // TexCoord = clamp(TexCoord, 0.0, 1.0);

        // // Debug output: Output the texture coordinates as color
        // fragColor = vec4(TexCoord, 0.0, 1.0);
        // return;

        // Use texture
        if (iTextureChannels == 1)
        {
            fragColor = vec4(texture(text, TexCoord).r); // Use red channel for single-channel textures
        }
        else
        {
            fragColor = texture(text, TexCoord);        // Use the full texture
        }
    }
}

// Function to calculate the signed distance function (SDF) for a rounded box
float roundedBoxSDF(vec2 center, vec2 size, float radius)
{
    return length(max(abs(center) - size + radius, 0.0)) - radius;
}

// Function to get the radius for a specific corner
float getRadius(float x, float y)
{
    // x, y, z, w = topLeft, bottomLeft, topRight, bottomRight
    return x < halfSize.x
            ? (y > halfSize.y ? iCornerRadius.x : iCornerRadius.w)
            : (y > halfSize.y ? iCornerRadius.y : iCornerRadius.z);
} 

// Function to get the border thickness for a specific side
float getBorderThickness(float x, float y, float radius)
{
    return x < max(radius, iBorderThickness.x)
        ? iBorderThickness.x
        : ((iSize.x - x) < max(radius, iBorderThickness.z)
            ? iBorderThickness.z
            : (y<max(radius, iBorderThickness.w)
                ? iBorderThickness.w
                : ((iSize.y - y) < max(radius, iBorderThickness.y)
                    ? iBorderThickness.y
                    : 0.0)));
}
    
// Function to draw a bordered rectangle
vec4 borderedRectangle(void)
{
    vec4 fromColor;
    vec4 toColor;

    float radius = getRadius(x, y);
    float distance = roundedBoxSDF(gl_FragCoord.xy - center, halfSize, radius);
    float borderThickness = getBorderThickness(x, y, radius);

    float minBlend = 0.0, maxBlend = 1.0;

    if (borderThickness > 0.0)
    {
        // have to blend depending on the distance
        fromColor = BorderColor;
        
        if (distance < 0.0)
        {
            // from inside to border
            toColor = BackgroundColor;
            distance = abs(distance);
        }
        else
        {
            // from border to outside
            toColor = vec4(BorderColor.rgb, 0.0);
            minBlend = -1.0;
        }

        distance -= (borderThickness * 0.5);
    }
    else
    {
        // solid color -> blend to 0 alpha
        fromColor = BackgroundColor;
        toColor = vec4(BackgroundColor.rgb, 0.0);
    }

    return mix(fromColor, toColor, smoothstep(minBlend, maxBlend, distance));
}

//---------------------------------------------------------
// draw ring at pos 
//---------------------------------------------------------
// Function to draw a halo ring
float haloRing(vec2 uv, vec2 pos, float radius, float thick)
{
  return clamp(-(abs(length(uv-pos) - radius) * 100.0 / thick) + 0.9, 0.0, 1.0);
}
