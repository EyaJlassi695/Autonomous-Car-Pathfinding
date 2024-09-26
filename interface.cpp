#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include "interface.hpp"
#include "classes.hpp"

using namespace std;
// Fonction pour détecter le contour en tenant compte des niveaux de gris
void findContour(const sf::Image &image, vector<vector<Sommet>>& nodes) {

    int width = image.getSize().x;
    int height = image.getSize().y;
    vector <Sommet> edgeSommet;
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            sf::Color currentPixel = image.getPixel(j, i);
            sf::Color northPixel = image.getPixel(j, i - 1);
            sf::Color southPixel = image.getPixel(j, i + 1);
            sf::Color westPixel = image.getPixel(j - 1, i);
            sf::Color eastPixel = image.getPixel(j + 1, i);

            // Vérifie si le pixel courant fait partie du contour
            if (currentPixel.r > northPixel.r + 1 ||
                currentPixel.r > southPixel.r + 1 ||
                currentPixel.r > westPixel.r + 1 ||
                currentPixel.r > eastPixel.r + 1) {
                edgeSommet.push_back(Sommet(j,i));
            }
        }
    }

    nodes.push_back(edgeSommet);
}

void detectAndSaveContours(const string &imagePath, vector<vector<Sommet>>& nodes) {

      sf::Image edgeImage;
      if (edgeImage.loadFromFile(imagePath)) {
        edgeImage.createMaskFromColor(sf::Color::White);  // Convertir en niveaux de gris

        // Récupérer la taille de l'image
        unsigned int width = edgeImage.getSize().x;
        unsigned int height = edgeImage.getSize().y;

        // Parcourir l'image pour détecter les contours
        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                // Si le pixel dans l'image de contours est noir, enregistrez les coordonnées
                if (edgeImage.getPixel(x,y) == sf::Color::Black) {

                    // Utiliser une pile pour effectuer un parcours en profondeur pour trouver tous les pixels du contour
                    stack<sf::Vector2u> stack;
                    stack.push(sf::Vector2u(x,y));

                    // Créer une nouvelle image pour chaque forme détectée
                    sf::Image formImage;
                    formImage.create(width, height, sf::Color::White);

                    while (!stack.empty()) {
                        sf::Vector2u current = stack.top();
                        stack.pop();

                        if (current.x >= 0 && current.x < width && current.y >= 0 && current.y < height &&
                            edgeImage.getPixel(current.x, current.y) == sf::Color::Black) {
                            edgeImage.setPixel(current.x, current.y, sf::Color::White);  // Marquer le pixel comme visité

                            // Ajouter le point au fichier de contours
                            formImage.setPixel(current.x, current.y, sf::Color::Black);

                            // Ajouter les voisins non visités à la pile
                            stack.push(sf::Vector2u(current.x + 1, current.y));
                            stack.push(sf::Vector2u(current.x - 1, current.y));
                            stack.push(sf::Vector2u(current.x, current.y + 1));
                            stack.push(sf::Vector2u(current.x, current.y - 1));
                        }
                    }
                    // detecter le contour des formes
                        findContour(formImage,nodes) ;
                }
            }
        }

    }
    else{
        cout<<"erreur"<<endl;
    }
}
