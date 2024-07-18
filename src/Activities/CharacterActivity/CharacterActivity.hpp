#ifndef CHARACTERACTIVITY_HPP
#define CHARACTERACTIVITY_HPP

#include "Activities/Activity.hpp"
#include "config.hpp"
#include "System/Game.hpp"

class CharacterActivity : public Activity {
    public :
        CharacterActivity();

        ActivityEnum executeActivity() override;


    private :
        sf::Texture backgroundTX;
        sf::Sprite backgroundSP;
};

#endif
