#pragma once

#include "../hax_entity_manager.h"

void updatePlayer(HaxEntityManager&, ngn::EntityId) noexcept;

inline ngn::EntityId createPlayer(HaxEntityManager& mgr) noexcept {
	auto player = mgr.createEntity();
	mgr.component(player, Behavior { updatePlayer });
	return player;
}

inline void updatePlayer(HaxEntityManager& mgr, ngn::EntityId) noexcept {
	auto& input = mgr.sharedData().core().input();
	auto& screen = mgr.sharedData().core().screen();
	auto& viewer = mgr.sharedData().viewer();
	viewer.viewportSize(screen.size());
	if (input.isKeyDown(ngn::Key::LEFT)) { viewer.euler(viewer.euler() - ngn::Vec3r {0, 180 * screen.delta(), 0}); }
	if (input.isKeyDown(ngn::Key::RIGHT)) { viewer.euler(viewer.euler() + ngn::Vec3r {0, 180 * screen.delta(), 0}); }
	if (input.isKeyDown(ngn::Key::UP)) { viewer.move(ngn::Vec3r{0, 0, 16 * screen.delta()}); }
	if (input.isKeyDown(ngn::Key::DOWN)) { viewer.move(ngn::Vec3r{0, 0, -16 * screen.delta()}); }
}
