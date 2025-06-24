#ifndef FIGHTENDSTATE_HPP
#define FIGHTENDSTATE_HPP

#include "Activities/FightActivity/FightStates/FightState.hpp"
#include <System/GameUI.hpp>
#include "Animations/IncomingBanner.hpp"
#include "Activities/FightActivity/FightData.hpp"
#include "System/GameState.hpp"
#include "Global/Save.hpp"
#include "UIElements/UIBox.hpp"
#include "Animations/Fading.hpp"

class FightEndState: public FightState {
  public:
    FightEndState(FightData& fight_data);
    FightStateEnum run() override;
  private:
    IncomingBanner turnChangeBanner = IncomingBanner("Fight End");
    Fading transparent_background_layer_fader = Fading((uint8_t)220, (uint8_t)0, 200);
    FightData& fight_data;

    UIBox fight_result_box = UIBox(sf::Color(51, 25, 0, 150), "borders/metal_border_900x900.png");
    sf::RectangleShape transparent_background_layer;

    int calculate_full_exp_reward();

    void show_fight_results();
};

#endif