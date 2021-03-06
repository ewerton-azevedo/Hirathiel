#include "Bleed.hpp"
#include "MoB.hpp"
#include <SDL.h>

Bleed::Bleed(int time) :Effect((time), ((int)(time/1))) {
	this->dmg = 15;
	this->bleedTimer = new CTimer();
	this->firsttick = true;
}

void Bleed::init() {
	
}


Bleed::~Bleed() {
	delete this->bleedTimer;
}

void Bleed::copy(Effect* effect){
	Bleed* copy = dynamic_cast<Bleed*>(effect);
	if (copy) {
		this->timing = effect->getTiming();
		this->ticks = effect->getTicks();
	}
	copy = nullptr; delete copy;
}

void Bleed::apply(Object* applicant){
	this->bleedTimer->updateElapsed();
	if (bleedTimer->getElapsed() >= 1 && ticks > 0) {
		dynamic_cast<MoB*>(applicant)->applyDmg(this->dmg);
		this->timing - bleedTimer->getElapsed();
		this->bleedTimer->update();
		this->ticks--;
	}

}