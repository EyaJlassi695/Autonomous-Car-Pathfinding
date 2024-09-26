#ifndef INTERFACE_HPP_INCLUDED
#define INTERFACE_HPP_INCLUDED
#include <stack>
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <cmath>

#include <fstream>
#include <iostream>
#include <vector>
#include <cfloat>
#include <chrono> // Pour mesurer le temps

#include "classes.hpp"

// Your code where FLT_MAX is used
using namespace std;
class GraphVisualizer {
public:
    GraphVisualizer(const std::vector<vector<Sommet>>& nodes, const std::string& locImage, const std::string& objectImage, const std::string& backgroundImage, const std::vector<Sommet> chemin)
        : nodes(nodes), locImage(locImage), objectImage(objectImage), backgroundImage(backgroundImage),startClicked(false), endClicked(false),destinationIndex(0)  {

        // Charger les images de d�part, de fin et de l'objet
        if (!loadTexture(locTexture, locImage) || !loadTexture(objectTexture, objectImage) || !loadTexture(backgroundTexture, backgroundImage)) {
            std::cerr << "Erreur lors du chargement des images." << std::endl;
            return;
        }

        locSprite.setTexture(locTexture);
        objectSprite.setTexture(objectTexture);
        backgroundSprite.setTexture(backgroundTexture);

        // D�finir l'�chelle pour r�duire la taille des images
        float scale1 = 0.2;
        // Mettre � l'�chelle les images
        locSprite.setScale(scale1, scale1);

    }

   void visualize(sf::Vector2f &startPos, sf::Vector2f &endPos) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");
    window.setFramerateLimit(60);

    bool startClicked = false;
    bool endClicked = false;
    bool windowClosing = false;
    auto startTime = std::chrono::steady_clock::now(); // Mesurer le temps de d�but

    while (window.isOpen() && !windowClosing) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                windowClosing = true;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Si le d�but n'est pas cliqu�, d�finir la position de d�but
                    if (!startClicked) {
                        startClicked = true;
                        startPos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    }
                    // Si le d�but est cliqu� mais la fin n'est pas cliqu�e, d�finir la position de fin
                    else if (!endClicked) {
                        endClicked = true;
                        endPos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    }
                }
            }
        }

        window.clear();

        // Dessiner l'arri�re-plan
        window.draw(backgroundSprite);
        // Dessiner le graphe
        drawGraph(window);
        // Si les positions de d�but et de fin sont d�finies, dessiner les images
        if (startClicked)
            drawlocImage(window, startPos.x, startPos.y);
        if (endClicked)
            drawlocImage(window, endPos.x, endPos.y);
        window.display();

        // V�rifier si le temps �coul� depuis que l'end position a �t� d�finie d�passe 5 secondes
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        if (endClicked && elapsedTime.count() >= 1) {
            window.close();
        }
    }
}
  void trajectoire(const std::vector<Sommet> chemin) {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Trajectory Visualization");
        window.setFramerateLimit(60);

        // Initialiser la position de l'objet � la premi�re position du chemin
        objectSprite.setPosition(chemin.front().x, chemin.front().y);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear();

            // Dessiner l'arri�re-plan
            window.draw(backgroundSprite);
            // Dessiner le graphe
            drawGraph(window);

            // Dessiner le point de d�part (premier sommet dans 'chemin')
            drawlocImage(window, chemin.front().x, chemin.front().y);

            // Dessiner le point d'arriv�e (dernier sommet dans 'chemin')
            drawlocImage(window, chemin.back().x, chemin.back().y);

            // D�placer l'objet selon la trajectoire
            moveObject(window,chemin);

            window.display();
        }
    }


private:
    std::vector<vector<Sommet>> nodes;
    std::vector<Sommet> chemin;
    std::string locImage;
    std::string objectImage;
    std::string backgroundImage;
    std::string batimentImage="obstacle_1.jpg";

    sf::Sprite locSprite;
    sf::Sprite objectSprite;
    sf::Sprite backgroundSprite;
    sf::Sprite batimentSprite;

    sf::Texture locTexture;
    sf::Texture objectTexture;
    sf::Texture backgroundTexture;
    sf::Texture batTexture;

    size_t destinationIndex;
    bool startClicked; // Ajout de startClicked et endClicked comme membres de la classe
    bool endClicked;


    bool loadTexture(sf::Texture& texture, const std::string& imagePath) {
        if (!texture.loadFromFile(imagePath)) {
            std::cerr << "Erreur lors du chargement de l'image : " << imagePath << std::endl;
            return false;
        }
        return true;
    }

/*   void drawGraph(sf::RenderWindow& window) {
    loadTexture(batTexture, batimentImage);
    batimentSprite.setTexture(batTexture);

    // Largeur et hauteur du sprite de spike
    float spikeWidth = batimentSprite.getLocalBounds().width;
    float spikeHeight = batimentSprite.getLocalBounds().height;
    float h=0.7;

    for (const auto& shapeNodes : nodes) {
    float centerX = 0.0f;
    float centerY = 0.0f;
    for (const auto& node : shapeNodes) {
        centerX += node.x;
        centerY += node.y;
    }
    centerX /= shapeNodes.size();
    centerY /= shapeNodes.size();

    // Cr�er une forme en utilisant les sommets des obstacles
    sf::ConvexShape obstacleShape;
    obstacleShape.setPointCount(shapeNodes.size()); // Nombre de sommets
    for (size_t i = 0; i < shapeNodes.size(); ++i) {
        obstacleShape.setPoint(i, sf::Vector2f(h*shapeNodes[i].x+(1-h)*centerX,h*shapeNodes[i].y+(1-h)*centerY ));
    }

    // D�terminer le rectangle englobant la forme
    sf::FloatRect boundingRect = obstacleShape.getGlobalBounds();

    // Placer les sprites de spike pour remplir la forme
    for (float x = boundingRect.left; x < boundingRect.left + boundingRect.width; x += spikeWidth) {
        for (float y = boundingRect.top; y < boundingRect.top + boundingRect.height; y += spikeHeight) {
            batimentSprite.setPosition(x, y);
            if (obstacleShape.getGlobalBounds().contains(x, y)) {
                window.draw(batimentSprite);
            }
        }
    }
}
   }
*/
    void drawGraph(sf::RenderWindow& window) {
    loadTexture(batTexture, batimentImage);
    batimentSprite.setTexture(batTexture);

    // Largeur et hauteur du sprite de spike
    float spikeWidth = batimentSprite.getLocalBounds().width;
    float spikeHeight = batimentSprite.getLocalBounds().height;
    float h=0.7;

    for (const auto& shapeNodes : nodes) {
    float centerX = 0.0f;
    float centerY = 0.0f;
    for (const auto& node : shapeNodes) {
        centerX += node.x;
        centerY += node.y;
    }
    centerX /= shapeNodes.size();
    centerY /= shapeNodes.size();
           // sf::VertexArray vertexArray(sf::TrianglesFan);
        sf::VertexArray vertexArray(sf::LineStrip);


    for (size_t i = 0; i < shapeNodes.size(); ++i) {
       /* float textureX = shapeNodes[i].x / spikeWidth; // Coordonn�e x normalis�e dans l'image de texture
        float textureY = shapeNodes[i].y / spikeHeight; // Coordonn�e y normalis�e dans l'image de texture*/

        vertexArray.append(sf::Vertex(sf::Vector2f(h*shapeNodes[i].x+(1-h)*centerX,h*shapeNodes[i].y+(1-h)*centerY), sf::Color::Black));
    }
        /*sf::RenderStates states;
        states.texture = &batTexture;*/
        window.draw(vertexArray);}

   }



    void drawlocImage(sf::RenderWindow& window, double X, double Y) {
    // Obtenez les dimensions de la sprite

        locSprite.setPosition(X-22,Y-45);
        window.draw(locSprite);
    }

    void moveObject(sf::RenderWindow& window,const std::vector<Sommet> chemin) {
        if (destinationIndex < chemin.size()) {
            sf::Vector2f destination (chemin[destinationIndex].x,chemin[destinationIndex].y);
            sf::Vector2f currentPosition = objectSprite.getPosition();
            sf::Vector2f direction = destination - currentPosition;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (distance >1.0f) {
                direction/=(distance);
                sf::Vector2f movement = direction * 1.0f;
                objectSprite.move(movement);
            } else {
                // Si l'objet a atteint sa destination, passer � la suivante
                ++destinationIndex;
            }
            // Calcul de l'angle de rotation en radians
        float angleRadians = std::atan2(direction.y, direction.x);
        // Conversion de l'angle de radians � degr�s
        float angleDegrees = angleRadians * (180.0f / M_PI);

        // D�finition de l'angle de rotation du sprite
        objectSprite.setRotation(angleDegrees);
        }

        window.draw(objectSprite);
    }


    sf::FloatRect findBoundingBox(const std::vector<std::vector<Sommet>>& nodes) {
    if (nodes.empty()) {
        // Retourner une bo�te englobante vide s'il n'y a pas de n�uds
        return sf::FloatRect(0, 0, 0, 0);
    }

    float left = nodes[0][0].x;
    float top = nodes[0][0].y;
    float right = left;
    float bottom = top;

    for (const auto& shapeNodes : nodes) {
        for (const auto& node : shapeNodes) {
            if (node.x < left)
                left = node.x;
            if (node.x > right)
                right = node.x;
            if (node.y < top)
                top = node.y;
            if (node.y > bottom)
                bottom = node.y;
        }
    }

    return sf::FloatRect(left, top, right - left, bottom - top);
    };
};

void findContour(const sf::Image &image, std::vector<vector<Sommet>>& nodes);
void detectAndSaveContours(const std::string &imagePath, std::vector<vector<Sommet>>& nodes);
#endif // INTERFACE_HPP_INCLUDED
