#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

/*public variable naming : camel Case (Example : int maxPlayerHealth)
  private variable naming : dashed camel case (Example : int _maxPlayerHealth)
  global variables : PascalCase (Example : int MaxPlayerHealth)*/

#pragma region ForwardsDeclarations
    
#pragma endregion


struct Circle {
    std::string name;
    sf::Vector2<float> position = sf::Vector2(100.0f, 100.0f);
    sf::Vector2<float> speed = sf::Vector2( 0.1f, 0.1f);
    sf::Color color = sf::Color::White;
    float radius = 10.0f;
};

struct Rectangle {
    std::string name;
    sf::Vector2<float> position = sf::Vector2(100.0f, 100.0f);
    sf::Vector2<float> speed = sf::Vector2(0.1f, 0.1f);
    sf::Color color = sf::Color::White;
    sf::Vector2<float> Size = sf::Vector2<float>(50.0f, 50.0f);
};

struct FontData {
    std::string path = "";
    int size = 5;
    sf::Color color = sf::Color::White;
    sf::Font fontobj;
};

class ConfigFileReader {
    std::ifstream inputFile;
public:
    ConfigFileReader() = default;
    

    ConfigFileReader(const std::string& path, sf::Vector2u& winSize, FontData& font, std::vector<Circle>& circles, std::vector<Rectangle>& rectangles)
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
                        font.path = params[1];
                        font.size = std::stoi(params[2]);
                        font.color = sf::Color(std::stoi(params[3]), std::stoi(params[4]), std::stoi(params[5]));

                        sf::Font tempfont;
                        if (!tempfont.openFromFile(params[1])) {
                            std::cerr << " couldnt open the file !" << std::endl;
                        }
                        font.fontobj = tempfont;
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
                        c.radius = std::stof(params[9]);
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

                        unsigned long rl = std::stoul(params[6]);
                        unsigned long gl = std::stoul(params[7]);
                        unsigned long bl = std::stoul(params[8]);
                        uint8_t r8 = static_cast<uint8_t>(rl);
                        uint8_t g8 = static_cast<uint8_t>(gl);
                        uint8_t b8 = static_cast<uint8_t>(bl);

                        r.color = sf::Color(r8, g8, b8);
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

// ANIMATION FUNCTIONS
void SetupCircles(std::vector<sf::CircleShape>& circles, std::vector<Circle> data) {
    for (int i = 0; i < data.size(); i++) {
        circles[i].setRadius(data[i].radius);
        circles[i].setFillColor(data[i].color);
        circles[i].setPosition(data[i].position);
    }
}

void SetupRectangles(std::vector<sf::RectangleShape>& rects, std::vector<Rectangle> data) {
    for (int i = 0; i < data.size(); i++) {
        rects[i].setSize(data[i].Size);
        rects[i].setFillColor(data[i].color);
        rects[i].setPosition(data[i].position);
    }
}

void UpdateCircle(sf::CircleShape& drawing, Circle& data, sf::Text& label) {
    sf::Vector2f newPosition = drawing.getPosition() + (data.speed * 0.1f);
    drawing.setPosition(newPosition);

    //Centering the label
    sf::Vector2f textcenter = sf::Vector2f(label.getLocalBounds().size.x * 0.5f, label.getLocalBounds().size.y * 0.5f);
    sf::Vector2f circlecenter = sf::Vector2f(drawing.getPosition().x + (drawing.getLocalBounds().size.x * 0.5f) , drawing.getPosition().y + (drawing.getLocalBounds().size.y *0.5f));

    sf::Vector2f finalPosition = circlecenter - textcenter;
    label.setPosition(finalPosition);
    
    data.position = newPosition;
}
void UpdateRectangle(sf::RectangleShape& drawing, Rectangle data, sf::Text& label) {
    sf::Vector2f newPosition = drawing.getPosition() + (data.speed * 0.1f);

    drawing.setPosition(newPosition);
    //Centering the label
    sf::Vector2f textcenter = sf::Vector2f(label.getLocalBounds().size.x * 0.5f, label.getLocalBounds().size.y * 0.5f);
    sf::Vector2f circlecenter = sf::Vector2f(drawing.getPosition().x + (drawing.getLocalBounds().size.x * 0.5f), drawing.getPosition().y + (drawing.getLocalBounds().size.y * 0.5f));
    sf::Vector2f finalPosition = circlecenter - textcenter;
    label.setPosition(finalPosition);
    
    data.position = newPosition;
}


// COLLISION CHECK FOR BOTH SHAPES
void CheckCircleCollision(sf::Window& window, sf::Shape& shape ) {
    //std::cout << "circle window : " << window.getSize().x << " -- " << window.getSize().y << std::endl;
    
}
void CheckRectangleCollision(sf::Window& window, sf::Shape& shape) {
    //std::cout << "rectangle window : " << window.getSize().x << " -- " << window.getSize().y << std::endl;
    
}


// FONT HELPER FUNCTION
std::vector<sf::Text> SetupCircleLabels(std::vector<Circle> circles, FontData& font) {
    sf::Text temp(font.fontobj);

    std::vector<sf::Text> labels;
    for (int i = 0; i < circles.size(); i++) {
        temp.setCharacterSize(font.size);
        temp.setFillColor(font.color);
        temp.setString(circles[i].name);
        temp.setPosition(sf::Vector2f(100.0f, 100.0f));
        labels.push_back(temp);
    }

    return labels;
}
std::vector<sf::Text> SetupRectangleLabels(std::vector<Rectangle> rectangles, FontData& font) {
    sf::Text temp(font.fontobj);
    std::vector<sf::Text> labels;
    for (int i = 0; i < rectangles.size(); i++) {
        temp.setCharacterSize(font.size);
        temp.setFillColor(font.color);
        temp.setString(rectangles[i].name);
        temp.setPosition(sf::Vector2f(100.0f, 100.0f));
        labels.push_back(temp);
    }

    return labels;
}


int main()
{
    // global variables
    std::string Path = "D:\\Projects\\2DSimpleGameEngine\\Config.txt";
    sf::Vector2u windowSize = sf::Vector2(800u, 600u);
    
    
    // data from the config file
    std::vector<Circle> CircleData;
    std::vector<Rectangle> RectangleData;
    FontData font;

    // Config file PATH
    ConfigFileReader(Path, windowSize, font, CircleData, RectangleData);

    // shapes and labels to draw
    std::vector<sf::CircleShape> Circles(CircleData.size());
    std::vector<sf::Text> CircleLabel = SetupCircleLabels(CircleData, font);
    std::vector<sf::RectangleShape> Rectangles(RectangleData.size());
    std::vector<sf::Text> RectangleLabel = SetupRectangleLabels(RectangleData, font);
    
    SetupCircles(Circles, CircleData);
    SetupRectangles(Rectangles, RectangleData);

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
        
        // update position, 
        for (int i = 0; i < CircleData.size(); i++) {
            UpdateCircle(Circles[i], CircleData[i], CircleLabel[i]);
            //CheckCircleCollision(window, Circles[i]);
        }
        for (int i = 0; i < RectangleData.size(); i++) {
            UpdateRectangle(Rectangles[i], RectangleData[i], RectangleLabel[i]);
            //CheckRectangleCollision(window, Rectangles[i]);
        }
        

        // Drawing process (delete, process , display)
        window.clear(sf::Color::Black);

        // draw everything here...
        
        for (int i = 0; i < Circles.size(); i++) {
            window.draw(Circles[i]);
            window.draw(CircleLabel[i]);
        }
        for (int i = 0; i < Rectangles.size(); i++) {
            window.draw(Rectangles[i]);
            window.draw(RectangleLabel[i]);
        }
        

        // end the current frame
        window.display();
    }
}