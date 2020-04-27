// 3Dポリゴン処理
#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Slime.h"
#include "Main.h"
#include "Texture.h"
#include "string.h"
#include "Battle.h"
#include "Hero.h"
#include "Boss.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;



extern nn::math::Vector3	g_posSlime(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_rotSlime(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_posSlimeHead(0.0f, 2.0f, 0.0f);
extern nn::math::Vector3	g_rotSlimeHead(0.0f, 0.0f, 0.0f);

extern bool fade_slime;
extern int random_enemy;

extern CSlime *sura;
extern CEnemy *mon;
extern CBattle *btl;
extern CHero *hero;
extern CBoss *boss;
// グローバル変数宣言------------------------------------------------
int appear_count = 0;
int change_count = 0;
int change_count2 = 0;
int flashing_count = 0;
int flashing_second = 0;
//-------------------------------------------------------------------

// スライムの初期値
CSlime::CSlime()
{
	strcpy(name, "スライム");
	hp = 5;
	mp = 0;
	atk = 2;
	def = 1;
	speed = 1;
	flash = false;
}

//　デストラクタ
CSlime::~CSlime()
{

}

void CSlime::InitSlime()
{	// 変数の初期化などあればここで行う
	g_posSlime = nn::math::Vector3(0.0f, 0.0f, 0.0f);
	g_rotSlime = nn::math::Vector3(0.0f, 0.0f, 0.0f);

	
}

void CSlime::UninitSlime()
{	// メモリの開放などあればここで行う
}

// 3Dポリゴン更新
void CSlime::UpdateSlime()
{
}

// 3Dポリゴン描画(上画面)
void CSlime::DrawSlime()
{
	if (GetFlashEnemy() == true)							//　攻撃を受けた敵は点滅する
	{
		if (flashing_count % 2 == 0 && flashing_second <= 15)		//　点滅時間
		{
			flashing_count++;
			flashing_second++;

			Change_2D();

			nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texsuraimu);
			nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

			CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
			DrawPolygonMain(4, 0);			// ポリゴン表示（三角形をデータ０から）
			this->slime_draw = true;

			if (random_enemy == 1 && change_count == 0)				//点滅する敵の指定
			{
				change_count++;
//				ChangeBMP(s_texsuraimu, "suraimu.bmp");
			}

			if (random_enemy == 2 && change_count == 0)				//点滅する敵の指定
			{
				change_count++;
//				ChangeBMP(s_texsuraimu, "doriruman.bmp");

			}


			if (random_enemy == 3 && change_count == 0)				//点滅する敵の指定
			{
				change_count++;
//				ChangeBMP(s_texsuraimu, "bee.bmp");
			}
		}
		else if(flashing_second > 15)							　　//点滅時間経過判定
		{
			flashing_second = 0;
			SetFlashFalse();
			flashing_count++;
		}
		else if(flashing_count % 2 != 0)						　 //奇数or偶数
		{
			flashing_count++;
		}
	}
	else
	{
		flashing_second = 0;
		Change_2D();

		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texsuraimu);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
		DrawPolygonMain(4, 0);			// ポリゴン表示（三角形をデータ０から）
		this->slime_draw = true;
		
		if (random_enemy == 1 && change_count == 0)　　　　　　　　　　　　　　　　　　//　スライムの描画
		{
			change_count++;
			ChangeTGA(s_texsuraimu, "suramu.tga");
		}

		if (random_enemy == 2 && change_count == 0)								//　ドリルマンの描画
		{
			change_count++;
			ChangeTGA(s_texsuraimu, "doriruman.tga");

		}


		if (random_enemy == 3 && change_count == 0)								//　ビーの描画
		{
			change_count++;
			ChangeTGA(s_texsuraimu, "bee.tga");
		}

	}

}



// 3Dポリゴン描画(下画面)
void CSlime::DrawSlimeSub()
{

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texsuraimu);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// ポリゴン表示位置セット
	DrawPolygonMain(4, 0);			// ポリゴン表示（三角形をデータ０から）
}

 // スライムの表示直前
void CSlime::DrawSlime_apper()
{
	appear_count++;
	if (appear_count > 120)
	{
		sura-> SetfalseAppear();
	}
		
	if (sura->GetIsAppear() == true)
	{
		
		Change_2D();
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texsurasura);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// ポリゴン表示位置セット
		DrawPolygonMain(4, 88);			// ポリゴン表示（三角形をデータ０から
		if (random_enemy == 1 && change_count2 == 0)
		{
			change_count2++;
			ChangeBMP(s_texsurasura,"suramu.bmp");
		}

		if (random_enemy == 2 && change_count2 == 0)
		{
			change_count2++;
			ChangeBMP(s_texsurasura, "doriman.bmp");
		}


		if (random_enemy == 3 && change_count2 == 0)
		{
			change_count2++;
			ChangeBMP(s_texsurasura, "beekun.bmp");
		}
	}
}

//　死亡判定
void CSlime::Destroy()
{
	slime_draw = false;
	is = false;
	fade_slime = false;
	appear_count = 0;
	hero -> LVUP();
	change_count = 0;
	change_count2 = 0;
}

//　ダメージ計算後のヒーローのHP
void CSlime::Attack()
{
	hero->SetHpHero(sura ->Attack_Calculation());
}

//　ヒーローのダメージ計算
int CSlime::Attack_Calculation()
{
	return (hero->GetHpHero() - sura->GetAtkSlime());
}

//　スライムが描画されているかどうかの変数を返す
int CSlime::GetIsSlime()
{
	return this->is;
}

//　スライムが存在していることを変数に代入
void CSlime::SetTrueSlime()
{
	this->is = true;
}

//　スライムが描画されているかどうかを返す
int CSlime::GetDrawSlime()
{
	return this->slime_draw;
}

//　スライム出現前の画像の描画ができているかを表す変数を返す
int CSlime::GetIsAppear()
{
	return this->slime_appear_draw;
}

//　スライム出現前の描画ができていることを変数に代入
void CSlime::SetTrueAppear()
{
	this->slime_appear_draw = true;
}

//　スライム出現まえの描画ができていないことを変数に代入
void CSlime::SetfalseAppear()
{
	this->slime_appear_draw = false;
}

//　スライムの速度を入手
int CSlime::GetSpeedSlime()
{
	return this->speed;
}

//　スライムのHPを返す
int CSlime::GetHpSlime()
{
	return this->hp;
}
y
//　スライムのHPをセット
void CSlime::SetHpSlime(int hp)
{
	this -> hp = hp;
}

//　スライムの攻撃力を返す
int CSlime::GetAtkSlime()
{
	return this->atk;
}

//　点滅しているかどうかの変数を返す
int CSlime::GetFlashEnemy()
{
	return this->flash;
}

//　点滅していないことを変数に代入
void CSlime::SetFlashFalse()
{
	flash = false;
}

//　点滅していることを変数に代入
void CSlime::SetFlashTrue()
{
	flash = true;
}


// 位置取得
nn::math::Vector3 CSlime::GetPosSlime()
{
	return g_posSlime;
}

nn::math::Vector3 CSlime::GetRotSlime()
{
	return g_rotSlime;
}


//--------------------------------------------------------------
// 矩形描画 上画面									先生のコード
//--------------------------------------------------------------
void FillRectMainSlime(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
// 矩形描画 下画面									先生のコード
//--------------------------------------------------------------
void FillRectSubSlime(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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

