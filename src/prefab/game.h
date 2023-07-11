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
	auto& screen = mgr.gameData().core().screen();
	auto textRen = mgr.component<TextRenderer>(game);
	auto ss = std::ostringstream {};
	ss << screen.size().x() << "x" << screen.size().y() << " @ " << screen.fps() << " FPS";
	textRen->text = ss.str();
}
