#pragma once

#include "comp/behavior.h"
#include "comp/text_renderer.h"
#include "hax_globals.h"
#include "ngn/entity_manager.h"

struct HaxEntityManager : ngn::EntityManager<HaxGlobals, Behavior, TextRenderer> {};
