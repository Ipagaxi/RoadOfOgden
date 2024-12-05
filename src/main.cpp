#include <iostream>

#include "System/Game.hpp"
#include "Activities/FightActivity/FightActivity.hpp"
#include "Activities/MenuActivity/MenuActivity.hpp"
#include "Activities/ActivityEnum.hpp"
#include "Global/Utility.hpp"
#include "Global/Save.hpp"


std::unique_ptr<Activity> setCurrentActivity(ActivityEnum newActivityEnum) {
  std::unique_ptr<Activity> newActivity;
  switch (newActivityEnum) {
    case ActivityEnum::Menu:
      newActivity = std::move(std::make_unique<MenuActivity>());
      break;
    case ActivityEnum::Fight:
      newActivity = std::move(std::make_unique<FightActivity>());
      break;
    case ActivityEnum::Character:
      newActivity = std::move(std::make_unique<CharacterActivity>());
      break;
    default:
      break;
  }
  return newActivity;
}

Game* Game::instance = nullptr;

int main()
{
  std::cout << getResourcesDirPath() << std::endl;
  Game& game = Game::getInstance();
  RenderEngine& render_engine = RenderEngine::getInstance();
  GameUI& game_ui = GameUI::getInstance();

  sf::Vector2i mousePos;
  sf::Vector2f mousePosF;

  //generateTexture();

  std::unique_ptr<Activity> currentActivity = std::make_unique<MenuActivity>();
  ActivityEnum currentActivityEnum = ActivityEnum::Menu;
  ActivityEnum oldActivityEnum = ActivityEnum::Menu;

  SaveState::create_game_state_if_no_exist();

  sf::Clock clock;
  sf::Time time;

  while (render_engine.gameWindow.isOpen()) {
    sf::Event event;

    time = clock.restart();
    game.gameStatus.elapsedTime = time;
    //std::cout << "Elapsed Time: " << std::to_string(time.asMilliseconds()) << std::endl;

    while (render_engine.gameWindow.pollEvent(event)) {

        switch (event.type) {
        case sf::Event::Closed:
            //game.backgroundMusic.stop();
            render_engine.gameWindow.close();
            break;

        case sf::Event::MouseMoved:
          game.gameEvents.mouseMoved = true;
            break;

        case sf::Event::MouseButtonPressed:
          game.gameEvents.mousePressed = true;
            mousePos = sf::Mouse::getPosition(render_engine.gameWindow);
            mousePosF = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            game.gameEvents.pressedPos = mousePosF;
            break;

        case sf::Event::MouseButtonReleased:
          game.gameEvents.mouseReleased = true;
            mousePos = sf::Mouse::getPosition(render_engine.gameWindow);
            mousePosF = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            game.gameEvents.releasedPos = mousePosF;
            break;

        default:
            break;
        }
    }
    render_engine.gameWindow.clear();
    currentActivityEnum = currentActivity->executeActivity();
    if (currentActivityEnum != oldActivityEnum) {
      currentActivity = std::move(setCurrentActivity(currentActivityEnum));
      oldActivityEnum = currentActivityEnum;
    }
    render_engine.gameWindow.display();
    game.gameEvents.mousePressed = false;
    game.gameEvents.mouseReleased = false;
    game.gameEvents.mouseMoved = false;
  }
  return 0;
}