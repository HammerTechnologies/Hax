#pragma once

#include "../hax_entity_manager.h"

inline ngn::EntityId createEnemy(HaxEntityManager& mgr, const ngn::Vec3r& position, const ngn::Vec2r& size) noexcept {
	auto enemy = mgr.createEntity();
	mgr.component(enemy, Transform { position, 0, size });
	mgr.component(enemy, SpriteRenderer { mgr.gameData().sheet(), 1, 1, 0 });
	return enemy;
}
