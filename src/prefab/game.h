#pragma once

#include <sstream>
#include "../hax_entity_manager.h"

void updateGame(HaxEntityManager&, ngn::EntityId) noexcept;

inline ngn::EntityId createGame(
	HaxEntityManager& mgr,
	const GameData& gameData,
	const std::shared_ptr<ngn::Font>& font) noexcept {
	auto game = mgr.createEntity();
	mgr.component<Behavior>(game) = Behavior { updateGame };
	mgr.component<GameData>(game) = GameData { gameData };
	mgr.component<TextRenderer>(game) = TextRenderer {font, "", {14, 12}, ngn::Color::RED};
	return game;
}

inline void updateGame(HaxEntityManager& mgr, ngn::EntityId game) noexcept {
	auto& gameData = mgr.component<GameData>(game).value();
	auto& screen = gameData.screen.get();
	auto& textRen = mgr.component<TextRenderer>(game).value();
	auto ss = std::ostringstream {};
	ss << screen.size().x() << "x" << screen.size().y() << " @ " << screen.fps() << " FPS";
	textRen.text = ss.str();
}
