// 3D�\���|���S����`
#ifndef ___H_ENEMY3D
#define ___H_ENEMY3D
#include <nn/os.h>

#define MAX_ENEMY 5
extern nn::math::MersenneTwister g_Mer;

class CEnemy
{
public:
	void UninitEnemy3D();					//�@���㏈��

	// �|���S���\���i�������A�t�F�[�h�Ŏg���Ă������̂Ȃ̂ō���͎g��Ȃ��j
	void FillRectMainEnemy3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA);
	void FillRectSubEnemy3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA);

	void DrawMonster_appear();				//�@�����o�����O

private:

};
#endif
