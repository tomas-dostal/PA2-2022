/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 16.06.2022
 */

#pragma once

class Pixel
{
public:
    // Stores the individual color components.
    int red, green, blue;

    // Initializes a Pixel with a default black color.
    Pixel() : red(0), green(0), blue(0) { }

    // Initializes a color Pixel with the specified RGB values.
    Pixel(int r, int g, int b) : red(r), green(g), blue(b) { }
};
