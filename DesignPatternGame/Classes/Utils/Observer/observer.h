#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Subject; // 前向声明

class Observer {
public:
    virtual void update(Subject* subject) = 0;
};

#endif // __OBSERVER_H__