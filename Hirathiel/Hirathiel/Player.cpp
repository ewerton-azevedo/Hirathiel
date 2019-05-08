#include "Player.hpp"

Player::Player(int x, int y, int w, int h, SDL_Renderer* renderer, SDL_Texture* texture):MoB((x),(y),(w),(h),(renderer),(texture)){
	this->speed = 400;
	this->life = 100;
	this->angle = 0;
}

Player::~Player(){}


CombatAction* Player::pollEvents(SDL_Event* event, const Uint8* keystate, CTimer* timer){
	CombatAction* combat = nullptr;
	if (this == nullptr) {
		return combat;
	}

	Vector2D* vector = new Vector2D(0.0f, 0.0f);

	if (keystate[SDL_SCANCODE_W]) {
		vector->subVector(new Vector2D(0, timer->getElapsed() * this->speed));
	}if (keystate[SDL_SCANCODE_S]) {
		vector->addVector(new Vector2D(0, timer->getElapsed() * this->speed));
	}if (keystate[SDL_SCANCODE_A]) {
		vector->subVector(new Vector2D(timer->getElapsed() * this->speed, 0));
	}if (keystate[SDL_SCANCODE_D]) {
		vector->addVector(new Vector2D(timer->getElapsed() * this->speed, 0));
	}

	this->move(vector);
	float angle;

	if (event != nullptr) {
		switch (event->type) {
			case SDL_MOUSEMOTION:
				angle = atan2(event->motion.y - (this->y + this->h), event->motion.x - (this->x + this->w));

				angle = angle * (180 / M_PI);
				if (angle < 0) {
					angle = 360 - (-angle);
				}
				this->angle = angle + 90;
				break;
		
			case SDL_KEYDOWN:
				switch (event->key.keysym.sym) {
				case SDLK_1:
					SDL_Rect* rect = new SDL_Rect();
					rect->h = 50;
					rect->w = 50;
					rect->x = this->x;
					rect->y = this->y;
					combat = new Strike(this->x, this->y, rect, nullptr, this->renderer);
					break;
				}
			break;
		}
	}

	this->update();
	return combat;
}