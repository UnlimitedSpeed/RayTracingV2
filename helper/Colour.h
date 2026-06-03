#ifndef COLOUR_HPP
#define COLOUR_HPP

#include <ostream>

class Colour
{
private:
    double colour[3];

    int ClampValue(int value) const
    {
        if (value > 255)
        {
            return 255;
        }
        else if (value < 0)
        {
            return 0;
        }

        return value;
    }

public:
    Colour() : colour{0, 0, 0} {};
    Colour(double r, double g, double b) : colour{r, g, b} {};

    double r() const { return colour[0]; }
    double g() const { return colour[1]; }
    double b() const { return colour[2]; }

    void WriteColour(std::ostream &out)
    {
        out << colour[0] << " " << colour[1] << " " << colour[2] << "\n";
    }

    Colour operator+(const Colour &c) const
    {
        return Colour(
            ClampValue(colour[0] + c.colour[0]),
            ClampValue(colour[1] + c.colour[1]),
            ClampValue(colour[2] + c.colour[2]));
    }

    Colour operator+=(const Colour &c)
    {
        colour[0] += c.colour[0];
        colour[1] += c.colour[1];
        colour[2] += c.colour[2];

        ClampValue(colour[0]);
        ClampValue(colour[1]);
        ClampValue(colour[2]);

        return *this;
    }

    Colour operator-(const Colour &c) const
    {
        return Colour(
            ClampValue(colour[0] - c.colour[0]),
            ClampValue(colour[1] - c.colour[1]),
            ClampValue(colour[2] - c.colour[2]));
    }

    Colour operator-=(const Colour &c)
    {
        colour[0] -= c.colour[0];
        colour[1] -= c.colour[1];
        colour[2] -= c.colour[2];

        ClampValue(colour[0]);
        ClampValue(colour[1]);
        ClampValue(colour[2]);

        return *this;
    }

    Colour operator*(const Colour &c) const
    {
        double r = ((colour[0] / 255) * (c.colour[0] / 255)) * 255;
        double g = ((colour[1] / 255) * (c.colour[1] / 255)) * 255;
        double b = ((colour[2] / 255) * (c.colour[2] / 255)) * 255;

        return Colour(
            ClampValue(r),
            ClampValue(g),
            ClampValue(b));
    }

    Colour operator*(const double t) const
    {
        return Colour(
            ClampValue(colour[0] * t),
            ClampValue(colour[1] * t),
            ClampValue(colour[2] * t));
    }

    friend Colour operator*(const double t, const Colour &c)
    {
        return c * t;
    }

    Colour operator/(const double t) const
    {
        return *this * (1 / t);
    }
};

// Common color constants
namespace Colours
{
    const Colour BLACK(0, 0, 0);
    const Colour WHITE(255, 255, 255);
    const Colour RED(255, 0, 0);
    const Colour GREEN(0, 255, 0);
    const Colour BLUE(0, 0, 255);
    const Colour YELLOW(255, 255, 0);
    const Colour CYAN(0, 255, 255);
    const Colour MAGENTA(255, 0, 255);
}

#endif