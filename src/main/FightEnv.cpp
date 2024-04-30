#include "FightEnv.hpp"

FightEnv::FightEnv() {
  playerStatsBox.init(Game::getInstance().player);
}
