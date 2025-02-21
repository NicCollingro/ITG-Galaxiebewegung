#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>
#include <thread>
#include <valarray>
#include <omp.h>
#include <chrono>
using namespace std;

struct Coordinate {
    float mass;
    double radius;
    double degree;
    double velocityRadius;
    double velocityDegree;
    double forceRadius = 0;
    double forceDegree = 0;
};

float gravitationalConstant = 6.67430e-11;

Coordinate Stars[100000];

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
        //std:cout << "Gelesene Zeile: " << line << std::endl;

        std::string radius_str, degree_str, velocityRadius_str, velocityDegree_str, mass_str;

        ss >> radius_str >> degree_str >> velocityRadius_str >> velocityDegree_str >> mass_str;

        // Konvertiere manuell mit std::stod
        Stars[count].radius = std::stod(radius_str);
        Stars[count].degree = std::stod(degree_str);
        Stars[count].velocityRadius = std::stod(velocityRadius_str);
        Stars[count].velocityDegree = std::stod(velocityDegree_str);
        Stars[count].mass = std::stod(mass_str);

        std::cout << "abgespeicherte werte: " << Stars[count].radius << " " <<Stars[count].degree << " " << Stars[count].velocityRadius << Stars[count].velocityDegree << Stars[count].mass << std::endl;

        ++count;

    }

    file.close();

    return 0;
}

void fromForceCalcPos(float timePerStep, int i) {
    Stars[i].velocityRadius += (Stars[i].forceRadius/Stars[i].mass)*timePerStep;
    Stars[i].velocityDegree += (Stars[i].forceDegree/Stars[i].mass)*timePerStep;
    Stars[i].radius += Stars[i].velocityRadius * timePerStep;
    Stars[i].degree += Stars[i].velocityDegree * timePerStep;
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
    importData();

    double conversionConstant = gravitationalConstant * massConstant / sqrt(pow(lightYearsInMeter,4)-2*pow(lightYearsInMeter,2));

    for (int k=0; k<numberOfTimesteps; ++k) {
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < 100000; i++) {
            for (int j = 0; j < 100000; j++) {
                if (i == j) j = j+1;
                double totalForce = Stars[i].mass * Stars[j].mass * conversionConstant/ (pow(Stars[i].radius,2)+pow(Stars[j].radius,2)-2*Stars[i].radius*Stars[j].radius*cos(Stars[i].degree - Stars[j].degree));
                //double testVal = pow(Stars[i].radius,2)+pow(Stars[j].radius,2)-2*Stars[i].radius*Stars[j].radius*cos(Stars[i].degree - Stars[j].degree);
                //printf("%e %e \n",conversionConstant, totalForce); //, testVal);
                Stars[i].forceRadius += totalForce * cos(Stars[i].degree - Stars[j].degree);
                Stars[i].forceDegree += totalForce * sin(Stars[i].degree - Stars[j].degree);
                //printf("%e %e \n",Stars[i].forceRadius, Stars[i].forceDegree); //, testVal);

            }
            fromForceCalcPos(timePerStep, i);

        }
        savePositions(k);
        printf("%i \n", k);
    }

    return 0;
}

int main() {
    int numberOfTimesteps = 1000;
    float timePerStep = 3.15576e12;
    SimulationBruteForce(numberOfTimesteps, timePerStep);
    return 0;
}
