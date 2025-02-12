#include <cstdio>
#include <random>
#include <cmath>

struct Coordinate {
public:
    int mass;
    int x;
    int y;
    float distanceFromCenter;
    float velocityX;
    float velocityY;
};


int main() {
    float minMass = 0.08;
    float maxMass = 300.0;
    float gravConst = 6.67430e-11;
    float centerMass = 3.7e6;
    int radiusOfGalaxy = 100000;
    Coordinate coordinates[100000];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-radiusOfGalaxy, radiusOfGalaxy);
    std::uniform_real_distribution<float> distrib2(minMass, maxMass);
    for (int i = 0; i < 100000; i++) {
        coordinates[i].x = distrib(gen);
        coordinates[i].y = distrib(gen);
        coordinates[i].mass = distrib2(gen);
        coordinates[i].distanceFromCenter = sqrt(pow(coordinates[i].x,2) + pow(coordinates[i].y,2));
        if (coordinates[i].x == 0 && coordinates[i].y == 0) {
            i--;
        }
        float theta = std::atan2(coordinates[i].y, coordinates[i].x);
        float velocity = std::sqrt((gravConst * centerMass) / coordinates[i].distanceFromCenter);
        coordinates[i].velocityX = -velocity * std::sin(theta);
        coordinates[i].velocityY = velocity * std::cos(theta);
    }
    return 0;
}