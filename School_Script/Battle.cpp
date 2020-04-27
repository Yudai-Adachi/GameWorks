#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Battle.h"
#include "Slime.h"
#include "Main.h"
#include "Texture.h"
#include "string.h"
#include "Boss.h"
//-----------------------------------------------------------------------------------------------
//マクロ定義

#define TATAKAU         0
#define MAHOU           1
#define DOUGU           2
#define NIGERU          3

//------------------------先生のコード-------------------------------------------------------------------------

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;
//--------------------------END------------------------------------------------------------------------------

//　グローバル変数宣言----------------------------------------------------------------------------
extern nn::math::Vector3	g_posbattle(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_rotbattle(0.0f, 0.0f, 0.0f);
//-----------------------------------------------------------------------------------------------

// インスタンス化--------------------------------------------------------------------------------
extern CSlime *sura;
extern CEnemy *mon;
extern CBoss *boss;
//-----------------------------------------------------------------------------------------------

//　二次元に変換して描画
void CBattle::DrawCommand()
{
	Change_2D();

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcommand);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
	DrawPolygonMain(4, 96);			// ポリゴン表示（三角形をデータ０から）
}

// 戦闘中のカーソルの表示
void CBattle::DrawCursor(int number)
{
	Change_2D();

	switch (number)
	{
	case TATAKAU:
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcursor);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
		DrawPolygonMain(4, 100);			// ポリゴン表示（三角形をデータ０から）
		break;

	case MAHOU:
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcursor);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
		DrawPolygonMain(4, 104);			// ポリゴン表示（三角形をデータ０から）
		break;

	case DOUGU:
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcursor);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
		DrawPolygonMain(4, 108);			// ポリゴン表示（三角形をデータ０から）
		break;

	case NIGERU:
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcursor);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
		DrawPolygonMain(4, 112);			// ポリゴン表示（三角形をデータ０から）
		break;
	}
}

//　コンストラクタ
CBattle::CBattle()
{
}

//　デストラクタ
CBattle::~CBattle()
{
}
