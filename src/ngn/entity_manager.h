#pragma once

#include <algorithm>
#include <cstddef>
#include <list>
#include <optional>
#include <tuple>
#include <vector>
#include "non_owning_ptr.h"

namespace ngn {

using EntityId = size_t;

template<typename SharedDataType, typename... CompTypes>
struct EntityManager {
	constexpr const SharedDataType& sharedData() const noexcept {
		return m_sharedData;
	}

	constexpr SharedDataType& sharedData() noexcept {
		return m_sharedData;
	}

	constexpr EntityId createEntity() noexcept {
		if (m_freeIds.empty()) {
			m_entities.emplace_back(Entity {});
			return m_entities.size() - 1;
		} else {
			const auto id = m_freeIds.front();
			m_freeIds.pop_front();
			new (&m_entities[id]) Entity {};
			return id;
		}
	}

	constexpr void destroyEntity(EntityId entity) noexcept {
		m_entities[entity] = {};
		m_freeIds.emplace_back(entity);
	}

	constexpr size_t numEntities() const noexcept {
		return m_entities.size();
	}

	constexpr void clear() noexcept {
		m_entities.clear();
		m_freeIds.clear();
	}

	constexpr bool isValid(EntityId entity) const noexcept {
		return bool {m_entities[entity]};
	}

	template <typename CompType>
	constexpr void component(EntityId entity, const CompType& comp) noexcept {
		std::get<std::optional<CompType>>(m_entities[entity].value()) = comp;
	}

	template <typename CompType>
	constexpr void component(EntityId entity, CompType&& comp) noexcept {
		std::get<std::optional<CompType>>(m_entities[entity].value()) = std::move(comp);
	}

	template<typename CompType>
	constexpr non_owning_ptr<CompType> component(EntityId entity) noexcept {
		auto& comp = std::get<std::optional<CompType>>(m_entities[entity].value());
		return comp ? &comp.value() : nullptr;
	}

	template<typename CompType>
	constexpr non_owning_ptr<const CompType> component(EntityId entity) const noexcept {
		auto& comp = std::get<std::optional<CompType>>(m_entities[entity].value());
		return comp ? &comp.value() : nullptr;
	}

	template<typename CompType>
	constexpr void removeComponent(EntityId entity) noexcept {
		std::get<std::optional<CompType>>(m_entities[entity]) = std::nullopt;
	}
private:
	using Entity = std::tuple<std::optional<CompTypes> ...>;

	SharedDataType m_sharedData {};
	std::vector<std::optional<Entity>> m_entities {};
	std::list<EntityId> m_freeIds {};
};

} // namespace ngn
