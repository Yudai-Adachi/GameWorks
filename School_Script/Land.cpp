// 地面処理
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

static int			g_nAlpha = 255;	// 不透明度
static nn::math::Vector3	g_posLand(0.0f,0.0f,0.0f);
static nn::math::Vector3	g_rotLand(0.0f,0.0f,0.0f);

extern nn::math::Vector3	g_posPolygon3D;
extern nn::math::Vector3	g_rotPolygon3D;

//インスタンス化
extern CSlime *sura;
extern CEnemy *mon;
extern CBoss *boss;
CEffect *ef = new CEffect();


void InitLand()
{	// 変数の初期化などあればここで行う
	g_posLand = nn::math::Vector3(0.0f,0.0f,0.0f);
	g_rotLand = nn::math::Vector3(0.0f,0.0f,0.0f);
}

void UninitLand()
{	// メモリの開放などあればここで行う
}

// 地面更新
void UpdateLand()
{
	// 毎フレームの更新処理をここで行う
}

// 地面描画(上画面)
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

// 地面描画(下画面)
void DrawLandSub()
{
	if (g_nAlpha) {
		CreateMatrix3D( g_posLand, g_rotLand, nn::math::Vector3(1.0f,1.0f,1.0f) );
		DrawPolygonSub(4,20);
	}
}
