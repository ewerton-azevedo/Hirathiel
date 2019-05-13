#pragma once
#include "GenericList.hpp"
#include "CombatAction.hpp"
#include "MobList.hpp"
#include "Stack.hpp"

class CombatActionList{
public:
	CombatActionList();
	~CombatActionList();

	void add(CombatAction* add);
	void clear();
	void draw();
	void hit(MobList* mobs);

	
protected:
	Stack<CombatAction> list;
};