import numpy as np
import matplotlib.pyplot as plt



for i in range(186):
    plt.close()
    coordinateRadius = []
    coordinateDegree = []
    coordinateX = []
    coordinateY = []
    file="/home/niccollingro/Documents/ITG 1/ITG-Galaxiebewegung/Data/SimData/BruteForce/Positionen{}.txt".format(i)
    with open(file, "r") as f:
        for line in f:
            values = line.strip().split("\t")  # Zeile aufsplitten (Tab als Trennzeichen)
            coordinateRadius.append(float(values[0]))
            coordinateDegree.append(float(values[1]))

    coordinateX = coordinateRadius * np.sin(coordinateDegree)
    coordinateY = coordinateRadius * np.cos(coordinateDegree)

    # Filtern der Punkte, die in den oberen 25% von X und Y liegen
    x_min = np.max(coordinateX) * 0.05
    x_max = np.max(coordinateX) * 0.10
    y_min = np.max(coordinateY) * 0.05
    y_max = np.max(coordinateY) * 0.10

    # Filtern der Punkte innerhalb des Zoom-Bereichs
    mask = (coordinateX >= x_min) & (coordinateX <= x_max) & (coordinateY >= y_min) & (coordinateY <= y_max)
    zoomX = coordinateX[mask]
    zoomY = coordinateY[mask]

    fig, ax = plt.subplots(figsize=(40, 40), dpi=100)

    fig.patch.set_facecolor('black')

    ax.set_facecolor('black')

    #ax.scatter(zoomX, zoomY, color='white', s=8)
    ax.scatter(coordinateX, coordinateY, c='white', s=0.1)

    ax.set_xticks([])  # Entfernt x-Achsen-Ticks
    ax.set_yticks([])  # Entfernt y-Achsen-Ticks
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.spines['bottom'].set_visible(False)
    ax.spines['left'].set_visible(False)
    ax.set_xticklabels([])  # Entfernt x-Achsen-Beschriftungen
    ax.set_yticklabels([])
    #ax.set_xlim(x_min, x_max)
    #ax.set_ylim(y_min, y_max)

    plt.tight_layout()
    plt.savefig("/home/niccollingro/Documents/ITG 1/ITG-Galaxiebewegung/Data/SimData/Output files/BruteForce/FullFrame/Pic{}.png".format(i), format="png", bbox_inches='tight', pad_inches=0, dpi=100)
