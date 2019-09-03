#include "State_Base.hpp"
#include "Game.hpp"

State_Base::State_Base(SharedContext & ctx, std::string name) :
ctx(ctx),
name(name) {}

State_Base::~State_Base() {}

