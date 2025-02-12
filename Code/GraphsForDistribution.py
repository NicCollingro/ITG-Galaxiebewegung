import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

file="/Users/niccollingro/Desktop/Universitaet des Saarlandes/WiSe 24:25/ITG/ITG-Galaxiebewegung/Data/Startwerte.txt"
coordinateRadius = []
coordinateDegree = []
coordinateVelocity = []
coordinateMass = []

with open(file, "r") as f:
    for line in f:
        values = line.strip().split("\t")  # Zeile aufsplitten (Tab als Trennzeichen)
        coordinateRadius.append(float(values[0]))
        coordinateDegree.append(float(values[1]))
        coordinateVelocity.append(float(values[3]))
        coordinateMass.append(float(values[4]))

coordinateRadius = np.array(coordinateRadius)
coordinateDegree = np.array(coordinateDegree)
coordinateVelocity = np.array(coordinateVelocity)
coordinateMass = np.array(coordinateMass)

unique_values, counts = np.unique(coordinateRadius, return_counts=True)

plt.figure(figsize=(8, 4.5), dpi=300)

plt.hist(coordinateRadius / 1e21, bins=75, density=True, alpha=0.85, edgecolor="black", facecolor='blue', label='Daten')
mu, std = (50000*9.461e15)/1e21, (25000*9.461e15)/1e21
xmin, xmax = plt.xlim()
x = np.linspace(xmin, xmax, 100)
p = norm.pdf(x, mu, std)


plt.plot(x, p, linewidth=2, color="red", label='Gaußverteilung')

plt.xlim(0, 1.3)
plt.xlabel(r'Radius in [m$\cdot 10^{21}$]')
plt.ylabel(r'Häufigkeit in [$10^{-21}$]')
plt.tight_layout()
plt.savefig("/Users/niccollingro/Desktop/Universitaet des Saarlandes/WiSe 24:25/ITG/ITG-Galaxiebewegung/Data/RadiusDisrtibution.pdf", format="pdf")
plt.show()
plt.close()
plt.figure(figsize=(8, 4.5), dpi=300)
plt.hist(coordinateDegree, bins = 100, density=True, alpha=0.85, edgecolor="black", facecolor='blue', label='Daten')
plt.xlabel("Winkel in [rad]")
plt.ylabel("Häufigkeit")
plt.xlim(0, 2*np.pi)
plt.savefig("/Users/niccollingro/Desktop/Universitaet des Saarlandes/WiSe 24:25/ITG/ITG-Galaxiebewegung/Data/DegreeDistribution.pdf", format="pdf")
plt.show()
plt.close()
plt.figure(figsize=(8, 4.5), dpi=300)
plt.hist(coordinateMass, bins = 100, density=True, alpha=0.85, edgecolor="black", facecolor='blue', label='Daten')
plt.xlabel(r'Masse in [M$_{\odot}$]')
plt.ylabel("Häufigkeit")
plt.savefig("/Users/niccollingro/Desktop/Universitaet des Saarlandes/WiSe 24:25/ITG/ITG-Galaxiebewegung/Data/MassDistribution.pdf", format="pdf")
plt.show()