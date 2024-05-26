#include "ObserverPattern/Observer.hpp"

//constructor and destructor defined in ObserverPattern/Subject.cpp

Observer::Observer() {
  std::cout << "Observer" << std::endl;
}

Observer::~Observer() {
  std::cout << "~Observer" << std::endl;
  //this->subject->detachObserver(*this);
}

void Observer::onNotify(int newValue) {}

void Subject::notify(int newValue) {
  for (Observer obs: observers) {
    obs.onNotify(newValue);
  }
}

void Subject::attachObserver(Observer &observer) {
  std::cout << "Observer attached" << std::endl;
  this->observers.push_front(observer);
}

void Subject::detachObserver(Observer &observer) {
  std::cout << "Size: " << this->observers.size() << std::endl;
  this->observers.remove_if([&observer] (const Observer obs) {
    return &obs == &observer;
  });
}