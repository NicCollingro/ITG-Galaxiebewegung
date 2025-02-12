import numpy as np
import matplotlib.pyplot as plt

file="/Users/niccollingro/Desktop/Universitaet des Saarlandes/WiSe 24:25/ITG/ITG-Galaxiebewegung/cmake-build-debug/Startwerte.txt"

coordinateX = []
coordinateY = []
coordinateRadius = []
coordinateDegree = []

with open(file, "r") as f:
    for line in f:
        values = line.strip().split("\t")  # Zeile aufsplitten (Tab als Trennzeichen)
        coordinateRadius.append(float(values[0]))
        coordinateDegree.append(float(values[1]))

coordinateX = coordinateRadius * np.sin(coordinateDegree)
coordinateY = coordinateRadius * np.cos(coordinateDegree)

fig, ax = plt.subplots(figsize=(40, 40), dpi=100)

fig.patch.set_facecolor('black')
ax.set_facecolor('black')

ax.scatter(coordinateX, coordinateY, color='white', s=1)


ax.set_xticks([])  # Entfernt x-Achsen-Ticks
ax.set_yticks([])  # Entfernt y-Achsen-Ticks
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['bottom'].set_visible(False)
ax.spines['left'].set_visible(False)
ax.set_xticklabels([])  # Entfernt x-Achsen-Beschriftungen
ax.set_yticklabels([])

plt.show()