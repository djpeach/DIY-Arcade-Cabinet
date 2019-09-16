#pragma once

class Game {
public:
    Game() {
        clear();
    }

    void setLogo(std::string path) {
      if(!logoTexture.loadFromFile("../../games/" + exePath + path)) {
        std::cout << "could not load logo from path: ../../games/" + exePath + path << std::endl;
        exit(1);
      }
      logo.setTexture(logoTexture);
    }

    sf::Text name;
    sf::Text author;
    sf::Text language;
    std::string exePath;
    std::string start1;
    std::string start2;
    sf::Color bgColor;
    std::vector<std::string> mappings;
    std::vector<std::string> instructions;
    std::string startButton;
    bool hasLogo;
    sf::Sprite logo;
    sf::Texture logoTexture;

    void clear() {
        name.setString("");
        author.setString("");
        language.setString("");
        exePath = "";
        start1 = "";
        start2 = "";
        mappings.clear();
        instructions.clear();
        bgColor = sf::Color(120, 120, 120);
        startButton = "";
        hasLogo = false;
    }
};
