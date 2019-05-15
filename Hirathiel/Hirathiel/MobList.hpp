#pragma once
#include "MobListObject.hpp"
#include "MoB.hpp"
#include <SDL.h>
#include "Object.hpp"
#include "GenericList.hpp"
#include "CombatAction.hpp"
#include <mutex>

class MobList: public GenericList{
public:
	MobList();
	~MobList();
	void add(MobListObject* add);
	void draw();
	void triggerEffects(std::mutex* moblock);
	int getScore() { return this->score; };

private:
	int score;
};
