#include "Activities/Activity.hpp"
#include <string>

using namespace std;

class FightActivity: public Activity {
    string nameEnemy = "Enemy";
  public:
    void displayActivity(sf::RenderWindow &window);
};