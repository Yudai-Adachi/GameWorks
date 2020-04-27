#pragma once
#ifndef ___H_BEE
#define ___H_BEE
#include <nn/os.h>
#include "Enemy.h"
#include "Land.h"

class CBee
{
public:

	CBee();										//???????

	~CBee();									//??????

	void InitBee();								//???
	
	void Attack();								// ??????????
	
	int GetSpeedBee();							//????????

	void SetHpBee(int hp);						//????HP???
	int GetHpBee();								//?HP???
	int GetAtkBee();							//???????
	int Attack_Calculation();					// ??????????

	nn::math::Vector3 GetPosBee();				// ????
	nn::math::Vector3 GetRotBee();				// ????


////////////////////////????/////////////////////////////////
private:
	char name[10];
	int hp;
	int mp;
	int atk;
	int def;
	int speed;

	bool is;
	bool bee_draw;
	bool bee_appear_draw;
};

#endif
