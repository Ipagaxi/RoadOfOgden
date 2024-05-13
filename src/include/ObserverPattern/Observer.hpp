#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <list>
#include <iostream>

class Subject;

class Observer {
  public:
    Observer();
    //Observer(Actor& subject);
    virtual ~Observer();
    virtual void onNotify(int newValue);
  private:
    Subject* subject;
};

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