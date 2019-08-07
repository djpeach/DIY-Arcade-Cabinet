#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>

#include <SFML/Graphics.hpp>

struct SharedContext;

// The types of events available
enum class EventType{
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1 // realtime keyboard input
};

// Some adt'l data an event might need to store
struct EventInfo{
    EventInfo(){ code = 0; }
    
    EventInfo(int event){ code = event; }
    
    union{
        int code;
    };
};

// The event
struct Event {
    Event(EventType type, EventInfo info) : type(type), info(info) {
        
    }
    
    EventType type;
    EventInfo info;
};

// Details that incorporate info of each event in a binding
struct BindingDetails{
    BindingDetails() {
        clear();
    }
    
    void clear(){
        size = sf::Vector2i(0, 0);
        textEntered = 0;
        keyCode = -1;
    }
    
    sf::Vector2i size;
    sf::Uint32 textEntered;
    int keyCode; // Single key code.
};

// A binding links a cb name to a set of events
struct Binding{
    Binding(const std::string & name) : name(name), fullfilledEventCount(0){}
    
    void bindEvent(EventType type, EventInfo info = EventInfo()){
        events.emplace_back(Event(type, info));
    }
    
    bool allEventsFullfilled() {
        return fullfilledEventCount >= events.size();
    }
    
    std::vector<Event> events;
    std::string name;
    int fullfilledEventCount;
    
    BindingDetails details;
};

// a data structure to link cb names to an action
using CallbackSet = std::unordered_map<std::string, std::function<void(BindingDetails*)>>;

enum class StateType;

class EventManager{
public:
    EventManager(SharedContext * ctx);
    ~EventManager();
    
    void setCurrentState(StateType state);
    void setFocus(const bool & focus);
    
    template<class T>
    bool addCallback(StateType state, const std::string & name, void(T::*func)(BindingDetails *), T * instance)
    {
        auto callbackSet = callbacks.emplace(state, CallbackSet()).first->second;
        auto action = std::bind(func, instance, std::placeholders::_1);
        return callbackSet.emplace(name, action).second;
    }
    
    bool removeCallback(StateType state, const std::string& name){
        auto callbackItr = callbacks.find(state);
        if (callbackItr == callbacks.end()){ return false; }
        CallbackSet * callbackSet = &callbackItr->second;
        auto cbItr = callbackSet->find(name);
        if (cbItr == callbackSet->end()){ return false; }
        callbackSet->erase(name);
        return true;
    }
    
    void handlePolledEvent(sf::Event& event);
    void handleRealTimeEvents();
    
private:
    bool addBinding(Binding * binding);
    void loadBindingsFromFile(std::string filePath);
    
    SharedContext * ctx;
    
    StateType currentState;
    std::unordered_map<std::string, Binding*> bindings;
    std::unordered_map<StateType, CallbackSet> callbacks;
    
    bool hasFocus;
};
