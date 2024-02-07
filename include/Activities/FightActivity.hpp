#include "Activities/Activity.hpp"


using namespace std;

class FightActivity: public Activity {
    string nameEnemy = "Enemy";
  public:
    void displayActivity(sf::RenderWindow &window, sf::Texture &background, sf::Texture &gear) override;
};