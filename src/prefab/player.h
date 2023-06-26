#pragma once

#include "../hax_entity_manager.h"

void updatePlayer(HaxEntityManager&, ngn::EntityId) noexcept;

inline ngn::EntityId createPlayer(HaxEntityManager& mgr, const GameData& gameData) noexcept {
	auto player = mgr.createEntity();
	mgr.component<Behavior>(player) = Behavior { updatePlayer };
	mgr.component<GameData>(player) = GameData { gameData };
	return player;
}

inline void updatePlayer(HaxEntityManager& mgr, ngn::EntityId player) noexcept {
	auto& gameData = mgr.component<GameData>(player).value();
	auto& input = gameData.input.get();
	auto& screen = gameData.screen.get();
	auto& viewer = gameData.viewer.get();
	viewer.viewportSize(screen.size());
	if (input.isKeyDown(ngn::Key::LEFT)) { viewer.euler(viewer.euler() - ngn::Vec3r {0, 180 * screen.delta(), 0}); }
	if (input.isKeyDown(ngn::Key::RIGHT)) { viewer.euler(viewer.euler() + ngn::Vec3r {0, 180 * screen.delta(), 0}); }
	if (input.isKeyDown(ngn::Key::UP)) { viewer.move(ngn::Vec3r{0, 0, 16 * screen.delta()}); }
	if (input.isKeyDown(ngn::Key::DOWN)) { viewer.move(ngn::Vec3r{0, 0, -16 * screen.delta()}); }
}
