#include <memory>
#include "comp/behavior.h"
#include "comp/game_data.h"
#include "dir.h"
#include "hax_entity_manager.h"
#include "level.h"
#include "ngn/core.h"
#include "ngn/gfx/font.h"
#include "ngn/gfx/texture.h"
#include "ngn/gfx/viewer.h"
#include "ngn/logger.h"
#include "prefab/game.h"
#include "prefab/player.h"

static auto g_logger = ngn::Logger {};
static auto g_core = std::make_unique<ngn::Core>(ngn::Vec2<uint16_t>{640, 360}, false, g_logger);
static auto g_entityMgr = HaxEntityManager {};
static auto g_level = std::unique_ptr<Level> {};
static auto g_viewer = ngn::Viewer {
	{0, 8, -5},
	{},
	{0, 0},
	g_core->screen().size(),
};

void init() noexcept {
	changeDir(exeDir() + "/assets");

	auto font = std::shared_ptr<ngn::Font> {g_core->graphics().loadFont("Minecraft.ttf", 16)};
	auto tex = std::shared_ptr<ngn::Texture> {g_core->graphics().loadTexture("textures/wall001.png")};
	g_level = std::make_unique<Level>(ngn::Vec2<uint8_t>{16, 16}, 0, tex, g_core->graphics());

	auto gameData = GameData { g_core->input(), g_core->graphics(), g_core->screen(), g_viewer };
	createGame(g_entityMgr, gameData, font);
	createPlayer(g_entityMgr, gameData);
}

bool update() noexcept {
	auto& graphics = g_core->graphics();
	auto& input = g_core->input();
	auto& screen = g_core->screen();

	if (!screen.isOpened() || input.isKeyDown(ngn::Key::ESC)) {
		return false;
	}

	// Behaviors
	for (size_t entity = 0; entity < g_entityMgr.numEntities(); ++entity) {
		if (g_entityMgr.isValid(entity)) {
			auto& behavior = g_entityMgr.component<Behavior>(entity);
			if (behavior) { behavior.value().func(g_entityMgr, entity); }
		}
	}

	// 3D rendering
	graphics.setup3D(g_viewer);
	graphics.cls();
	g_level->draw3D(16, ngn::Color::WHITE);

	// 2D rendering
	graphics.setup2D({0, 0}, screen.size());
	g_level->draw2D({16, 32}, 16, ngn::Color::ORANGE);
	graphics.drawRect(
		{12 + g_viewer.position().x(), 28 + g_level->size().y() * 16 - g_viewer.position().z()},
		{8, 8},
		ngn::Color::RED);
	for (size_t entity = 0; entity < g_entityMgr.numEntities(); ++entity) {
		if (g_entityMgr.isValid(entity)) {
			auto& textRenderer = g_entityMgr.component<TextRenderer>(entity);
			if (textRenderer) { textRenderer.value().render(graphics); }
		}
	}
	screen.refresh();

	return true;
}

void finish() noexcept {
	g_entityMgr.clear();
	g_level = nullptr;
	g_core = nullptr;
}
