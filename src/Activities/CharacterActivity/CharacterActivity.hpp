#ifndef CHARACTERACTIVITY_HPP
#define CHARACTERACTIVITY_HPP

#include "Activities/Activity.hpp"
#include "Global/Utility.hpp"
#include "System/Game.hpp"
#include "System/GameUI.hpp"
#include "Character_Inventory/CharacterActivityUI_Inventory.hpp"

class CharacterActivity : public Activity {
    public :
        CharacterActivity();

        ActivityEnum executeActivity() override;


    private :
        void draw_ui();
};

#endif
