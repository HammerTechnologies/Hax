#pragma once

#include "../hax_entity_manager.h"

void updatePlayer(HaxEntityManager&, ngn::EntityId) noexcept;

inline ngn::EntityId createPlayer(HaxEntityManager& mgr) noexcept {
	auto player = mgr.createEntity();
	mgr.component(player, Behavior { updatePlayer });
	return player;
}

inline void updatePlayer(HaxEntityManager& mgr, ngn::EntityId) noexcept {
	auto& data = mgr.gameData();
	auto& viewer = data.viewer();
	viewer.viewportSize(data.screenSize());
	viewer.euler(viewer.euler() + ngn::Vec3r {0, data.inputs().right * 180 * data.delta(), 0});
	viewer.move(ngn::Vec3r {0, 0, data.inputs().forward * 16 * data.delta()});
}
