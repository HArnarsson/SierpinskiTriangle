#include <SFML/Graphics.hpp>

#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

void add_vertices(std::vector<sf::CircleShape>& vertices, const int RADIUS, sf::RenderWindow& window){
    const int NUM_VERTICES(3);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    for(int i = 0; i < NUM_VERTICES; i++){
        vertices.push_back(sf::CircleShape(RADIUS));
    }
    vertices.at(0).setPosition(0, HEIGHT);
    vertices.at(1).setPosition(WIDTH/2, 0);
    vertices.at(2).setPosition(WIDTH, HEIGHT);
    vertices.at(0).setFillColor(sf::Color(255,255,255));
    vertices.at(1).setFillColor(sf::Color(255,255,255));
    vertices.at(2).setFillColor(sf::Color(255,255,255));
}

bool is_in_triangle(sf::CircleShape& randomPoint, sf::RenderWindow& window){
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    const float X = randomPoint.getPosition().x;
    const float Y = randomPoint.getPosition().y;
    // X guaranteed to be less than 600 and positive
    // Y guaranteed to be less than 600 and positive
    if(X<=WIDTH/2){return Y >= HEIGHT - 2*X;}
    if(X>WIDTH/2){return Y >= 2*X - HEIGHT;}
    std::cout << "SNO error \n"; 
    return false;
}

sf::CircleShape generate_first_random_point(sf::RenderWindow& window, const int RADIUS){
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    sf::CircleShape randomPoint(RADIUS);
    randomPoint.setFillColor(sf::Color(255,255,255));
    do{
        float X = rand()/(float)RAND_MAX*WIDTH;
        float Y = rand()/(float)RAND_MAX*HEIGHT;
        randomPoint.setPosition(X,Y);
    } while(!is_in_triangle(randomPoint, window));
    return randomPoint;
}

sf::CircleShape generate_random_point(sf::RenderWindow& window, sf::CircleShape mostRecent, std::vector<sf::CircleShape>& vertices, const int RADIUS){
    sf::CircleShape vertex = vertices.at(rand()%3);
    sf::CircleShape newPoint(RADIUS);
    newPoint.setFillColor(sf::Color(255,255,255));
    float newX = (vertex.getPosition().x + mostRecent.getPosition().x)/2;
    float newY = (vertex.getPosition().y + mostRecent.getPosition().y)/2;
    newPoint.setPosition(newX, newY);
    return newPoint;
}

int main(){
    const int WIDTH(600), HEIGHT(600);
    const int RADIUS(1);
    std::srand(std::time(0));
    std::rand();
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sierpinski");


    sf::Event event;

    std::vector<sf::CircleShape> vertices;
    add_vertices(vertices, RADIUS, window);

    std::vector<sf::CircleShape> randomPoints;
    sf::CircleShape firstPoint = generate_first_random_point(window, RADIUS);
    sf::CircleShape mostRecent = firstPoint;
    randomPoints.push_back(firstPoint);

    while(window.isOpen()){

        window.clear();

        for(unsigned int i = 0; i < vertices.size(); i++){
            window.draw(vertices.at(i));
        }

        for(unsigned int i = 0; i < randomPoints.size(); i++){
            window.draw(randomPoints.at(i));
        }

        firstPoint = generate_random_point(window, mostRecent, vertices, RADIUS);
        mostRecent = firstPoint;
        randomPoints.push_back(mostRecent);
        //usleep(5000);

        window.display();

        while( window.pollEvent(event) ) {
            // if event type corresponds to pressing window X
            if(event.type == sf::Event::Closed) {
                // tell the window to close
                window.close();
            }
        }
    }
    return 0;
}