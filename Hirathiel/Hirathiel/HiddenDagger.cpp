#include "HiddenDagger.hpp"
#include <SDL.h>
#include <math.h>

HiddenDagger::HiddenDagger(int x, int y, SDL_Rect* rect, SDL_Texture* texture, SDL_Renderer* renderer,int critchance ,float crit) :CombatAction((x), (y), (rect), (texture), (renderer)) {
	this->critchance = critchance;
	this->crit = crit;
	
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	Vector2D* posVector = new Vector2D(mouseX - this->x, mouseY - this->y);
	int sqX, sqY;
	sqX = (int)posVector->getX();
	sqY = (int)posVector->getY();
	if (sqX < 0)
		sqX *= -1;
	if (sqY < 0)
		sqY *= -1;
	sqX *= sqX;
	sqY *= sqY;

	float length = sqrt(sqX + sqY);
	//std::cout << length << std::endl;

	float scalar = 50 / length;


	posVector->scalar(scalar);
	this->x += posVector->getX();
	this->y += posVector->getY();
	this->rect->x = this->x;
	this->rect->y = this->y;

	delete posVector;

	this->addEffects();
}


HiddenDagger::~HiddenDagger(){}

void HiddenDagger::applyEffects(MoB* applicant){
	Effect* copy = nullptr;
	auto list = this->effects.get();

	for (int i = 0; i < list.size(); i++) {
		copy = list.at(i);
		applicant->addEffect(copy);
	}
	copy = nullptr;
	delete copy;
}

void HiddenDagger::addEffects() {
	int dmg = 50;
	srand(chrono::system_clock::now().time_since_epoch().count());
	if (rand() % 100 + 1 <= this->critchance) {
		dmg *= this->crit;
	}
	this->effects.add(new FlatDmg(dmg));
	this->effects.add(new Cripple(8));
	this->effects.add(new Poison(30));
}