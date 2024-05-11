#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <list>

#include "ObserverPattern/Observer.hpp"

class Subject {
  public:
    void attachObserver(Observer& observer);
    void detachObserver(Observer& observer);

  private:
    std::list<Observer> observers;

  protected:
    virtual void notify(int newValue);
};

#endif