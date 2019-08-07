#pragma once

#include <SFML/Graphics.hpp>

struct SharedContext;

class State_Base{
    
    friend class StateMachine;
    
public:
    
    State_Base(SharedContext * ctx) : ctx(ctx), transparent(false), transcendent(false){}
    
    virtual ~State_Base(){}
    
    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;
    
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    
    virtual void update(const sf::Time & time) = 0;
    virtual void draw() = 0;
    
    void setTransparent(const bool& transparent){ this->transparent = transparent; }
    bool isTransparent()const{ return transparent; }
    void setTranscendent(const bool& transcendence){ this->transcendent = transcendence; }
    bool isTranscendent()const{ return transcendent; }
    
    sf::View & getView(){ return view; }
    
protected:
    
    SharedContext * ctx;
    
    bool transparent;
    bool transcendent;
    sf::View view;
};
