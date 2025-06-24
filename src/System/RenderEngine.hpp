#ifndef RENDERENGINE_HPP
#define RENDERENGINE_HPP

#include <SFML/Graphics.hpp>

class RenderEngine {
  public:
    sf::RenderWindow gameWindow;

    static RenderEngine& getInstance();
    RenderEngine(const RenderEngine&) = delete;
    RenderEngine& operator=(const RenderEngine&) = delete;

    //RenderEngine(sf::RenderWindow* gameWindow);

  private:
    RenderEngine();
    RenderEngine(sf::RenderWindow* game_window);
    ~RenderEngine();
    static RenderEngine* instance;

};

#endif