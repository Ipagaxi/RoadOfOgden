#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <list>
#include <iostream>
#include <memory>

template <typename T>
class Subject;

template <typename T>
class Observer {
  public:
    Observer(Subject<T>& _subject): subject(_subject) {
        this->subject.attachObserver(*this);
    }

    virtual ~Observer() {
        if (this->valid) {
            subject.detachObserver(*this);
        }
    }

    Observer(const Observer&) = delete; // rule of three
    Observer& operator=(const Observer&) = delete;

    virtual void on_notify(T entity) {
    }

    void invalidateSubject() {
        this->valid = false;
    }

  private:
    bool valid = true;
    Subject<T>& subject;
};

template <typename T>
class Subject {
  public:
    virtual ~Subject() {
        this->valid = false;
        for (auto& obs : this->observers) {
            obs.get().invalidateSubject();
        }
    };
    using RefObserver = std::reference_wrapper<Observer<T>>;
    void attachObserver(Observer<T>& observer) {
        this->observers.push_front(observer);
    }

    void detachObserver(Observer<T> &observer) {
        this->observers.remove_if([&observer] (const RefObserver& obs) {

            return &obs.get() == &observer;
        });
    }

    virtual void notify(T entity) const {
        for (const auto& obs: observers) {
            obs.get().on_notify(entity);
        }
    }

    bool valid = true;

  private:
    std::list<RefObserver> observers;

  protected:
};

#endif