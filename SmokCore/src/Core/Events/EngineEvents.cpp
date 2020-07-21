#include <smpch.h>
#include "EngineEvents.h"

std::vector<fastdelegate::DelegateMemento> ECSSystemEvent::methods;
std::vector<fastdelegate::DelegateMemento> ECSGUIRenderEvent::methods;
std::vector<fastdelegate::DelegateMemento> UpdateEvent::methods;
std::vector<fastdelegate::DelegateMemento> FixedUpdateEvent::methods;

fastdelegate::FastDelegate0<void> ECSSystemEvent::system;
fastdelegate::FastDelegate0<void> ECSGUIRenderEvent::system;
fastdelegate::FastDelegate1<float> UpdateEvent::update;
fastdelegate::FastDelegate1<float> FixedUpdateEvent::fixedUpdate;

//the begin and end of the Smok GUI Renderer
fastdelegate::FastDelegate0<void> ECSGUIRenderEvent::begin;
fastdelegate::FastDelegate0<void> ECSGUIRenderEvent::end;