#pragma once
#include "State.h"
#include <map>


template <typename T>
class StateMachine
{
protected:
    std::map<T, State<T>*> states;
    State<T>* currentState;
public:
    StateMachine() {
    }

    void add(State<T>* state) {
        if (state == 0)
            return;
        states[state->getID()] = state;
    }

    void add(T stateID, State<T>* state) {
        states.add(stateID, state);
    }

    State<T>* getState(T stateID) {
        return states[stateID];
    }

    State<T>* getCurrentState() {
        return currentState;
    }

    void setCurrentState(T stateID) {
        State<T>* state = getState(stateID);
        setCurrentState(state);
    }

    void setCurrentState(State<T>* state) {
        if (currentState == state)
        {
            return;
        }
        if (currentState != nullptr)
        {
            currentState->exit();
        }
        currentState = state;
        if (currentState != nullptr)
        {
            currentState->enter();
        }
    }

    void update() {
        if (currentState != nullptr)
        {
            currentState->update();
        }
    }
};