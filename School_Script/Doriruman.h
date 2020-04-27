#pragma once
#ifndef ___H_DORIRUMAN
#define ___H_DORIRUMAN
#include <nn/os.h>
#include "Enemy.h"
#include "Land.h"

class CDoriruman
{
public:

	CDoriruman();												//????????

	~CDoriruman();												//???????

	void InitDoriruman();										// ???
	
	void Attack();												//?????????????

	int GetSpeedDoriruman();									//??????

	void SetHpDoriruman(int hp);								//?HP??????
	int GetHpDoriruman();										//?HP???
	int GetAtkDoriruman();										//???????
	int Attack_Calculation();									//???????????

	nn::math::Vector3 GetPosDoriruman();						// ????
	nn::math::Vector3 GetRotDoriruman();						// ????


////////////////////////////////????/////////////////////////////////
private:
	char name[10];
	int hp;
	int mp;
	int atk;
	int def;
	int speed;

	bool is;
	bool doriruman_draw;
	bool doriruman_appear_draw;
};

#endif
