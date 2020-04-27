// �n�ʏ���
#include <nn/gd.h>
#include <nn/snd.h>
#include "Land.h"
#include "Main.h"
#include "Texture.h"
#include "slime.h"
#include "Boss.h"
#include "Polygon3D.h"
#include "Effect.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;

static int			g_nAlpha = 255;	// �s�����x
static nn::math::Vector3	g_posLand(0.0f,0.0f,0.0f);
static nn::math::Vector3	g_rotLand(0.0f,0.0f,0.0f);

extern nn::math::Vector3	g_posPolygon3D;
extern nn::math::Vector3	g_rotPolygon3D;

//�C���X�^���X��
extern CSlime *sura;
extern CEnemy *mon;
extern CBoss *boss;
CEffect *ef = new CEffect();


void InitLand()
{	// �ϐ��̏������Ȃǂ���΂����ōs��
	g_posLand = nn::math::Vector3(0.0f,0.0f,0.0f);
	g_rotLand = nn::math::Vector3(0.0f,0.0f,0.0f);
}

void UninitLand()
{	// �������̊J���Ȃǂ���΂����ōs��
}

// �n�ʍX�V
void UpdateLand()
{
	// ���t���[���̍X�V�����������ōs��
}

// �n�ʕ`��(����)
void DrawLand()
{
	g_posPolygon3D = GetPosPolygon3D();
	Change_3D();
	if (sura -> GetDrawSlime() == false)
	{
		if (g_nAlpha) {
				nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texLand);
				CreateMatrix3D(g_posLand, g_rotLand, nn::math::Vector3(1.0f, 1.0f, 1.0f));
				DrawPolygonMain(4, 120, true);
		}
		ef->BossStage();
		boss->DrawBoss();
	}
}

// �n�ʕ`��(�����)
void DrawLandSub()
{
	if (g_nAlpha) {
		CreateMatrix3D( g_posLand, g_rotLand, nn::math::Vector3(1.0f,1.0f,1.0f) );
		DrawPolygonSub(4,20);
	}
}
