#ifndef MATERIAL_H
#define MATERIAL_H

#include "Utility.h"
#include "Hittable.h"

struct HitRecord;

class Material {
    public:
        virtual bool Scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
    public:
        Vec3 mAlbedo;
    
    public:
        Lambertian(const Vec3& albedo) : mAlbedo(albedo) {}

        virtual bool Scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override {
            Vec3 scatterDirection = rec.normal + RandomUnitVector();

            // Catch zero scatter direction vector
             if (scatterDirection.NearZero()) {
                scatterDirection = rec.normal;
             }

            scattered = Ray(rec.p, scatterDirection);
            attenuation = mAlbedo;
            
            return true;
        }
};

class Metal : public Material {
    public:
        Vec3 mAlbedo;
        double mFuzzyness;
    
    public:
        Metal(const Vec3 albedo, double fuzzyness) : mAlbedo(albedo), mFuzzyness(fuzzyness) {}

        virtual bool Scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override {
            Vec3 reflected = reflect(unitVector(rIn.direction()), rec.normal);
            scattered = Ray(rec.p, reflected + mFuzzyness*RandomInUnitSphere());
            //                                 ^ randomize the reflected direction by using a sphere and thus, choosing a new endpoint for the ray
            attenuation = mAlbedo;

            return (dot(scattered.direction(), rec.normal) > 0);
        }
};

class Dielectric : public Material {
    public:
        // Index of refraction
        double mIR;

    public:
        Dielectric(double iR) : mIR(iR) {}

        virtual bool Scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override {
            attenuation = Vec3(1.0, 1.0, 1.0);
            double refractionRatio = rec.frontFace ? (1.0 / mIR) : mIR;

            Vec3 unitDirection = unitVector(rIn.direction());

            double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
            double sinTheta = sqrt(1.0 - cosTheta*cosTheta);

            Vec3 direction;

            // Adding the "total internal reflection" 
            if (refractionRatio * sinTheta > 1.0 || Reflectance(cosTheta, refractionRatio) > RandomDouble()) {
                direction = Reflect(unitDirection, rec.normal);
            }
            else {
                direction = Refract(unitDirection, rec.normal, refractionRatio);
            }

            scattered = Ray(rec.p, direction);

            return true;
        }

        private:
            static double Reflectance(double cosTheta, double refIndex) {
                // Use Shlick's approximation for reflectance
                // R(Theta) becomes R0 when reflection coefficient for light incoming is parallel to the normal -> r0

                double r0 = (1 - refIndex) / (1 + refIndex);
                r0 = r0 * r0;

                return r0 + (1 - r0)*pow((1 - cosTheta), 5);
        }
};

#endif