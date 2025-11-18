#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

/*public variable naming : camel Case (Example : int maxPlayerHealth)
  private variable naming : dashed camel case (Example : int _maxPlayerHealth)
  global variables : PascalCase (Example : int MaxPlayerHealth)*/

// simple shapes class
class SimpleShapes {
public:
    std::string Name = "";
    std::shared_ptr<sf::Vector2<float>> ShapePosition = std::make_shared<sf::Vector2<float>>(0.0f,0.0f);
    std::shared_ptr<sf::Vector2<float>> ShapeSpeed = std::make_shared<sf::Vector2<float>>(0.0f,0.0f);
    std::shared_ptr<sf::Color> ShapeColor = std::make_shared<sf::Color>(255,255,255);

    SimpleShapes(const std::string& name, std::shared_ptr<sf::Vector2<float>> position, std::shared_ptr<sf::Vector2<float>> speed, std::shared_ptr<sf::Color> color)
        :Name(name), ShapePosition(position), ShapeSpeed(speed), ShapeColor(color) { }

    virtual sf::Shape* getShape() {
        return nullptr;
    }
};

class SimpleCircle : public SimpleShapes {

    sf::CircleShape Shape;

public :

    int Radius;
    // default constructor with sensible defaults
    SimpleCircle()
        : SimpleShapes(std::string("Circle"),
            std::make_shared<sf::Vector2<float>>(0, 0),
            std::make_shared<sf::Vector2<float>>(0, 0),
            std::make_shared<sf::Color>(255, 255, 255)),
        Radius(10) 
    {
        Shape.setFillColor(*ShapeColor);
        Shape.setPosition(*ShapePosition);
    }

    // parameterized constructor for the simple circle
    SimpleCircle(std::string& name, int radius, std::shared_ptr<sf::Vector2<float>> position, std::shared_ptr<sf::Vector2<float>> speed, std::shared_ptr<sf::Color> color)
        :SimpleShapes(name,position,speed,color), Radius(radius)
    {
        Shape.setFillColor(*ShapeColor);
        Shape.setPosition(*ShapePosition);
    }

    sf::Shape* getShape() override {
        std::cout << "get the circle shape !" << std::endl;
        return &Shape;
    }
};

class SimpleRectangle : public SimpleShapes {

    sf::RectangleShape rectangle;
public :
    std::shared_ptr<sf::Vector2<int>> Size;
    SimpleRectangle()
        : SimpleShapes(std::string("Circle"),
            std::make_shared<sf::Vector2<float>>(0, 0),
            std::make_shared<sf::Vector2<float>>(0, 0),
            std::make_shared<sf::Color>(255, 255, 255)),
        Size(std::make_shared<sf::Vector2<int>>(10, 10)) {
    }
    SimpleRectangle(const std::string& name, std::shared_ptr<sf::Vector2<int>> size, std::shared_ptr<sf::Vector2<float>> position, std::shared_ptr<sf::Vector2<float>> speed, std::shared_ptr<sf::Color> color)
        :SimpleShapes(name, position, speed, color),Size(size){ }
};

class ConfigFileReader {
    std::ifstream configFile;
    int windowSize[2] = {0,0};

    std::vector<SimpleShapes*> shapeHolder;

public:
    ConfigFileReader() = default;

    ConfigFileReader(std::string Path = "") {
        if (Path.empty()) {
            std::cout << "String is empty (invalid)." << std::endl;
        }
        else
        {
            configFile.open(Path);
            if (!configFile.is_open()) {
                std::cerr << "Error opening file!" << std::endl;
            }
            else
            {
                std::cout << "File opened successfully !" << std::endl;
                //getWindowConfig(configFile);
                
            }
        }
    }

    ~ConfigFileReader() {
        if (configFile.is_open()) {
            configFile.close(); 
            std::cout << "File object closed !";
        }
    }

    std::vector<SimpleShapes> getShapes() {
        return shapeHolder;
    }

    std::vector<std::string> split_sentence(std::string sen) {

        // Create a stringstream object
        std::stringstream ss(sen);

        // Variable to hold each word
        std::string  word;

        // Vector to store the words
        std::vector<std::string> words;

        // Extract words from the sentence
        while (ss >> word) {

            // Add the word to the vector
            words.push_back(word);
        }

        return words;
    }

    void getWindowConfig() {
        std::string line;
        
        while (std::getline(configFile, line)) {
            // Process string Line
            std::vector<std::string> result = split_sentence(line);
            if (result.size() != 0)
            {
                if (!result[0].compare("Window")) {
                    windowSize[0] = std::stoi(result[1]);
                    windowSize[1] = std::stoi(result[2]);

                    std::cout << "Window size set !" << std::endl;
                    
                }
                else if(!result[0].compare("Font"))
                {
                    std::cout << "Found a Font !" << std::endl;
                }
                else if (!result[0].compare("Circle"))
                {
                    std::cout << "Found a circle !" << std::endl;
                    // Example: Circle name posX posY speedX speedY colorR colorG colorB radius
                    if (result.size() >= 9) {
                        std::string name = result[1];
                        int radius = std::stoi(result[9]);
                        std::shared_ptr<sf::Vector2<float>> position = std::make_shared<sf::Vector2<float>>(std::stoi(result[2]), std::stoi(result[3]));
                        std::shared_ptr<sf::Vector2<float>> speed = std::make_shared<sf::Vector2<float>>(std::stoi(result[4]), std::stoi(result[5]));
                        std::shared_ptr<sf::Color> color = std::make_shared<sf::Color>(std::stoi(result[6]), std::stoi(result[7]), std::stoi(result[8]));

                        SimpleCircle* tempCircle(name, radius, position, speed, color);

                        shapeHolder.push_back(tempCircle);
                    }
                }
                else if (!result[0].compare("Rectangle"))
                {
                    std::cout << "Found a Rectangle !" << std::endl;
                }
            }
            else
            {
                continue;
            }
        }
    }
};

int main()
{
    // read the config file
    ConfigFileReader confReader = ConfigFileReader("D:\\Projects\\2DSimpleGameEngine\\Config.txt");
    confReader.getWindowConfig();


    // create the window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window");

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
        
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(sf::CircleShape(100.0f));
        for (auto shape : confReader.getShapes()) {
            if (shape.getShape() != nullptr) 
            {
                window.draw(*shape.getShape());
            }
        }

        // end the current frame
        window.display();
    }
}