#include "ObserverPattern/Observer.hpp"

Observer::Observer(Subject& _subject): subject(_subject) {
  subject.attachObserver(*this);
  std::cout << "Observer" << std::endl;
}

Observer::~Observer() {
  if (this->valid) {
    subject.detachObserver(*this);
  }
}

void Observer::update(int newValue) const {
  std::cout << "Got a notification" << std::endl;
}


void Observer::invalidateSubject() {
  this->valid = false;
}

bool Observer::subjectIsValid() const {
  return this->valid;
}

Subject::~Subject() {
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

void Subject::attachObserver(Observer& observer) {
  this->observers.push_front(observer);
}

void Subject::detachObserver(Observer &observer) {
  std::cout << "Size: " << this->observers.size() << std::endl;
  this->observers.remove_if([&observer] (const RefObserver& obs) {

    return &obs.get() == &observer;
  });
}