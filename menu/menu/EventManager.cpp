#include "EventManager.hpp"
#include "SharedContext.hpp"

EventManager::EventManager(SharedContext * ctx) : ctx(ctx), currentState(StateType(0)), hasFocus(true) {
    loadBindingsFromFile("assets/config/keys.cfg");
}

EventManager::~EventManager(){
    for (auto & bindingItr : bindings){
        delete bindingItr.second;
    }
}

bool EventManager::addBinding(Binding * binding){
    if (bindings.find(binding->name) != bindings.end())
        return false;
    
    return bindings.emplace(binding->name, binding).second;
}

void EventManager::setCurrentState(StateType state){
    currentState = state;
}

void EventManager::setFocus(const bool& focus){ hasFocus = focus; }

void EventManager::handlePolledEvent(sf::Event & event){
    for (auto & bindingItr : bindings){
        Binding * binding = bindingItr.second;
        for (auto &bindingEventItr : binding->events){
            EventType sfmlEvent = (EventType)event.type;
            if (bindingEventItr.type != sfmlEvent){ continue; }
            if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp){
                if (bindingEventItr.info.code == event.key.code){
                    if (binding->details.keyCode != -1){
                        binding->details.keyCode = bindingEventItr.info.code;
                    }
                    ++(binding->fullfilledEventCount);
                    break;
                }
            } else {
                // No need for additional checking.
                if (sfmlEvent == EventType::WindowResized){
                    binding->details.size.x = event.size.width;
                    binding->details.size.y = event.size.height;
                } else if (sfmlEvent == EventType::TextEntered){
                    binding->details.textEntered = event.text.unicode;
                }
                ++(binding->fullfilledEventCount);
            }
        }
    }
}

void EventManager::handleRealTimeEvents(){
    if (!hasFocus){ return; }
    for (auto &b_itr : bindings){
        Binding* binding = b_itr.second;
        for (auto &e_itr : binding->events){
            if (e_itr.type == EventType::Keyboard) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.info.code))){
                        if (binding->details.keyCode != -1){
                            binding->details.keyCode = e_itr.info.code;
                        }
                        ++(binding->fullfilledEventCount);
                    }
            }
        }
        
        if (binding->allEventsFullfilled()){
            auto stateCallbacks = callbacks.find(currentState);
            auto globalCallbacks = callbacks.find(StateType(0));
            
            if (stateCallbacks != callbacks.end()){
                auto callItr = stateCallbacks->second.find(binding->name);
                if (callItr != stateCallbacks->second.end()){
                    // Pass in information about events.
                    callItr->second(&binding->details);
                }
            }
            
            if (globalCallbacks != callbacks.end()){
                auto callItr = globalCallbacks->second.find(binding->name);
                if (callItr != globalCallbacks->second.end()){
                    // Pass in information about events.
                    callItr->second(&binding->details);
                }
            }
        }
        binding->fullfilledEventCount = 0;
        binding->details.clear();
    }
}

void EventManager::loadBindingsFromFile(std::string filePath){
    
    std::ifstream bindingsStream;
    bindingsStream.open(filePath);
    
    if (!bindingsStream.is_open()){
        std::cerr << "! Failed loading keys from file: " << filePath << std::endl;
        exit(1);
    }
    
    std::string line;
    
    while (std::getline(bindingsStream, line)){
        
        if (line[0] == '#' || line.empty()) { continue; }
        
        std::stringstream eventStream(line);
        std::string bindingName;
        eventStream >> bindingName;
        
        Binding* binding = new Binding(bindingName);
        
        while (!eventStream.eof()){
            
            std::string typeAndCodeDelimiter = ":";
            std::string events;
            eventStream >> events;
            
            int start = 0;
            int end = (int)events.find(typeAndCodeDelimiter);
            
            if (end == std::string::npos){
                delete binding;
                binding = nullptr;
                break;
            }
            
            EventType type = EventType(stoi(events.substr(start, end - start)));
            int code = stoi(events.substr(end + typeAndCodeDelimiter.length(),
                events.find(typeAndCodeDelimiter, end + typeAndCodeDelimiter.length())));
            EventInfo eventInfo;
            eventInfo.code = code;
            binding->bindEvent(type, eventInfo);
        }
        
        if (!addBinding(binding)){
            std::cerr << "Binding with name: " << bindingName << "already exists" << std::endl;
            delete binding;
        }
        
        binding = nullptr;
    }
    bindingsStream.close();
}
