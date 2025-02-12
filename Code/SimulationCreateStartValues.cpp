#include <cstdio>
#include <random>
#include <cmath>
#include <iostream>
#include <fstream>

struct Coordinate {
public:
    float mass;
    float radius;
    float degree;
    float velocityRadius;
    float velocity;
};


int main() {
    int entries = 100000;
    float minMass = 0.08;
    float maxMass = 300.0;
    float gravConst = 6.67430e-11;
    float centerMass = 3.7e6;
    int radiusOfGalaxy = 100000;
    Coordinate coordinates[entries];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib1(0, radiusOfGalaxy);
    std::uniform_real_distribution<float> distrib2(0, 2*M_PI);
    std::uniform_real_distribution<float> distrib3(minMass, maxMass);
    for (int i = 0; i < entries; i++) {
        coordinates[i].radius = distrib1(gen);
        coordinates[i].degree = distrib2(gen);
        coordinates[i].mass = distrib3(gen);
        if (coordinates[i].radius == 0){
            i--;
        }
        float velocity = std::sqrt((gravConst * centerMass) / coordinates[i].radius);
        coordinates[i].velocityRadius = 0;
        coordinates[i].velocityY = velocity * std::cos(coordinates[i].degree);
    }

    std::ofstream file("Startwerte.txt", std::ios::trunc);
    if (!file){
        std::cout << "Error creating file" << std::endl;
    }
    for (int i = 0; i < entries; i++) {
        file << coordinates[i].radius << "\t" << coordinates[i].degree << "\t" << coordinates[i].velocityX << "\t" << coordinates[i].velocityY << "t" << coordinates[i].mass <<"\n";
    }

    return 0;
}