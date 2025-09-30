from PIL import Image
import os

# --- Paramètres ---
input_file = "1666765882frenchtatotcards.png"  # Ton fichier source
output_dir = "output_cards"     # Dossier de sortie
cols, rows = 10, 8              # Grille : 10 colonnes × 8 lignes

# --- Chargement de l'image ---
img = Image.open(input_file)
width, height = img.size
card_width = width // cols
card_height = height // rows

# --- Création du dossier de sortie ---
os.makedirs(output_dir, exist_ok=True)

# --- Découpe et sauvegarde ---
for row in range(rows):
    for col in range(cols):
        left = col * card_width
        upper = row * card_height
        right = left + card_width
        lower = upper + card_height
        card = img.crop((left, upper, right, lower))
        index = row * cols + col + 1
        card.save(f"{output_dir}/card_{index:02d}.png")

print("✅ Découpe terminée : 80 cartes enregistrées.")
