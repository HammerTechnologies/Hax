#pragma once

#include "../hax_entity_manager.h"

void updatePlayer(HaxEntityManager&, ngn::EntityId) noexcept;

inline ngn::EntityId createPlayer(HaxEntityManager& mgr) noexcept {
	auto player = mgr.createEntity();
	mgr.component(player, Behavior { updatePlayer });
	return player;
}

inline void updatePlayer(HaxEntityManager& mgr, ngn::EntityId) noexcept {
	auto& inputs = mgr.gameData().inputs();
	auto& screen = mgr.gameData().core().screen();
	auto& viewer = mgr.gameData().viewer();
	viewer.viewportSize(screen.size());
	viewer.euler(viewer.euler() + ngn::Vec3r {0, inputs.right * 180 * screen.delta(), 0});
	viewer.move(ngn::Vec3r {0, 0, inputs.forward * 16 * screen.delta()});
}
