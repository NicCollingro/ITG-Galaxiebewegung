from PIL import Image
import os
import subprocess

image_folder = "/home/niccollingro/Documents/ITG 1/ITG-Galaxiebewegung/Data/SimData/Output files/BruteForce/FullFrame/"

for img_file in os.listdir(image_folder):
    if img_file.endswith(".png"):
        img_path = os.path.join(image_folder, img_file)
        img = Image.open(img_path)
        width, height = img.size

        # Falls ungerade, auf nächste gerade Zahl setzen
        new_width = width if width % 2 == 0 else width + 1
        new_height = height if height % 2 == 0 else height + 1

        # Resize nur wenn nötig
        if (new_width, new_height) != (width, height):
            img = img.resize((new_width, new_height), Image.LANCZOS)
            img.save(img_path)

print("Alle Bilder sind nun auf gerade Dimensionen angepasst.")
# Pfad zu den Bildern
output_video = "/home/niccollingro/Documents/ITG 1/ITG-Galaxiebewegung/Data/SimData/Output files/BruteForce/FullFrame/output.mp4"

# Überprüfen, ob Bilder existieren
images = sorted([img for img in os.listdir(image_folder) if img.endswith(".png")])

if not images:
    print("Keine Bilder gefunden!")
    exit()

# Prüfen, ob FFmpeg installiert ist
try:
    subprocess.run(["ffmpeg", "-version"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
except FileNotFoundError:
    print("FFmpeg ist nicht installiert! Installiere es und versuche es erneut.")
    exit()

# FFmpeg-Befehl ausführen
ffmpeg_command = [
    "ffmpeg",
    "-framerate", "24",                  # 24 Bilder pro Sekunde
    "-i", f"{image_folder}Pic%d.png",    # Input-Bilder (stellenweise Nummerierung wichtig!)
    "-c:v", "libx264",                   # Codec für H.264-Komprimierung
    "-preset", "slow",                    # Encoding-Qualität
    "-crf", "18",                         # Qualität (0 = beste, 51 = schlechteste, 18 ist fast verlustfrei)
    "-pix_fmt", "yuv420p",                # Standard für MP4-Videos
    output_video
]

subprocess.run(ffmpeg_command)

print(f"Video gespeichert als: {output_video}")