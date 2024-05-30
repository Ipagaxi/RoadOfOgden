#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <list>
#include <iostream>

class Subject;

class Observer {
  public:
    Observer();
    virtual ~Observer();

    Observer(const Observer&) = delete; // rule of three
    Observer& operator=(const Observer&) = delete;

    virtual void update(int newValue) const;
    void invalidateSubject() const;

  private:
  bool valid = true;
  Subject* subject;
};

class Subject {
  public:
    ~Subject();
    using RefObserver = std::reference_wrapper<const Observer>;
    void attachObserver(const Observer& observer);
    void detachObserver(Observer& observer);
    bool valid = true;

  private:
    std::list<RefObserver> observers;

  protected:
    virtual void notify(int newValue) const = 0;
};

#endif