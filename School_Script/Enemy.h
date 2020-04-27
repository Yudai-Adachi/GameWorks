// 3D表示ポリゴン定義
#ifndef ___H_ENEMY3D
#define ___H_ENEMY3D
#include <nn/os.h>

#define MAX_ENEMY 5
extern nn::math::MersenneTwister g_Mer;

class CEnemy
{
public:
	void UninitEnemy3D();					//　事後処理

	// ポリゴン表示（ただし、フェードで使われていたものなので今回は使わない）
	void FillRectMainEnemy3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA);
	void FillRectSubEnemy3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA);

	void DrawMonster_appear();				//　魔物出現直前

private:

};
#endif
