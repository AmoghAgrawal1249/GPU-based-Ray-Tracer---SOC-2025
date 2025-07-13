
#include <stdexcept>
#ifndef VEC3_H
#define VEC3_H
using namespace std;

class vec3 {
private:
    float x_coord;
    float y_coord;
    float z_coord;

public:
    vec3(float x = 0, float y = 0, float z = 0) {
        x_coord = x;
        y_coord = y;
        z_coord = z;
    }

    vec3 operator+(const vec3& other) const {
        return vec3(x_coord + other.x_coord, y_coord + other.y_coord, z_coord + other.z_coord);
    }

    vec3 operator-(const vec3& other) const {
        return vec3(x_coord - other.x_coord, y_coord - other.y_coord, z_coord - other.z_coord);
    }

    vec3 operator*(float scalar) const {
        return vec3(scalar * x_coord, scalar * y_coord, scalar * z_coord);
    }

    vec3 operator/(float scalar) const {
        if (scalar != 0) {
            return vec3(x_coord / scalar, y_coord / scalar, z_coord / scalar);
        }
        else {
            throw std::runtime_error("Division by zero");
        }
    }

    vec3 operator-() const {
        return vec3(-x_coord, -y_coord, -z_coord);
    }

    float& operator[](int index) {
        if (index == 0) return x_coord;
        if (index == 1) return y_coord;
        if (index == 2) return z_coord;
        throw std::out_of_range("Index out of range");
    }

    float operator[](int index) const {
        if (index == 0) return x_coord;
        if (index == 1) return y_coord;
        if (index == 2) return z_coord;
        throw std::out_of_range("Index out of range");
    }

    float getLength() const {
        return sqrt(x_coord * x_coord + y_coord * y_coord + z_coord * z_coord);
    }

    vec3 getUnitVector() const {
        float length = getLength();
        if (length != 0) {
            return *this / length;
        }
        else {
            throw std::runtime_error("Vector has zero length");
        }
    }

    float getDotProduct(const vec3& other) const {
        return x_coord * other.x_coord + y_coord * other.y_coord + z_coord * other.z_coord;
    }

    vec3 getCrossProduct(const vec3& other) const {
        return vec3((y_coord * other.z_coord) - (z_coord * other.y_coord),
                    (z_coord * other.x_coord) - (x_coord * other.z_coord),
                    (x_coord * other.y_coord) - (y_coord * other.x_coord));
    }

    vec3 getReflection(const vec3& normal) const {
        vec3 unit_normal = normal.getUnitVector();
        float dot_product = 2 * getDotProduct(unit_normal);
        return *this - unit_normal * dot_product;
    }

    vec3 getRefraction(const vec3& normal, float refractive_index) const {
        vec3 unit_normal = normal.getUnitVector();
        vec3 unit_incident = (*this).getUnitVector();
        float cos_incident = -unit_incident.getDotProduct(unit_normal);
        float eta = 1.0f / refractive_index;
        float discriminant = 1 - eta * eta * (1 - cos_incident * cos_incident);
        if (discriminant < 0) {
            return getReflection(normal);
        }
        else {
            return unit_incident * eta + unit_normal * (eta * cos_incident - sqrt(discriminant));
        }
    }

    void print() const {
        cout << x_coord << " " << y_coord << " " << z_coord << endl;
    }
};

using point3 = vec3;

// Allow float * vec3 multiplication
inline vec3 operator*(float t, const vec3& v) {
    return v * t;
}

#endif
