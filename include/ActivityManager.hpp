#ifndef ACTIVITYMANAGER_HPP
#define ACTIVITYMANAGER_HPP

#include "ActivityEnum.hpp"
#include "GameState.hpp"
#include "Activities/FightActivity.hpp"
#include "Activities/MenuActivity.hpp"

namespace ActivityManager {
    void runCurrentActivity(GameState &gameState) {

        Activity* activity = nullptr;
        switch (gameState.currentActivity) {
        case Fight:
            activity = new FightActivity();
            break;
        case Menu:
            activity = new MenuActivity();
            break;
        
        default:
            break;
        }

        if (activity != nullptr) {
            activity->displayActivity(gameState);
            delete activity;
        }
    }
}

#endif