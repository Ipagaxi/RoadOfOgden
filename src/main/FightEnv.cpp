#include "FightEnv.hpp"

FightEnv::FightEnv(Game &game): playerStatsBox(game, game.player), enemyOverview(game), playerOverview(game), turnChangeBanner(game) {

}
