#pragma once

#include "../hax_entity_manager.h"

void updatePlayer(HaxEntityManager&, ngn::EntityId) noexcept;

inline ngn::EntityId createPlayer(HaxEntityManager& mgr) noexcept {
	auto player = mgr.createEntity();
	mgr.component(player, Behavior { updatePlayer });
	mgr.component(player, Transform { {0, 8, -5} });
	return player;
}

inline void updatePlayer(HaxEntityManager& mgr, ngn::EntityId entity) noexcept {
	auto& data = mgr.gameData();
	auto& viewer = data.viewer();
	auto& transform = *mgr.component<Transform>(entity);
	transform.rotation += data.inputs().right * 180 * data.delta();
	transform.move(ngn::Vec3r {0, 0, data.inputs().forward * 16 * data.delta()});
	viewer.viewportSize(data.screenSize());
	viewer.position(transform.position);
	viewer.euler({0, transform.rotation, 0});
}
