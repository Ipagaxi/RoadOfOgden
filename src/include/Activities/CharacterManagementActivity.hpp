#ifndef CHARACTERMANAGEMENTACTIVITY_HPP
#define CHARACTERMANAGEMENTACTIVITY_HPP

#include "Activities/Activity.hpp"
#include "Defines.hpp"
#include "Game.hpp"

class CharacterManagementActivity : public Activity {
    public :
        CharacterManagementActivity(Game &game);

        ActivityEnum executeActivity(Game &game) override;


    private :
        sf::Texture backgroundTX;
        sf::Sprite backgroundSP;
};

#endif
