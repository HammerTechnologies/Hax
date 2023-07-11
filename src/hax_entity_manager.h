#pragma once

#include "comp/behavior.h"
#include "comp/sprite_renderer.h"
#include "comp/text_renderer.h"
#include "comp/transform.h"
#include "hax_data.h"
#include "ngn/entity_manager.h"

struct HaxEntityManager : ngn::EntityManager<
	HaxData,
	Behavior,
	SpriteRenderer,
	TextRenderer,
	Transform> {};
