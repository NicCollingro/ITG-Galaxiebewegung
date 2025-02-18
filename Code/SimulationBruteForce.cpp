#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Coordinate {
    float mass;
    float radius;
    float degree;
    float velocityRadius;
    float velocityDegree;
};

Coordinate Stars[100000]; // Richtige Deklaration anstelle von #define

int importData() {
    ifstream file("/Users/niccollingro/Desktop/Universitaet des Saarlandes/WiSe 24:25/ITG/ITG-Galaxiebewegung/Data/Startwerte.txt");
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

int Simulation(float numberOfTimesteps) {
    float gravitationalConstant = 6.67430e-11;
    float massConstant = 1.989e30;
    float lightYearsInMeter = 9.461e15;
    importData();
    for (int i = 0; i < 100000; ++i) {
        cout << "Mass: " << Stars[i].mass << ", "
             << "Radius: " << Stars[i].radius << ", "
             << "Degree: " << Stars[i].degree << ", "
             << "VelocityRadius: " << Stars[i].velocityRadius << ", "
             << "VelocityDegree: " << Stars[i].velocityDegree << endl;
    }
    return 0;
}
