#ifndef VEC3_H
#define VEC3_H

#include <math.h>

class Vec3 
{
    private:
        double e[3];

    public:
        Vec3() : e{0, 0, 0} {}
        Vec3(double x, double y, double z) : e{x, y, z} {}

        std::ostream& operator<<(std::ostream& os) const
        {
            os << "Vec3(" << e[0] << ", " << e[1] << ", " << e[2] << ")";
            return os;
        }

        Vec3 ScalarMultiply(double scalar) const {
            return Vec3(e[0] * scalar, e[1] * scalar, e[2] * scalar);
        }

        Vec3 operator*(double scalar) const
        {
            return ScalarMultiply(scalar);
        }

        friend Vec3 operator*(double scalar, const Vec3& v)
        {
           return v.ScalarMultiply(scalar);
        }

        Vec3 operator/(double scalar) const
        {
            return *this * (1/scalar);
        }

        Vec3 operator+(const Vec3& v) const
        {
            return Vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
        }

        Vec3& operator+=(const Vec3& v)
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
                
            return *this;
        }

        Vec3 operator-(const Vec3& v) const
        {
            return Vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
        }

        Vec3& operator-=(const Vec3& v)
        {
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            e[2] -= v.e[2];
                
            return *this;
        }

        double Dot(const Vec3& v) const
        {
            return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
        }

        double LengthSquared()
        {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        double Length()
        {
            return sqrt(LengthSquared());
        }

        Vec3 Cross(const Vec3& v) const
        {
            return Vec3(
                this->e[1] * v.e[2] - this->e[2] * v.e[2],
                this->e[2] * v.e[0] - this->e[0] * v.e[1],
                this->e[0] * v.e[1] - this->e[1] * v.e[0]
            );
        }

        Vec3 UnitVector()
        {
            return *this / this->Length();
        }
}

#endif