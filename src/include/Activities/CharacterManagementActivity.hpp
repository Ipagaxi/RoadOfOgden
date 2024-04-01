#ifndef CHARACTERMANAGEMENTACTIVITY_HPP
#define CHARACTERMANAGEMENTACTIVITY_HPP

#include "Activities/Activity.hpp"
#include "Defines.hpp"
#include "GameState.hpp"

class CharacterManagementActivity : public Activity {
    public :
        CharacterManagementActivity(GameState &gameState);

        void executeActivity(GameState &game) override;


    private :
        sf::Texture backgroundTX;
        sf::Sprite backgroundSP;
};

#endif
