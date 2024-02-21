#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>

struct RGB {
    int red = 0;
    int green = 0;
    int blue = 0;
};

class Actor {
    private:

    public:
        std::string name;
        int health;
        RGB offense;
        RGB defense;

    Actor();
};

#endif