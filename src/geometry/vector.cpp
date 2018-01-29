#include "geometry/vector.hpp"

#include <cmath>
#include <iostream>

namespace geo {
    vector operator+(const vector& lhs, const vector& rhs) {
        return vector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    vector operator-(const vector& lhs, const vector& rhs) {
        return vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    vector operator*(const vector& lhs, double rhs) {
        return vector(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }

    vector operator/(const vector& lhs, double rhs) {
        return vector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
    }

    vector operator*(double lhs, const vector& rhs) {
        return rhs * lhs;
    }

    vector operator/(double lhs, const vector& rhs) {
        return rhs / lhs;
    }

    vector operator*(const vector& lhs, const vector& rhs) {
        return geo::vector(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
    }

    vector operator/(const vector& lhs, const vector& rhs) {
        return geo::vector(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
    }

    bool operator==(const vector& lhs, const vector& rhs) {
        return lhs.x == rhs.x &&
               lhs.y == rhs.y &&
               lhs.z == rhs.z &&
               lhs.w == rhs.w;
    }

    bool operator!=(const vector& lhs, const vector& rhs) {
        return !(lhs == rhs);
    }

    std::ostream& operator<<(std::ostream& os, const vector& vec) {
        os << '(' << vec.x << ", " 
                  << vec.y << ", " 
                  << vec.z << ')';
        return os;
    }

    double length(const vector& v) {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    vector normalize(const vector& v) {
        const double len = std::sqrt(length(v));
        return vector(v.x / len, v.y / len, v.z / len, v.w);
    }

    double dot(const vector& v1, const vector& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    vector cross(const vector& v1, const vector& v2) {
        return vector(v1.y * v2.z - v1.z * v2.y,
                      v1.z * v2.x - v1.x * v2.z,
                      v1.x * v2.y - v1.y * v2.x);
    }
}
