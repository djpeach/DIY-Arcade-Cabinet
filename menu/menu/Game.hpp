#pragma once

class Game {
public:
    Game() {
        clear();
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
    // sf::Sprite logo;
    // std::unique_ptr<sf::Texture> logoTexture;

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
    }
};
