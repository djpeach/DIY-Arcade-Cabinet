#include "StateMachine.hpp"
#include "SharedContext.hpp"

StateMachine::StateMachine(SharedContext * ctx) : ctx(ctx) {
//    registerState<State>(StateType::DIYACMenu);
}

StateMachine::~StateMachine(){
    for (auto &itr : states){
        itr.second->onDestroy();
        delete itr.second;
    }
}

void StateMachine::update(const sf::Time& time){
    if (states.empty()){ return; }
    if (states.back().second->isTranscendent() && states.size() > 1){
        auto itr = states.end();
        while (itr != states.begin()){
            if (itr != states.end()){
                if (!itr->second->isTranscendent()){
                    break;
                }
            }
            --itr;
        }
        for (; itr != states.end(); ++itr){
            itr->second->update(time);
        }
    } else {
        states.back().second->update(time);
    }
}

void StateMachine::draw(){
    if (states.empty()){ return; }
    if(states.back().second->isTransparent() && states.size() > 1){
        auto itr = states.end();
        while(itr != states.begin()){
            if(itr != states.end()){
                if(!itr->second->isTransparent()){
                    break;
                }
            }
            --itr;
        }
        for(; itr != states.end(); ++itr){
            ctx->window->getRenderWindow()->setView(itr->second->getView());
            itr->second->draw();
        }
    } else {
        states.back().second->draw();
    }
}

bool StateMachine::hasState(const StateType& type){
    for (auto itr = states.begin();
         itr != states.end(); ++itr)
    {
        if (itr->first == type){
            auto removed = std::find(toRemove.begin(), toRemove.end(), type);
            if (removed == toRemove.end()){ return true; }
            return false;
        }
    }
    return false;
}

void StateMachine::processRequests(){
    while (toRemove.begin() != toRemove.end()){
        removeState(*toRemove.begin());
        toRemove.erase(toRemove.begin());
    }
}

void StateMachine::changeState(const StateType & type){
    ctx->eventManager->setCurrentState(type);
    for (auto itr = states.begin();
         itr != states.end(); ++itr)
    {
        if (itr->first == type){
            states.back().second->deactivate();
            StateType tmp_type = itr->first;
            State_Base * tmp_state = itr->second;
            states.erase(itr);
            states.emplace_back(tmp_type, tmp_state);
            tmp_state->activate();
            ctx->window->getRenderWindow()->setView(tmp_state->getView());
            return;
        }
    }
    
    // State with type wasn't found.
    if (!states.empty()){ states.back().second->deactivate(); }
    createState(type);
    states.back().second->activate();
    ctx->window->getRenderWindow()->setView(states.back().second->getView());
}

void StateMachine::remove(const StateType & type){
    toRemove.push_back(type);
}

// Private methods.

void StateMachine::createState(const StateType & type){
    auto newState = stateFactory.find(type);
    if (newState == stateFactory.end()){ return; }
    State_Base * state = newState->second();
    state->view = ctx->window->getRenderWindow()->getDefaultView();
    states.emplace_back(type, state);
    state->onCreate();
}

void StateMachine::removeState(const StateType & type){
    for (auto itr = states.begin();
         itr != states.end(); ++itr)
    {
        if (itr->first == type){
            itr->second->onDestroy();
            delete itr->second;
            states.erase(itr);
            return;
        }
    }
}
