#ifndef COLOUR_HPP
#define COLOUR_HPP

#include <algorithm>
#include <ostream>

class Colour
{
private:
    double colour[3];

    int ToByte(double value) const
    {
        if (value < 0.0) value = 0.0;
        if (value > 1.0) value = 1.0;
        return static_cast<int>(255.999 * value);
    }

public:
    Colour() : colour{0, 0, 0} {};
    Colour(double r, double g, double b) : colour{r, g, b} {};

    double r() const { return colour[0]; }
    double g() const { return colour[1]; }
    double b() const { return colour[2]; }

    void WriteColour(std::ostream &out)
    {
        out << ToByte(colour[0]) << " " << ToByte(colour[1]) << " " << ToByte(colour[2]) << "\n";
    }

    friend std::ostream &operator<<(std::ostream &os, const Colour &c)
    {
        os << "Colour(" << c.colour[0] << ", " << c.colour[1] << ", " << c.colour[2] << ")";
        return os;
    }

    Colour operator+(const Colour &c) const
    {
        return Colour(
            colour[0] + c.colour[0],
            colour[1] + c.colour[1],
            colour[2] + c.colour[2]);
    }

    Colour operator+=(const Colour &c)
    {
        colour[0] += c.colour[0];
        colour[1] += c.colour[1];
        colour[2] += c.colour[2];

        return *this;
    }

    Colour operator-(const Colour &c) const
    {
        return Colour(
            colour[0] - c.colour[0],
            colour[1] - c.colour[1],
            colour[2] - c.colour[2]);
    }

    Colour operator-=(const Colour &c)
    {
        colour[0] -= c.colour[0];
        colour[1] -= c.colour[1];
        colour[2] -= c.colour[2];

        return *this;
    }

    Colour operator*(const Colour &c) const
    {
        double r = colour[0] * c.colour[0];
        double g = colour[1] * c.colour[1];
        double b = colour[2] * c.colour[2];

        return Colour(r, g, b);
    }

    Colour operator*(const double t) const
    {
        return Colour(
            colour[0] * t,
            colour[1] * t,
            colour[2] * t);
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
    const Colour WHITE(1, 1, 1);
    const Colour RED(1, 0, 0);
    const Colour GREEN(0, 1, 0);
    const Colour BLUE(0, 0, 1);
    const Colour YELLOW(1, 1, 0);
    const Colour CYAN(0, 1, 1);
    const Colour MAGENTA(1, 0, 1);
}

#endif
