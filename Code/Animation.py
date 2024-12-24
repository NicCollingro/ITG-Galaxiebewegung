from manim import *
import numpy as np

class GalaxyAnimation(ThreeDScene):
    def construct(self):
        # Anzahl der Punkte
        num_points = 1000
        
        # Zufällige Anfangspositionen für die Punkte (in Polarkoordinaten)
        radii = np.random.uniform(4, 20, num_points)  # Radien zwischen 0.5 und 3.0
        angles = np.random.uniform(0, 2 * np.pi, num_points)  # Winkel zwischen 0 und 2π
        speeds = np.random.uniform(0.5, 1.5, num_points)  # Rotationsgeschwindigkeit
        
        # Erstelle die Punkte als kleine Kreise
        points = VGroup(*[
            Dot(color=WHITE).scale(0.2).move_to([r * np.cos(a), r * np.sin(a), 0])
            for r, a in zip(radii, angles)
        ])
        
        self.add(points)  # Punkte zur Szene hinzufügen
        
        def update_points(group, dt):
            for i, dot in enumerate(group):
                # Berechnung der aktuellen Winkelgeschwindigkeit
                angles[i] += speeds[i] * dt
                x = radii[i] * np.cos(angles[i])
                y = radii[i] * np.sin(angles[i])
                dot.move_to([x, y, 0])
        
        # Punkte werden während der Animation kontinuierlich aktualisiert
        points.add_updater(update_points)
        
         # Kameraausrichtung einstellen (Kippen und Drehen)
        self.set_camera_orientation(phi=75 * DEGREES, theta=45 * DEGREES)
        
        # Animation laufen lassen
        self.add(points)
        self.wait(10)  # Die Animation läuft 10 Sekunden lang
