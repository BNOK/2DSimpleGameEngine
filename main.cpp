#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

/*public variable naming : camel Case (Example : int maxPlayerHealth)
  private variable naming : dashed camel case (Example : int _maxPlayerHealth)
  global variables : PascalCase (Example : int MaxPlayerHealth)*/

struct Circle {
    std::string name;
    sf::Vector2<float> position = sf::Vector2(100.0f, 100.0f);
    sf::Vector2<float> speed = sf::Vector2( 0.1f, 0.1f);
    sf::Color color = sf::Color::White;
    int radius = 10;
};

struct Rectangle {
    std::string name;
    sf::Vector2<float> position = sf::Vector2(100.0f, 100.0f);
    sf::Vector2<float> speed = sf::Vector2(0.1f, 0.1f);
    sf::Color color = sf::Color::White;
    sf::Vector2<float> Size = sf::Vector2<float>(50.0f, 50.0f);
};

class ConfigFileReader {
    std::ifstream inputFile;
public:
    ConfigFileReader() = default;
    

    ConfigFileReader(const std::string& path, sf::Vector2u& winSize, sf::Font& font, std::vector<Circle>& circles, std::vector<Rectangle>& rectangles)
    {
        inputFile;
        inputFile.open(path);
        std::cout << "File opened !"<<std::endl;

        if (inputFile.is_open()) {

            std::string line;

            while (std::getline(inputFile, line)) {
                std::stringstream ss(line);
                std::string word;

                (ss >> word);
                if (word.length() == 0) {
                    continue;
                }
                else {
                    /*std::cout << word << std::endl;
                    while (ss >> word) {
                        std::cout << "value is : " << word << std::endl;
                    }*/

                    std::vector<std::string> params = SplitSentence(line);
                    std::cout << " size : " << params.size() << std::endl;
                    if (params[0] == "Window" && params.size() == 3) {
                        std::cout << "found window" << std::endl;
                        winSize.x = std::stoi(params[1]);
                        winSize.y = std::stoi(params[2]);
                    }
                    else if (params[0] == "Font" && params.size() == 6) {
                        // set font later
                        std::cout << "found font" << std::endl;
                    }
                    else if (params[0] == "Circle" && params.size() == 10) {
                        std::cout << "found circle !" << std::endl;
                        Circle c;
                        c.name = params[1];
                        c.position.x = std::stof(params[2]);
                        c.position.y = std::stof(params[3]);
                        c.speed.x = std::stof(params[4]);
                        c.speed.y = std::stof(params[5]);
                        c.color = sf::Color(std::stoi(params[6]), std::stoi(params[7]), std::stoi(params[8]));
                        c.radius = std::stoi(params[9]);
                        circles.push_back(c);
                    }
                    else if (params[0] == "Rectangle" && params.size() == 11) {
                        std::cout << "found rectangle !" << std::endl;
                        Rectangle r;
                        r.name = params[1];
                        r.position.x = std::stof(params[2]);
                        r.position.y = std::stof(params[3]);
                        r.speed.x = std::stof(params[4]);
                        r.speed.y = std::stof(params[5]);
                        r.color = sf::Color(std::stof(params[6]), std::stof(params[7]), std::stof(params[8]));
                        r.Size.x = std::stof(params[9]);
                        r.Size.y = std::stof(params[10]);
                        rectangles.push_back(r);
                    }
                }

                std::cout << "Finished the Line !" << std::endl;
            }
        }
    }

    ~ConfigFileReader() 
    {
        if (inputFile.is_open()) {
            inputFile.close();
        }
        std::cout << "File closed !"<< std::endl;
    }

    std::vector<std::string> SplitSentence(std::string line) {
        std::stringstream ss(line);
        std::string word;

        std::vector<std::string> result;

        while (ss >> word) {
            result.push_back(word);
        }
        
        return result;
    }
};

void PrintGlobals(std::string path, sf::Vector2<int> winSize, sf::Font font, std::vector<Circle> circles, std::vector<Rectangle> rectangles) {
    std::cout << "Path : " << path << std::endl;
    std::cout << "window height :" << winSize.x << " window width :" << winSize.y << std::endl;
    std::cout << "Font : " << font.getInfo().family << std::endl;
    std::cout << "Circles :" << circles.size() << " Rectangles :" << rectangles.size() << std::endl;
}

void UpdateCircle(sf::CircleShape& drawing, Circle data) {
    drawing.setRadius(data.radius);

    sf::Vector2f newPosition = drawing.getPosition() + (data.speed * 0.1f);
    drawing.setPosition(newPosition);

    drawing.setFillColor(data.color);
}
void UpdateRectangle(sf::RectangleShape& drawing, Rectangle data) {
    drawing.setSize(data.Size);

    sf::Vector2f newPosition = drawing.getPosition() + (data.speed * 0.1f);
    drawing.setPosition(newPosition);

    drawing.setFillColor(data.color);
}


int main()
{
    // global variables
    std::string Path = "D:\\Projects\\2DSimpleGameEngine\\Config.txt";
    sf::Vector2u windowSize = sf::Vector2(800u, 600u);
    sf::Font font;
    // data from the config file
    std::vector<Circle> CircleData;
    std::vector<Rectangle> RectangleData;

    // Config file PATH
    ConfigFileReader(Path, windowSize, font, CircleData, RectangleData);

    // circle shapes to draw
    std::vector<sf::CircleShape> Circles(CircleData.size());
    std::vector<sf::RectangleShape> Rectangles(RectangleData.size());



    // create the window
    sf::RenderWindow window(sf::VideoMode({ windowSize.x, windowSize.y }), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        // prepare shapes to be drawn
        for (int i = 0; i < CircleData.size(); i++) {
            UpdateCircle(Circles[i], CircleData[i]);
        }
        for (int i = 0; i < RectangleData.size(); i++) {
            UpdateRectangle(Rectangles[i], RectangleData[i]);
        }


        // Drawing process (delete, process , display)
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(sf::CircleShape(10.0f));
        for (sf::CircleShape circle : Circles) {
            window.draw(circle);

        }
        for (sf::RectangleShape rectangle : Rectangles) {
            window.draw(rectangle);

        }

        // end the current frame
        window.display();
    }
}