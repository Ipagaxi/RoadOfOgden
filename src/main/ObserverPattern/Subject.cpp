#include "ObserverPattern/Subject.hpp"

void Subject::notify(int newValue) {
  for (Observer obs: observers) {
    obs.onNotify(newValue);
  }
}

void Subject::attachObserver(Observer &observer) {
  this->observers.push_front(observer);
}

void Subject::detachObserver(Observer &observer) {
  this->observers.remove_if([&observer] (const Observer obs) {
    return &obs == &observer;
  });
}