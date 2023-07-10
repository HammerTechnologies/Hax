#include <memory>
#include "comp/behavior.h"
#include "dir.h"
#include "hax_entity_manager.h"
#include "hax_globals.h"
#include "prefab/game.h"
#include "prefab/player.h"

static auto changedToAssetsDir = changeDir(exeDir() + "/assets");
static auto entityMgr = HaxEntityManager {};

void init() noexcept {
	if (!changedToAssetsDir) {
		entityMgr.sharedData().core().logger().error("Could not set 'assets' dir as active.");
	}
	createGame(entityMgr);
	createPlayer(entityMgr);
}

bool update() noexcept {
	auto& graphics = entityMgr.sharedData().core().graphics();
	auto& input = entityMgr.sharedData().core().input();
	auto& screen = entityMgr.sharedData().core().screen();
	auto& level = entityMgr.sharedData().level();
	auto& viewer = entityMgr.sharedData().viewer();

	if (!screen.isOpened() || input.isKeyDown(ngn::Key::ESC)) {
		return false;
	}

	// Behaviors
	for (size_t entity = 0; entity < entityMgr.numEntities(); ++entity) {
		if (entityMgr.isValid(entity)) {
			auto behavior = entityMgr.component<Behavior>(entity);
			if (behavior) { behavior->func(entityMgr, entity); }
		}
	}

	// 3D rendering
	graphics.setup3D(entityMgr.sharedData().viewer());
	graphics.cls();
	level.draw3D(16, ngn::Color::WHITE);

	// 2D rendering
	graphics.setup2D({0, 0}, screen.size());
	level.draw2D({16, 32}, 16, ngn::Color::ORANGE);
	graphics.drawRect(
		{12 + viewer.position().x(), 28 + level.size().y() * 16 - viewer.position().z()},
		{8, 8},
		ngn::Color::RED);
	for (size_t entity = 0; entity < entityMgr.numEntities(); ++entity) {
		if (entityMgr.isValid(entity)) {
			auto textRenderer = entityMgr.component<TextRenderer>(entity);
			if (textRenderer) { textRenderer->render(entityMgr.sharedData().font(), graphics); }
		}
	}
	screen.refresh();

	return true;
}

void finish() noexcept {
	entityMgr.clear();
	entityMgr.sharedData().finish();
}
