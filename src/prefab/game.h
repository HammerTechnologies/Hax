#pragma once

#include <sstream>
#include "../hax_entity_manager.h"

void updateGame(HaxEntityManager&, ngn::EntityId) noexcept;

inline ngn::EntityId createGame(HaxEntityManager& mgr) noexcept {
	auto game = mgr.createEntity();
	mgr.component(game, Behavior { updateGame });
	mgr.component(game, TextRenderer {"", {14, 12}, ngn::Color::RED});
	return game;
}

inline void updateGame(HaxEntityManager& mgr, ngn::EntityId game) noexcept {
	auto& data = mgr.gameData();
	auto textRen = mgr.component<TextRenderer>(game);
	auto ss = std::ostringstream {};
	ss << data.screenSize().x() << "x" << data.screenSize().y() << " @ " << data.fps() << " FPS";
	textRen->text = ss.str();
}
