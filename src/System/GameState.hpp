#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>

#include "Actors/Player.hpp"

// The game state represents a game run including the player, the world and their progression
class GameState {
    public:
        std::shared_ptr<Player> player;

        static GameState& getInstance();
        static GameState& getInstance(Player player);

        GameState(const GameState&) = delete;
        GameState& operator=(const GameState&) = delete;

        void update_player(Player player);
    
    private:
        GameState(Player player);
        ~GameState();

        static GameState* instance;
};

#endif