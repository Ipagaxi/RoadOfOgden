#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <list>
#include <iostream>
#include <memory>

class Subject;

class Observer {
  public:
    Observer(Subject& subject);
    virtual ~Observer();

    Observer(const Observer&) = delete; // rule of three
    Observer& operator=(const Observer&) = delete;

    virtual void update(int newValue);
    void invalidateSubject();
    bool subjectIsValid() const;

  private:
    bool valid = true;
    Subject& subject;
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
    virtual void notify(int newValue) const = 0;
};

#endif