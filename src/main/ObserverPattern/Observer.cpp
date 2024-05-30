#include "ObserverPattern/Observer.hpp"

//constructor and destructor defined in ObserverPattern/Subject.cpp

Observer::Observer() {
  std::cout << "Observer" << std::endl;
}

Observer::~Observer() {
  std::cout << "~Observer" << std::endl;
  if (this->valid) {
    subject->detachObserver(*this);
  }
}

void Observer::update(int newValue) const {
  std::cout << "Got a notification" << std::endl;
}


void Observer::invalidateSubject() const {
  //this->subject = nullptr;
  //this->valid = false;
}

Subject::~Subject() {
  std::cout << "~Subject" << std::endl;
  this->valid = false;
  for (auto& obs : observers) {
    obs.get().invalidateSubject();
  }
}


void Subject::notify(int newValue) const {
  for (const auto& obs: observers) {
    obs.get().update(newValue);
  }
}

void Subject::attachObserver(const Observer& observer) {
  this->observers.push_front(observer);
}

void Subject::detachObserver(Observer &observer) {
  std::cout << "Size: " << this->observers.size() << std::endl;
  this->observers.remove_if([&observer] (const RefObserver& obs) {

    return &obs.get() == &observer;
  });
}