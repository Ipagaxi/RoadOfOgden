#include "ObserverPattern/Observer.hpp"

//constructor and destructor defined in ObserverPattern/Subject.cpp

Observer::Observer() {
  std::cout << "Observer" << std::endl;
}

Observer::~Observer() {
  std::cout << "~Observer" << std::endl;
  if (subject && subject->valid) {
    subject->detachObserver(*this);
  }
}

void Observer::onNotify(int newValue) {}

void Observer::invalidateSubject() {
  this->subject = nullptr;
}

Subject::~Subject() {
  this->valid = false;
  for (RefObserver& obs : observers) {
    obs.get().invalidateSubject();
  }
}


void Subject::notify(int newValue) {
  for (Observer obs: observers) {
    obs.onNotify(newValue);
  }
}

void Subject::attachObserver(Observer &observer) {
  this->observers.push_front(observer);
}

void Subject::detachObserver(Observer &observer) {
  std::cout << "Size: " << this->observers.size() << std::endl;
  this->observers.remove_if([&observer] (const RefObserver& obs) {

    return &obs.get() == &observer;
  });
}