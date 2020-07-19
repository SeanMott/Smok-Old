#include <smpch.h>
#include "EngineEvents.h"

std::vector<fastdelegate::DelegateMemento> ECSSystemEvent::methods;
std::vector<fastdelegate::DelegateMemento> UpdateEvent::methods;
std::vector<fastdelegate::DelegateMemento> FixedUpdateEvent::methods;

fastdelegate::FastDelegate0<void> ECSSystemEvent::system;
fastdelegate::FastDelegate1<float> UpdateEvent::update;
fastdelegate::FastDelegate1<float> FixedUpdateEvent::fixedUpdate;