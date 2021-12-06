#ifndef VEC3_H 
#define VEC3_H 
 
#include <iostream> 

#include "Utility.h"
 
class Vec3 { 
public:
    float e[3]; 

public: 
    Vec3() {} 
 
    Vec3(float e0, float e1, float e2) { 
        e[0] = e0; 
        e[1] = e1; 
        e[2] = e2; 
    } 
 
    inline float x() const { return e[0]; } 
 
    inline float y() const { return e[1]; } 
 
    inline float z() const { return e[2]; } 
 
    inline float r() const { return e[0]; } 
 
    inline float g() const { return e[1]; } 
 
    inline float b() const { return e[2]; } 
 
    inline const Vec3 &operator+() const { return *this; } 
 
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); } 
 
    inline float operator[](int i) const { return e[i]; } 
 
    inline float &operator[](int i) { return e[i]; } 
 
    inline Vec3 &operator+=(const Vec3 &v2); 
 
    inline Vec3 &operator-=(const Vec3 &v2); 
 
    inline Vec3 &operator*=(const Vec3 &v2); 
 
    inline Vec3 &operator/=(const Vec3 &v2); 
 
    inline Vec3 &operator*=(const float t); 
 
    inline Vec3 &operator/=(const float t); 
 
    inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); } 
 
    inline float squaredLength() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; } 
 
    inline void makeUnitVector(); 

    inline static Vec3 Random() { return Vec3(RandomDouble(), RandomDouble(), RandomDouble()); }

    inline static Vec3 Random(double min, double max) { return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max)); }
  
    Vec3 RandomInUnitSphere();
    
    Vec3 RandomUnitVector();
    
    // Alternative diffuse formulation
    // The idea is to have a uniform scatter direction for all angles away from the hit point
    // No dependence on the normal's angle
    Vec3 RandomInHemisphere(const Vec3& normal);

    bool NearZero() const {
        // Return true if the vector is close to 0 in all dimensions
        const double s = 1e-8;
        
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }
};
 
inline std::istream &operator>>(std::istream &is, Vec3 &t) { 
    is >> t.e[0] >> t.e[1] >> t.e[2]; 
    return is; 
} 
 
inline std::ostream &operator<<(std::ostream &os, const Vec3 &t) { 
    os << t.e[0] << " " << t.e[1] << " " << t.e[2]; 
    return os; 
}

inline void Vec3::makeUnitVector() { 
    float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); 
    e[0] *= k; 
    e[1] *= k; 
    e[2] *= k; 
} 
 
inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) { 
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]); 
} 
 
inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) { 
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]); 
} 
 
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) { 
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]); 
} 
 
inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) { 
    return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]); 
} 
 
inline Vec3 operator*(float t, const Vec3 &v) { 
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]); 
} 
 
inline Vec3 operator/(Vec3 v, float t) { 
    return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t); 
} 
 
inline Vec3 operator*(const Vec3 &v, float t) { 
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]); 
} 
 
inline Vec3 &Vec3::operator+=(const Vec3 &v) { 
    e[0] += v.e[0]; 
    e[1] += v.e[1]; 
    e[2] += v.e[2]; 
    return *this; 
} 
 
inline Vec3 &Vec3::operator*=(const Vec3 &v) { 
    e[0] *= v.e[0]; 
    e[1] *= v.e[1]; 
    e[2] *= v.e[2]; 
    return *this; 
} 
 
inline Vec3 &Vec3::operator/=(const Vec3 &v) { 
    e[0] /= v.e[0]; 
    e[1] /= v.e[1]; 
    e[2] /= v.e[2]; 
    return *this; 
} 
 
inline Vec3 &Vec3::operator-=(const Vec3 &v) { 
    e[0] -= v.e[0]; 
    e[1] -= v.e[1]; 
    e[2] -= v.e[2]; 
    return *this; 
} 
 
inline Vec3 &Vec3::operator*=(const float t) { 
    e[0] *= t; 
    e[1] *= t; 
    e[2] *= t; 
    return *this; 
} 
 
inline Vec3 &Vec3::operator/=(const float t) {
    float k = 1.0f / t; 
 
    e[0] *= k; 
    e[1] *= k; 
    e[2] *= k; 
    return *this; 
} 
 
inline Vec3 unitVector(Vec3 v) { 
    return v / v.length(); 
} 
 
inline float dot(const Vec3 &v1, const Vec3 &v2) { 
    return v1.e[0] * v2.e[0] 
           + v1.e[1] * v2.e[1] 
           + v1.e[2] * v2.e[2]; 
} 
 
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) { 
    return Vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1], 
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2], 
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]); 
} 
 
inline Vec3 reflect(const Vec3& v, const Vec3& n) { 
    return v - 2 * dot(v, n) * n; 
} 
 
inline float schlick(float cosine, float refractionIndex) { 
    float r0 = (1 - refractionIndex) / (1 + refractionIndex); 
    r0 = r0 * r0; 
    return r0 + (1 - r0) * pow((1 - cosine), 5); 
} 

Vec3 RandomInUnitSphere() {
    while (true) {
        Vec3 p = Vec3::Random(-1,1);
        if (p.squaredLength() >= 1) continue;
        
        return p;
    }
}
 
Vec3 RandomUnitVector() {
    return unitVector(RandomInUnitSphere());
}

Vec3 RandomInHemisphere(const Vec3& normal) {
    Vec3 inUnitSphere = RandomInUnitSphere();

    // Testing if inUnitSphere is in the same hemisphere as the normal
    if (dot(inUnitSphere, normal) > 0.0) {
        return inUnitSphere;
    }    
    else {
        return -inUnitSphere;
    }
}

Vec3 Reflect(const Vec3& vec, const Vec3& normal) {
    return vec - 2*dot(vec, normal)*normal;
}

// Using a modified version of the Snell-Descartes Law
Vec3 Refract(const Vec3& uv, const Vec3& normal, double etaDividedByEtaPrime) {
    double cosTheta = fmin(dot(-uv, normal), 1.0);
    Vec3 refractPerp =  etaDividedByEtaPrime * (uv + cosTheta*normal);
    Vec3 refractParallel = -sqrt(fabs(1.0 - refractPerp.squaredLength())) * normal;
    return refractPerp + refractParallel;
}

Vec3 RandomInUnitDisk() {
    while (true) {
        Vec3 p = Vec3(RandomDouble(-1, 1), RandomDouble(-1, 1), 0);
        if (p.squaredLength() >= 1) continue;

        return p;
    }
}

#endif