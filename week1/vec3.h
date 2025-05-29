#include <iostream>
#include <cmath>
#include <stdexcept>
#ifndef Vec3_H
#define Vec3_H
using namespace std;


class Vec3 {
private:
    float r[3];

public:
    Vec3(float x = 0, float y = 0, float z = 0) {
        r[0] = x;
        r[1] = y;
        r[2] = z;
    }

    Vec3 operator+(const Vec3& other) const {
        return Vec3(r[0] + other.r[0], r[1] + other.r[1], r[2] + other.r[2]);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(r[0] - other.r[0], r[1] - other.r[1], r[2] - other.r[2]);
    }

    Vec3 operator*(float k) const {
        return Vec3(k * r[0], k * r[1], k * r[2]);
    }

    Vec3 operator/(float k) const {
        if (k != 0) {
            return Vec3(r[0] / k, r[1] / k, r[2] / k);
        }
        else {
            throw std::runtime_error("Division by zero");
        }
    }

    Vec3 operator-() const {
        return Vec3(-r[0], -r[1], -r[2]);
    }

    float& operator[](int index) {
        if (index < 0 || index >= 3) throw std::out_of_range("Index out of range");
        return r[index];
    }

    float operator[](int index) const {
        if (index < 0 || index >= 3) throw std::out_of_range("Index out of range");
        return r[index];
    }

    float length() const {
        return sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
    }

    Vec3 unit() const {
        float len = length();
        if (len != 0) {
            return *this / len;
        }
        else {
            throw std::runtime_error("Vector has zero length");
        }
    }

    float dot(const Vec3& other) const {
        return r[0] * other.r[0] + r[1] * other.r[1] + r[2] * other.r[2];
    }

    Vec3 cross(const Vec3& other) const {
        return Vec3((r[1] * other.r[2]) - (r[2] * other.r[1]),
                    (r[2] * other.r[0]) - (r[0] * other.r[2]),
                    (r[0] * other.r[1]) - (r[1] * other.r[0]));
    }

    Vec3 reflect(const Vec3& normal) const {
        Vec3 n = normal.unit();
        float k = 2 * dot(n);
        return *this - n * k;
    }

    Vec3 refract(const Vec3& normal, float refractive_index) const {
        Vec3 n = normal.unit();
        Vec3 I = (*this).unit();
        float cosI = -I.dot(n);
        float eta = 1.0f / refractive_index;
        float k = 1 - eta * eta * (1 - cosI * cosI);
        if (k < 0) {
            // Total internal reflection
            return reflect(normal);
        }
        else {
            return I * eta + n * (eta * cosI - sqrt(k));
        }
    }

    void print() const {
        cout << r[0] << " " << r[1] << " " << r[2] << endl;
    }
};
#endif
