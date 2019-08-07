#pragma once

#include <vector>
#include <unordered_map>

#include "State_DIYACMenu.hpp"

enum class StateType{
    DIYACMenu = 1
};

// State container.
using StateContainer = std::vector<std::pair<StateType, State_Base *>>;

// State factory.
using StateFactory = std::unordered_map<StateType, std::function<State_Base*(void)>>;

class StateMachine {
    
public:
    
    StateMachine(SharedContext * ctx);
    ~StateMachine();
    
    void update(const sf::Time & time);
    void draw();
    
    void processRequests();
    
    bool hasState(const StateType & type);
    
    void changeState(const StateType & type);
    void remove(const StateType & type);
    
private:
    
    void createState(const StateType & type);
    void removeState(const StateType & type);
    
    template<class T>
    void registerState(const StateType & type){
        stateFactory[type] = [this]() -> State_Base *
        {
            return new T(this);
        };
    }
    
    SharedContext * ctx;
    
    StateContainer states;
    std::vector<StateType> toRemove;
    StateFactory stateFactory;
};
