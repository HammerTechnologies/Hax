#include <memory>
#include "dir.h"
#include "hax_entity_manager.h"
#include "hax_data.h"
#include "prefab/enemy.h"
#include "prefab/game.h"
#include "prefab/player.h"

static auto changedToAssetsDir = changeDir(exeDir() + "/assets");
static auto entityMgr = HaxEntityManager {};

void init() noexcept {
	if (!changedToAssetsDir) {
		entityMgr.gameData().m_core->logger().error("Could not set 'assets' dir as active.");
	}
	createGame(entityMgr);
	createEnemy(
		entityMgr,
		{-32, 0, 32},
		ngn::Vec2r(entityMgr.gameData().level().size().x(), entityMgr.gameData().level().size().y()));
	createPlayer(entityMgr);
}

bool update() noexcept {
	auto& data = entityMgr.gameData();
	data.update();
	auto& graphics = data.m_core->graphics();
	auto& input = data.m_core->input();
	auto& screen = data.m_core->screen();
	auto& level = data.level();
	auto& viewer = data.viewer();

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
	graphics.setup3D(entityMgr.gameData().viewer());
	graphics.cls();
	level.draw3D(16, ngn::Color::WHITE);

	// Sprites
	const ngn::Mat4r viewMatrix = entityMgr.gameData().viewer().viewMatrix();
	for (size_t entity = 0; entity < entityMgr.numEntities(); ++entity) {
		if (entityMgr.isValid(entity)) {
			auto spriteRen = entityMgr.component<SpriteRenderer>(entity);
			auto transform = entityMgr.component<Transform>(entity);
			if (spriteRen && transform) {
				const ngn::Mat4r matrix = ngn::Mat4r::billboard(
					viewMatrix,
					transform->position,
					transform->rotation,
					ngn::Vec2r(transform->scale.x(), transform->scale.y()),
					true);
				graphics.drawQuad(matrix, &spriteRen->texture.get());
			}
		}
	}

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
			if (textRenderer) { textRenderer->render(entityMgr.gameData().font(), graphics); }
		}
	}
	screen.refresh();

	return true;
}

void finish() noexcept {
	entityMgr.clear();
	entityMgr.gameData().finish();
}
