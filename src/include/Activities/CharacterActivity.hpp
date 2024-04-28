#ifndef CHARACTERACTIVITY_HPP
#define CHARACTERACTIVITY_HPP

#include "Activities/Activity.hpp"
#include "Defines.hpp"
#include "Game.hpp"

class CharacterActivity : public Activity {
    public :
        CharacterActivity(Game &game);

        ActivityEnum executeActivity(Game &game) override;


    private :
        sf::Texture backgroundTX;
        sf::Sprite backgroundSP;
};

#endif
