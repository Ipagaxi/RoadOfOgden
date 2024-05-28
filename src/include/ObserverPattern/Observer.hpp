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
    void invalidateSubject();

  private:
  Subject* subject;
};

class Subject {
  public:
    ~Subject();
    using RefObserver = std::reference_wrapper<Observer>;
    void attachObserver(Observer& observer);
    void detachObserver(Observer& observer);
    bool valid = true;

  private:
    std::list<RefObserver> observers;

  protected:
    virtual void notify(int newValue);
};

#endif