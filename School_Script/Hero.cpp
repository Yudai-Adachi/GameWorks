#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Hero.h"
#include "Main.h"
#include "Texture.h"
#include "Battle.h"
#include "Slime.h"
#include "Boss.h"
#include "Doriruman.h"
#include "Bee.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;

static int			g_nAlpha = 255;	// 不透明度

extern nn::math::Vector3	g_posHero(0.0f,0.0f,0.0f);
extern nn::math::Vector3	g_rotHero(0.0f,0.0f,0.0f);
extern nn::math::Vector3	g_posHeroHead(0.0f,2.0f,0.0f);
extern nn::math::Vector3	g_rotHeroHead(0.0f,0.0f,0.0f);


extern nn::gd::VertexBufferResource* bufferIndexHero;
extern nn::gd::VertexBufferResource* bufferCoordHero;
extern nn::gd::VertexBufferResource* bufferTexCoordHero;

extern int g_stage;
extern int music_count;
extern s32 g_fadeout;
extern int change_count;
extern int change_count2;

//　インスタンス化
extern CSlime *sura;
extern CEnemy *mon;
extern CBattle *btl;
extern CHero *hero;
extern CBoss *boss;
extern CDoriruman *dori;
extern CBee *bee;

//--------------------------------------------------------------------------------

CHero::CHero()
{
	strcpy(name, "勇者");
	hp = 100;
	mp = 20;
	atk = 3;
	def = 10;
	speed = 6;
	lv = 1;
	ex = 0;
}

void CHero::InitHero()
{	// 変数の初期化などあればここで行う
	g_posHero = nn::math::Vector3(0.0f,0.0f,0.0f);
	g_rotHero = nn::math::Vector3(0.0f,0.0f,0.0f);
}

void CHero::UninitHero()
{	// メモリの開放などあればここで行う
}

// 3Dポリゴン更新
void CHero::UpdateHero()
{
}

void CHero::DrawHero_2D()
{
	// ステータス表示
		Change_2D();
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texstatus);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// ポリゴン表示位置セット
		DrawPolygonMain(4, 92);			// ポリゴン表示（三角形をデータ０から）
}

void CHero::DrawHero_2D_second()
{
	// ステータス表示
		Change_2D();
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texstatus);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// ポリゴン表示位置セット
		DrawPolygonMain(4, 92);			// ポリゴン表示（三角形をデータ０から）
}

//　経験値表示
void CHero::DrawExperience()
{
	Change_2D();
	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texexperience);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// ポリゴン表示位置セット
	DrawPolygonMain(4, 140);			// ポリゴン表示（三角形をデータ０から）
}

//　残りHPの表示
void CHero::DrawHero_damage()
{
	Change_2D();
	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texhero_damage);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// ポリゴン表示位置セット
	DrawPolygonMain(4, 144);			// ポリゴン表示（三角形をデータ０から）
}

// 3Dポリゴン描画(下画面)
void CHero::DrawHeroSub()
{
	if (g_nAlpha) {
		CreateMatrix3D( g_posHero, g_rotHero, nn::math::Vector3(1.0f,1.0f,1.0f) );
		DrawPolygonSub(4,16);
	}
}

//----------------------- 先生のソースコード ----------------------------------------------
void CHero::SetHero()
{
	nn::gd::VertexBufferResource* buffers[2] = { bufferCoordHero, bufferTexCoordHero };
	u32 offsets[] = {0, 0};
	nn::gd::VertexInputStage::SetVertexBuffers(0, 2, buffers, offsets);
	nn::gd::VertexInputStage::SetIndexBuffer(bufferIndexHero, nn::gd::VertexInputStage::INDEX_FORMAT_USHORT, 0);
}
//-----------------------------END-------------------------------------------------------

//　死亡処理
void CHero::Destroy()
{
	delete hero;
	g_fadeout = 1;
	g_stage = 6;
	change_count = 0;
	change_count2 = 0;
}

//　レベルアップ時のステータスの変化と効果音
void CHero::LVUP()
{
	if (GetLvHero() == 1 && GetExHero() >= 3)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(2);
		SetHpHero(103);
		mp = 22;
		atk = 5;
		def = 13;
		speed = 7;
	}

	if (GetLvHero() == 2 && GetExHero() >= 10)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(3);
		SetHpHero(105);
		mp = 23;
		atk = 6;
		def = 14;
		speed = 8;
	}

	if (GetLvHero() == 3 && GetExHero() >= 20)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(4);
		SetHpHero(107);
		mp = 25;
		atk = 7;
		def = 15;
		speed = 9;
	}

	if (GetLvHero() == 4 && GetExHero() >= 35)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(5);
		SetHpHero(109);
		mp = 26;
		atk = 8;
		def = 16;
		speed = 10;
	}

	if (GetLvHero() == 5 && GetExHero() >= 60)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(6);
		SetHpHero(112);
		mp = 27;
		atk = 9;
		def = 17;
		speed = 11;
	}

	if (GetLvHero() == 6 && GetExHero() >= 90)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(7);
		SetHpHero(115);
		mp = 28;
		atk = 10;
		def = 18;
		speed = 12;
	}

	if (GetLvHero() == 7 && GetExHero() >= 135)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(8);
		SetHpHero(119);
		mp = 29;
		atk = 12;
		def = 20;
		speed = 13;
	}

	if (GetLvHero() == 8 && GetExHero() >= 170)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(9);
		SetHpHero(123);
		mp = 30;
		atk = 13;
		def = 19;
		speed = 14;
	}

	if (GetLvHero() == 9 && GetExHero() >= 215)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(10);
		SetHpHero(127);
		mp = 33;
		atk = 16;
		def = 20;
		speed =17;
	}

	if (GetLvHero() == 10 && GetExHero() >= 250)
	{
		app.SetSoundState(5, 0, 5, 0);
		SetLvHero(2);
		SetHpHero(140);
		mp = 35;
		atk = 18;
		def = 22;
		speed = 19;
	}
}

//　スライムが攻撃された後のHPセット
void CHero::AttackHero_slime()
{
	sura->SetHpSlime(hero->Attack_Calculation_slime());
}

//　スライムの攻撃時のダメージ計算をして値を返す
int CHero::Attack_Calculation_slime()
{
	return (sura -> GetHpSlime() - hero->GetAtkHero());
}

//　ドリルマンが攻撃された後のHPセット
void CHero::AttackHero_doriruman()
{
	dori->SetHpDoriruman(hero->Attack_Calculation_doriruman());
}

//　ドリルマンの攻撃時のダメージ計算をして値を返す
int CHero::Attack_Calculation_doriruman()
{
	return (dori->GetHpDoriruman() - hero->GetAtkHero());
}

//　ビーが攻撃された後のHPセット
void CHero::AttackHero_bee()
{
	bee->SetHpBee(hero->Attack_Calculation_bee());
}

//　ビーの攻撃時のダメージ計算をして値を返す
int CHero::Attack_Calculation_bee()
{
	return (bee->GetHpBee() - hero->GetAtkHero());
}

//　ボスが攻撃された後のHPセット
void CHero::AttackHero_boss()
{
	boss->SetHpBoss(hero->Attack_Calculation_boss());
}

//　ボスの攻撃時のダメージ計算をして値を返す
int CHero::Attack_Calculation_boss()
{
	return (boss->GetHpBoss() - hero->GetAtkHero());
}

//　ヒーローの速度を返す
int CHero::GetSpeedHero()
{
	return this->speed;
}

//　ヒーローのHPを返す
int CHero::GetHpHero()
{
	return this->hp;
}

//　ヒーローのHPをセット
void CHero::SetHpHero(int hp)
{
	this->hp = hp;
}

//　ヒーローのMPを返す
int CHero::GetMpHero()
{
	return this->mp;
}

//　ヒーローのMPをセットする
void CHero::SetMpHero(int mp)
{
	this->mp = mp;
}

//　ヒーローの攻撃力を返す
int CHero::GetAtkHero()
{
	return this->atk;
}

//　ヒーローのレベルを返す
int CHero::GetLvHero()
{
	return this->lv;
}

//　ヒーローのレベルをセットする
void CHero::SetLvHero(int lv)
{
	this->lv = lv;
}

//　ヒーローの取得した経験値を返す
int CHero::GetExHero()
{
	return this->ex;
}

//　ヒーローの総合経験値を計算する
void CHero::AddExHero(int ex)
{
	this->ex += ex;
}

//　ヒーローの総合経験値を計算する
void CHero::SetExHero(int ex)
{
	this->ex += ex;
}

 // 位置取得
nn::math::Vector3 GetPosHero()
{
	return g_posHero;
}

nn::math::Vector3 GetRotHero()
{
	return g_rotHero;
}

//--------------------------------------------------------------
// 矩形描画 上画面								先生のコード
//--------------------------------------------------------------
void FillRectMainHero(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
{
	//Texture combiner
	nn::gd::CombinerDescription combiner;
	combiner.ToDefault();

	// 下の情報　TextureColor + 定数 + 定数
	combiner.SetSourceRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT);
	// 下の情報　TextureAlpha + 定数 + 定数
	combiner.SetSourceAlpha(nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT);

	combiner.SetOperandRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR);

	combiner.SetOperandAlpha(nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA);

	combiner.SetCombineRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::COMBINE_RGB_REPLACE);

	combiner.SetCombineAlpha(nn::gd::CombinerStage::UNIT0,
							 nn::gd::CombinerStage::COMBINE_ALPHA_REPLACE);

	combiner.SetCombinerInUse(nn::gd::CombinerStage::UNIT0, GD_TRUE);

	nn::gd::CombinerState* texComState;
	nn::gd::CombinerStage::CreateTextureCombinerState(&combiner, &texComState);
	nn::gd::CombinerStage::SetTextureCombinerUnitConstantColor(nn::gd::CombinerStage::UNIT0,
		colorR, colorG, colorB, colorA);
	nn::gd::CombinerStage::SetTextureCombinerState(texComState);

	nn::gd::VertexBufferResource* buffers[] = {bufferCoord, bufferTexCoord};
	u32 offsets[] = {0, 0};
	nn::gd::VertexInputStage::SetVertexBuffers(0, 2, buffers, offsets);

	nn::gd::System::DrawIndexed(4, 16);

	nn::gd::CombinerStage::ReleaseTextureCombinerState(texComState);
}

//--------------------------------------------------------------
// 矩形描画 下画面								先生のコード
//--------------------------------------------------------------
void FillRectSubHero(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
{
	nn::gd::CombinerDescription combiner;
	combiner.ToDefault();

	// 下の情報　TextureColor + 定数 + 定数
	combiner.SetSourceRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT);
	// 下の情報　TextureAlpha + 定数 + 定数
	combiner.SetSourceAlpha(nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT);

	combiner.SetOperandRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR);

	combiner.SetOperandAlpha(nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA);

	combiner.SetCombineRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::COMBINE_RGB_REPLACE);

	combiner.SetCombineAlpha(nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::COMBINE_ALPHA_REPLACE);

	combiner.SetCombinerInUse(nn::gd::CombinerStage::UNIT0, GD_TRUE);

	nn::gd::CombinerState* texComState;
	nn::gd::CombinerStage::CreateTextureCombinerState(&combiner, &texComState);
	nn::gd::CombinerStage::SetTextureCombinerUnitConstantColor(nn::gd::CombinerStage::UNIT0,
		colorR, colorG, colorB, colorA);
	nn::gd::CombinerStage::SetTextureCombinerState(texComState);

	nn::gd::VertexBufferResource* buffers[] = {bufferCoord, bufferTexCoord};
	u32 offsets[] = {0, 0};
	nn::gd::VertexInputStage::SetVertexBuffers(0, 2, buffers, offsets);

	nn::gd::System::DrawIndexed(4, 8);

	nn::gd::CombinerStage::ReleaseTextureCombinerState(texComState);
	/* プリミティブの指定 */
	nn::gd::VertexInputStage::SetPrimitiveTopology(nn::gd::VertexInputStage::PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
}

