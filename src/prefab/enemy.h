#pragma once

#include "../hax_entity_manager.h"

inline ngn::EntityId createEnemy(HaxEntityManager& mgr) noexcept {
	auto enemy = mgr.createEntity();
	mgr.component(enemy, SpritePosition { {-32, 0, 32} });
	mgr.component(enemy, SpriteRenderer { mgr.gameData().sheet(), 1, 1, 0 });
	return enemy;
}
