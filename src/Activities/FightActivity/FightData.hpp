#ifndef FIGHTDATA_HPP
#define FIGHTDATA_HPP

enum WinningParty {
  PLAYER,
  ENEMY,
  NONE
};

class FightData {
  public:
    // If false player lost; is only relevant to evaluate fight
    WinningParty winning_party = WinningParty::NONE;
};

#endif