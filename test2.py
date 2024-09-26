import cv2
import numpy as np

def detect_shapes(image):
    # Convertir l'image en niveaux de gris
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    # Appliquer un seuillage inverse pour binariser l'image
    _, thresh = cv2.threshold(gray, 240, 255, cv2.THRESH_BINARY_INV)
    
    # Détecter les contours dans l'image
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    # Initialiser le compteur de formes
    shape_count = 0
    
    # Initialiser une liste pour stocker les informations sur les formes
    shape_info_list = []
    
    # Parcourir les contours détectés
    for contour in contours:
        # Approximer la forme du contour avec un polygone
        epsilon = 0.04 * cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, epsilon, True)
        
        # Si la forme a au moins 3 côtés et moins de 10 côtés (pour éviter les formes complexes)
        if len(approx) >= 3 and len(approx) < 10:
            # Incrémenter le compteur de formes
            shape_count += 1
            
            # Dessiner le contour de la forme
            cv2.drawContours(image, [approx], -1, (0, 255, 0), 2)
            
            # Extraire et stocker les coordonnées des coins de la forme
            corners = np.squeeze(approx, axis=1)
            shape_info_list.append((shape_count, corners))
    
    return image, shape_info_list

def write_shape_info_to_file(shape_info_list, filename):
    with open(filename, 'w') as file:
        for shape_info in shape_info_list:
            corners = shape_info[1]
            for corner in corners:
                file.write(f"{corner[0]} {corner[1]}\n")
            file.write("-1 -1\n")



    

# Charger l'image
image_path=input();
image = cv2.imread(image_path)

# Détecter les formes et leurs coins
image_with_shapes, shape_info_list = detect_shapes(image)

# Écrire les informations sur les formes dans un fichier
write_shape_info_to_file(shape_info_list, 'coordinates.txt')


