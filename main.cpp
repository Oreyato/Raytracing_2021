#include <iostream>
#include <fstream>

#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Material.h"

using namespace std;

HittableList RandomScene() {
    HittableList world;

    shared_ptr<Lambertian> groundMaterial = make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5));
    world.Add(make_shared<Sphere>(Vec3(0.0, -1000, 0.0), 1000.0, groundMaterial));

    for (int i = -11; i < 11; i++)
    {
        for (int j = -11; j < 11; j++)
        {
            double chooseMat = RandomDouble();
            Vec3 center(i + 0.9*RandomDouble(), 0.2, j + 0.9*RandomDouble());

            if ((center - Vec3(4.0, 0.2, 0.0)).length() > 0.9) {
                shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8) {
                    // Diffuse 
                    Vec3 albedo = Vec3::Random() * Vec3::Random();
                    sphereMaterial = make_shared<Lambertian>(albedo);
                    world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else if (chooseMat < 0.95) {
                    // Metal
                    Vec3 albedo = Vec3::Random(0.5, 1.0);
                    double fuzzyness = RandomDouble(0.0, 0.5);
                    sphereMaterial = make_shared<Metal>(albedo, fuzzyness);
                     world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else {
                    // Glass
                    sphereMaterial = make_shared<Dielectric>(1.5);
                    world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }
    
    shared_ptr<Dielectric> dielectricExampleMaterial = make_shared<Dielectric>(1.5);
    world.Add(make_shared<Sphere>(Vec3(0.0, 1.0, 0.0), 1.0, dielectricExampleMaterial));
    shared_ptr<Lambertian> lambertianExampleMaterial = make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1));
    world.Add(make_shared<Sphere>(Vec3(-4.0, 1.0, 0.0), 1.0, lambertianExampleMaterial));
    shared_ptr<Metal> metalExampleMaterial = make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0);
    world.Add(make_shared<Sphere>(Vec3(4.0, 1.0, 0.0), 1.0, metalExampleMaterial));

    return world;
}

Vec3 RayColor(const Ray& r, const Hittable& world, int depth) {
    HitRecord rec;

    // If we've exceed the ray bounce limit, no more light is gathered
    if (depth <= 0) {
        return Vec3(0,0,0);
    }
    
    if(world.Hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        Vec3 attenuation;

        if (rec.materialPtr->Scatter(r, rec, attenuation, scattered)) {
            return attenuation * RayColor(scattered, world, depth-1);
        }

        Vec3 target = rec.p + rec.normal + RandomInHemisphere(rec.normal);
        return 0.5 * RayColor(Ray(rec.p, target - rec.p), world, depth-1);
    }

    // Display the sky
    Vec3 unit_direction = unitVector(r.direction()); // -> unitVector : transformation en vecteur unitaire
    double t = 0.5*(unit_direction.y() + 1.0);

    return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}

int main(){
    // Init ================================================
    ofstream output;

    // Image
    const auto aspectRatio = 3.0 / 2.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 500;
    const int maxDepth = 50;

    // Vectors
    Vec3 lower_left_corner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);

    // Objects
    #pragma region PREVIOUS VERSION
    /*
    HittableList world;

    shared_ptr<Lambertian> materialGround = make_shared<Lambertian>(Vec3(0.8, 0.8, 0.0));
    shared_ptr<Lambertian> materialCenter = make_shared<Lambertian>(Vec3(0.7, 0.3, 0.3));
    shared_ptr<Dieletric> materialLeft = make_shared<Dieletric>(1.5);
    shared_ptr<Metal> materialRight = make_shared<Metal>(Vec3(0.8, 0.6, 0.2), 0.2);

    world.Add(make_shared<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.Add(make_shared<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5, materialCenter));
    world.Add(make_shared<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.Add(make_shared<Sphere>(Vec3(-1.0, 0.0, -1.0), -0.4, materialLeft));
    world.Add(make_shared<Sphere>(Vec3(1.0, 0.0, -1.0), 0.5, materialRight));
    */
    #pragma endregion
    #pragma region MORE RECENT VERSION
    
    double radius = cos(pi/4);
    HittableList world;

    shared_ptr<Lambertian> materialGround = make_shared<Lambertian>(Vec3(0.8, 0.8, 0.0));
    shared_ptr<Lambertian> materialCenter = make_shared<Lambertian>(Vec3(0.1, 0.2, 0.5));
    shared_ptr<Dielectric> materialLeft = make_shared<Dielectric>(1.5);
    shared_ptr<Metal> materialRight = make_shared<Metal>(Vec3(0.8, 0.6, 0.2), 0.0);

    world.Add(make_shared<Sphere>(Vec3( 0.0, -100.5, -1.0), 100.0, materialGround));
    world.Add(make_shared<Sphere>(Vec3( 0.0,    0.0, -1.0),   0.5, materialCenter));
    world.Add(make_shared<Sphere>(Vec3(-1.0,    0.0, -1.0),   0.5, materialLeft));
    world.Add(make_shared<Sphere>(Vec3(-1.0,    0.0, -1.0), -0.45, materialLeft));
    world.Add(make_shared<Sphere>(Vec3( 1.0,    0.0, -1.0),   0.5, materialRight));
    
    #pragma endregion

    // Too long to render
    // HittableList world = RandomScene();

    // Camera
    Vec3 lookFrom(13.0, 2.0, 3.0);
    Vec3 lookAt(0.0, 0.0, 0.0);
    Vec3 vup(0.0, 1.0, 0.0);
    // double distToFocus = (lookFrom - lookAt).length();
    double distToFocus = 10.0;
    //double aperture = 2.0;
    double aperture = 0.1;

    Camera cam(lookFrom, lookAt, vup, 20, aspectRatio, aperture, distToFocus);

    // =====================================================

    output.open("output.ppm");

    // Write the size of the file
    output << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    // Render ==============================================
    for (int column = imageHeight-1; column>= 0; --column) {
        // Progress bar
        std::cerr << "\rScanlines remaining: " << column << " " << std::flush;

        for (int row = 0; row < imageWidth; ++row) {
            Vec3 color(0, 0, 0);
            for(int s = 0; s < samplesPerPixel; s++) {
                float u = float(row + RandomDouble()) / float(imageWidth - 1);
                float v = float(column + RandomDouble()) / float(imageHeight - 1);
                Ray r = cam.GetRay(u, v);
                color += RayColor(r, world, maxDepth);
            }
            WriteColor(output, color, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
    // =====================================================

    output.close();

    return 0;
}