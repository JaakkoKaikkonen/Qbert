#pragma once

namespace Game {

	class State {

	public:
		virtual void init() = 0;

		virtual void handleInput() = 0;
		virtual void update(float dt) = 0;
		virtual void draw(float interpolation) = 0;

		virtual void pause() {}
		virtual void resume() {}

	};

}
