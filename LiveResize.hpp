#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>

//Makes the window keep redrawing while its border is being dragged (windows only, does nothing on other systems)
//
//Why it is needed: while the border is dragged, windows runs its own loop and window.pollEvent() does not return,
//so the main loop cannot draw until the mouse is released.
//
//How to use: create one LiveResize after the window, give it a function that draws one full frame,
//and call LiveResize::applyView(window) at the start of that function.
//The LiveResize object must be destroyed before the window (declaring it after the window does that).

class LiveResize{
    public:
    LiveResize(sf::RenderWindow& window, std::function<void()> redraw);
    ~LiveResize();

    LiveResize(const LiveResize&)=delete;
    LiveResize& operator=(const LiveResize&)=delete;

    //Sets a view that fits the real window size and returns that size. Returns nothing if the window is minimized.
    //Needed because during a drag SFML sends no Resized event, so window.getSize() is outdated.
    static std::optional<sf::Vector2u> applyView(sf::RenderWindow& window);

    //Called by the windows message hook. Not meant to be called directly.
    void redrawNow();

    private:
    sf::RenderWindow& targetWindow;
    std::function<void()> redrawCallback;
    bool busy=false;        //stops redrawNow from calling itself again
};
