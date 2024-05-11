#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Actor;

class Observer {
  public:
    Observer(Actor& subject);
    virtual ~Observer();
    virtual void onNotify(int newValue);
  private:
    Actor& subject;
};

#endif