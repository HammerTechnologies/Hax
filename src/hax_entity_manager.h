#pragma once

#include "comp/behavior.h"
#include "comp/game_data.h"
#include "comp/text_renderer.h"
#include "ngn/entity_manager.h"

struct HaxEntityManager : ngn::EntityManager<
	Behavior,
	GameData,
	TextRenderer
> {};
