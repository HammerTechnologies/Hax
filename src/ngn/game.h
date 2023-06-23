#pragma once

#include <cstdlib>
#include <iostream>
#include "non_owning_ptr.h"

namespace ngn {

struct Game {
	Game() noexcept {
		if (m_instance == nullptr) {
			m_instance = this;
		} else {
			std::cout << "Cannot create multiple instances of Game class." << std::endl;
			exit(-1);
		}
	}

	virtual ~Game() noexcept {
		m_instance = nullptr;
	}

	virtual bool update() = 0;
	virtual void finish() = 0;

	static non_owning_ptr<Game> instance() noexcept { return m_instance; }
private:
	static non_owning_ptr<Game> m_instance;
};

} // namespace ngn
