#pragma once
#include <string>

template <typename T>
class StateMachine;

template <typename T>
class State
{
public:
    inline T getID()
    {
        return stateId;
    }
    inline const std::string& getName() const
    {
        return stateName;
    }
    explicit State(T id,
        std::string name = "NoState")
        : stateName(name)
        , stateId(id)
    {
    }
    virtual void enter() {}
    virtual void exit() {}
    //virtual void update() {}
private:
    std::string stateName;
    T stateId;
    StateMachine<T>* stateMachine;
};

