#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Boss.h"
#include "Main.h"
#include "Texture.h"
#include "string.h"
#include "Battle.h"
#include "Hero.h"
#include "Polygon3D.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;


static int			g_nAlpha = 255;	// 不透明度

extern nn::math::Vector3	g_posBoss(45.0f, 70.0f, 2.0f);
extern nn::math::Vector3	g_rotBoss(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_posPolygon3D;
extern nn::math::Vector3	g_rotPolygon3D;
extern bool fade_boss;
extern int g_stage;
extern s32 g_fadeout;

extern CBoss *boss;
extern CEnemy *mon;
extern CBattle *btl;
extern CHero *hero;
// グローバル変数宣言------------------------------------------------
int appear_count1 = 0;
//-------------------------------------------------------------------

// ボスの初期値
CBoss::CBoss()
{
	strcpy(name, "ゾーマ");
	hp = 1;
	mp = 10;
	atk = 20;
	def = 15;
	speed = 12;
}

//コンストラクタ
CBoss::~CBoss()
{

}

void CBoss::InitBoss()
{	// 変数の初期化などあればここで行う
	
}

void CBoss::UninitBoss()
{	// メモリの開放などあればここで行う
}

// 3Dポリゴン更新
void CBoss::UpdateBoss()
{
}

// 3Dポリゴン描画(上画面)
void CBoss::DrawChangeBoss()
{
	ChangeBMP(s_texsuraimu, "boss.bmp");
	this->boss_draw = true;
}



// 3Dポリゴン描画(下画面)
void CBoss::DrawBossSub()
{

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texboss);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
	DrawPolygonMain(4, 0);			// ポリゴン表示（三角形をデータ０から）
}

// スライムの表示直前
void CBoss::DrawBoss_apper()
{
	appear_count1++;
	if (appear_count1 > 120)
	{
		boss->SetfalseAppear();
	}

	if (boss->GetIsAppear() == true)
	{

		Change_2D();
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texboss);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// ポリゴン表示位置セット
		DrawPolygonMain(4, 87);			// ポリゴン表示（三角形をデータ０から
	}
}

//　フィールドにボスをビルボードで描画
void CBoss::DrawBoss()
{
	g_posPolygon3D = GetPosPolygon3D();
	Change_3D();
	if (g_nAlpha) {
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texboss_final);
		CreateMatrix3D(g_posBoss, g_rotBoss, nn::math::Vector3(1.0f, 1.0f, 1.0f), true);
		DrawPolygonMain(4, 128, true);
	}
}

//　戦闘時のラスボス描画
void CBoss::DrawBossFinal()
{
	Change_2D();

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texboss_final);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
	DrawPolygonMain(4, 132);			// ポリゴン表示（三角形をデータ０から）
}

//　死亡判定
void CBoss::Destroy()
{
	boss_draw = false;
	is = false;
	fade_boss = false;
	delete boss;
	g_fadeout = 1;
	g_stage = 5;
}

//　攻撃後の残りHPをセット
void CBoss::Attack()
{
	hero->SetHpHero(boss->Attack_Calculation());
}

//　攻撃時のダメージ計算
int CBoss::Attack_Calculation()
{
	return (hero->GetHpHero() - boss->GetAtkBoss());
}

//　ボスの存在確認の変数を返す
int CBoss::GetIsBoss()
{
	return this->is;
}

//　ボスの存在ありの変更
void CBoss::SetTrueBoss()
{
	this->is = true;
}

//　ボスの存在なしに変更
void CBoss::SetFalseBoss()
{
	this->is = false;
}

//　ボスの存在確認の変数を返す
int CBoss::GetDrawBoss()
{
	return this->boss_draw;
}

//　ボスの出現確認の変数を返す
int CBoss::GetIsAppear()
{
	return this->boss_appear_draw;
}

//　ボスの出現の変数にOKを出す
void CBoss::SetTrueAppear()
{
	this->boss_appear_draw = true;
}

//　ボスの出現の変数にNoを出す
void CBoss::SetfalseAppear()
{
	this->boss_appear_draw = false;
}

//　ボスの速度を取得
int CBoss::GetSpeedBoss()
{
	return this->speed;
}

//　ボスのHPを取得
int CBoss::GetHpBoss()
{
	return this->hp;
}

//　ボスのHPをセット
void CBoss::SetHpBoss(int hp)
{
	this->hp = hp;
}

//　ボスの攻撃力を返す
int CBoss::GetAtkBoss()
{
	return this->atk;
}



// 位置取得
nn::math::Vector3 CBoss::GetPosBoss()
{
	return g_posBoss;
}

nn::math::Vector3 CBoss::GetRotBoss()
{
	return g_rotBoss;
}


//--------------------------------------------------------------
// 矩形描画 上画面             先生のコード
//--------------------------------------------------------------
void FillRectMainBoss(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
{
	//Texture combiner
	nn::gd::CombinerDescription combiner;
	combiner.ToDefault();

	// 下の情報　TextureColor + 定数 + 定数
	combiner.SetSourceRGB(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT);
	// 下の情報　TextureAlpha + 定数 + 定数
	combiner.SetSourceAlpha(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT);

	combiner.SetOperandRGB(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,
		nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,
		nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR);

	combiner.SetOperandAlpha(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,
		nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,
		nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA);

	combiner.SetCombineRGB(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::COMBINE_RGB_REPLACE);

	combiner.SetCombineAlpha(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::COMBINE_ALPHA_REPLACE);

	combiner.SetCombinerInUse(nn::gd::CombinerStage::UNIT0, GD_TRUE);

	nn::gd::CombinerState* texComState;
	nn::gd::CombinerStage::CreateTextureCombinerState(&combiner, &texComState);
	nn::gd::CombinerStage::SetTextureCombinerUnitConstantColor(nn::gd::CombinerStage::UNIT0,
		colorR, colorG, colorB, colorA);
	nn::gd::CombinerStage::SetTextureCombinerState(texComState);

	nn::gd::VertexBufferResource* buffers[] = { bufferCoord, bufferTexCoord };
	u32 offsets[] = { 0, 0 };
	nn::gd::VertexInputStage::SetVertexBuffers(0, 2, buffers, offsets);

	nn::gd::System::DrawIndexed(4, 16);

	nn::gd::CombinerStage::ReleaseTextureCombinerState(texComState);
}

//--------------------------------------------------------------
// 矩形描画 下画面						先生のコード
//--------------------------------------------------------------
void FillRectSubBoss(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
{
	nn::gd::CombinerDescription combiner;
	combiner.ToDefault();

	// 下の情報　TextureColor + 定数 + 定数
	combiner.SetSourceRGB(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT);
	// 下の情報　TextureAlpha + 定数 + 定数
	combiner.SetSourceAlpha(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT);

	combiner.SetOperandRGB(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,
		nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,
		nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR);

	combiner.SetOperandAlpha(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,
		nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,
		nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA);

	combiner.SetCombineRGB(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::COMBINE_RGB_REPLACE);

	combiner.SetCombineAlpha(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::COMBINE_ALPHA_REPLACE);

	combiner.SetCombinerInUse(nn::gd::CombinerStage::UNIT0, GD_TRUE);

	nn::gd::CombinerState* texComState;
	nn::gd::CombinerStage::CreateTextureCombinerState(&combiner, &texComState);
	nn::gd::CombinerStage::SetTextureCombinerUnitConstantColor(nn::gd::CombinerStage::UNIT0,
		colorR, colorG, colorB, colorA);
	nn::gd::CombinerStage::SetTextureCombinerState(texComState);

	nn::gd::VertexBufferResource* buffers[] = { bufferCoord, bufferTexCoord };
	u32 offsets[] = { 0, 0 };
	nn::gd::VertexInputStage::SetVertexBuffers(0, 2, buffers, offsets);

	nn::gd::System::DrawIndexed(4, 8);

	nn::gd::CombinerStage::ReleaseTextureCombinerState(texComState);
	/* プリミティブの指定 */
	nn::gd::VertexInputStage::SetPrimitiveTopology(nn::gd::VertexInputStage::PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
}

