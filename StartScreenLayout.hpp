#pragma once


#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

class StartScreenLayout{
    public: 
    float screenWidth;
    float screenHeight;
    sf::Vector2f screenCenter;
    sf::Vector2f logo;
    float logoSize;
    sf::Vector2f title;
    float titleSize;
    sf::Vector2f startButton;
    sf::Vector2f startButtonSize;
    sf::Vector2f quitButton;
    sf::Vector2f quitButtonSize;
    float buttonOutline;
    float buttonTextSize;

    static StartScreenLayout calculate(sf::Vector2u size) {

        float screenWidth=size.x;
        float screenHeight=size.y;

        float unit = std::min<float>(std::sqrt(screenWidth*screenHeight), 1.5 * std::min(screenWidth,screenHeight));
        unit = std::max(unit, 100.f);

        sf::Vector2f screenCenter={screenWidth/2.f,screenHeight/2.f};

        sf::Vector2f logo = fromCenter(screenWidth,screenHeight,0.f,20.f);
        float logoSize = 0.24*unit;

        sf::Vector2f title = fromCenter(screenWidth,screenHeight,0.f,-2.f);
        float titleSize = 0.1*unit;

        float buttonGap = 0.05*unit;
        float buttonOutline = 0.005*unit;

        sf::Vector2f startButtonSize = {0.24f*unit,0.08f*unit};
        sf::Vector2f startButton = fromCenter(screenWidth,screenHeight,0.f,-20.f);
        startButton.x -= (buttonGap + startButtonSize.x)/2.f;

        sf::Vector2f quitButtonSize = {0.24f*unit,0.08f*unit};
        sf::Vector2f quitButton = fromCenter(screenWidth,screenHeight,0.f,-20.f);
        quitButton.x += (buttonGap + quitButtonSize.x)/2.f;

        float buttonTextSize = std::min(0.45f*startButtonSize.y, 0.8f*startButtonSize.x/5);

        return {screenWidth,screenHeight,screenCenter,logo,logoSize,title,titleSize,startButton,startButtonSize,quitButton,quitButtonSize,buttonOutline,buttonTextSize};

    }

    static StartScreenLayout calculate(const sf::RenderWindow& window) {
        return calculate(window.getSize());
    }

    static sf::Vector2f fromCenter(float sw, float sh, float percentX, float percentY) {
    return {
        sw / 2.f + sw * (percentX / 100.f),
        sh / 2.f - sh * (percentY / 100.f)  //now y increases upwards
    };
}
};