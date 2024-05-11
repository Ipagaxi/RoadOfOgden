#include "Actors/Actor.hpp"

Actor::Actor() {}


Observer::Observer(Actor& subject_): subject(subject_) {
  this->subject.attachObserver(*this);
}

Observer::~Observer() {
  this->subject.detachObserver(*this);
}