#pragma once

#include <functional>
#include "../ngn/entity_manager.h"

struct HaxEntityManager;

struct Behavior {
	std::function<void(HaxEntityManager&, ngn::EntityId)> func;
};
