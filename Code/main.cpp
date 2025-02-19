#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <valarray>
#include <omp.h>
using namespace std;

struct Coordinate {
    float mass;
    float radius;
    float degree;
    float velocityRadius;
    float velocityDegree;
    float forceRadius = 0;
    float forceDegree = 0;
};

float gravitationalConstant = 6.67430e-11;

Coordinate Stars[100000]; // Richtige Deklaration anstelle von #define

int importData() {
    ifstream file("/home/niccollingro/Documents/ITG 1/ITG-Galaxiebewegung/Data/Startwerte.txt");
    if (!file.is_open()) {
        cerr << "Fehler beim Öffnen der Datei!" << endl;
        return 1;
    }

    string line;
    size_t count = 0;

    while (getline(file, line) && count < 100000) {
        stringstream ss(line);
        if (ss >> Stars[count].mass >> Stars[count].radius >> Stars[count].degree >> Stars[count].velocityRadius >> Stars[count].velocityDegree) {
            ++count;
        } else {
            cerr << "Warnung: Zeile mit falschem Format übersprungen." << endl;
        }
    }

    file.close();

    return 0;
}

void fromForceCalcPos(float timePerStep, int i) {
    Stars[i].velocityRadius += (Stars[i].forceRadius/Stars[i].mass)*timePerStep;
    Stars[i].velocityDegree += (Stars[i].forceDegree/Stars[i].mass)*timePerStep;
    Stars[i].radius += Stars[i].velocityRadius * timePerStep + Stars[i].velocityDegree * timePerStep;
}

void savePositions(int k) {
    std::string filename = "/home/niccollingro/Documents/ITG 1/ITG-Galaxiebewegung/Data/SimData/BruteForce/Positionen"
                           + std::to_string(k) + ".txt";
    std::ofstream file(filename, std::ios::trunc);
    if (!file){
        std::cout << "Error creating file" << std::endl;
    }
    for (int i = 0; i < 100000; i++) {
        file << Stars[i].radius << "\t" <<Stars[i].degree << "\t" << Stars[i].velocityRadius << "\t" << Stars[i].velocityDegree << "\t" << Stars[i].mass <<"\n";
    }
}

int SimulationBruteForce(int numberOfTimesteps, float timePerStep){
    float massConstant = 1.989e30;
    float lightYearsInMeter = 9.461e15;
    float timeConversionFactor = 3.156e7;
    importData();



    #pragma omp parallel for schedule(dynamic)
    for (int k=0; k<numberOfTimesteps; ++k) {
        for (int i = 0; i < 100000; i++) {
            for (int j = 0; j < 100000; j++) {
                if (i == j) continue;
                float totalForce = gravitationalConstant * (Stars[i].mass * Stars[j].mass) / pow(sqrt(pow(Stars[i].radius,2)+pow(Stars[j].radius,2)-2*Stars[i].radius*Stars[j].radius*cos(sqrt(pow(Stars[i].degree - Stars[j].degree, 2)))),2);
                Stars[i].forceRadius += totalForce * cos(sqrt(pow(Stars[i].degree - Stars[j].degree, 2)));
                Stars[i].forceDegree += totalForce * sin(sqrt(pow(Stars[i].degree - Stars[j].degree, 2)));
            }
            fromForceCalcPos(timePerStep, i);
        }
        savePositions(k);
    }

    return 0;
}

int main() {
    int numberOfTimesteps = 100;
    float timePerStep = 3.15576e11;
    SimulationBruteForce(numberOfTimesteps, timePerStep);
    return 0;
}