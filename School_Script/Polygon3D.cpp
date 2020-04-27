// 3Dポリゴン処理
#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Polygon3D.h"
#include "Main.h"
#include "Texture.h"
#include "Slime.h"
#include "Boss.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;

int encounter = 0;
float gravity = -0.2f;
float vel = 0;
int random_Encount = 0;
static int			g_nAlpha = 255;	// 不透明度

extern nn::math::Vector3	g_posPolygon3D(0.0f,0.0f,0.0f);
extern nn::math::Vector3	g_rotPolygon3D(0.0f,0.0f,0.0f);
extern nn::math::Vector3	g_posPolygon3DHead(0.0f,2.0f,0.0f);
extern nn::math::Vector3	g_rotPolygon3DHead(0.0f,0.0f,0.0f);
extern bool fade_boss;
extern int g_stage;

//　インスタンス化
extern CSlime *sura;
extern CEnemy *mon;
extern CBoss *boss;

void InitPolygon3D()
{	// 変数の初期化などあればここで行う
	g_posPolygon3D = nn::math::Vector3(0.0f,0.0f,0.0f);
	g_rotPolygon3D = nn::math::Vector3(0.0f,0.0f,0.0f);
}

void UninitPolygon3D()
{	// メモリの開放などあればここで行う
}

// 3Dポリゴン更新
void UpdatePolygon3D()
{
	// 毎フレームの更新処理をここで行う
	if (padStatus.hold & nn::hid::BUTTON_RIGHT)		//　３DSで右を押したら
	{
		g_rotPolygon3D.y -= 1.0f;
	}
	if (padStatus.hold & nn::hid::BUTTON_LEFT)		//　3DSで左を押したら
	{
		g_rotPolygon3D.y += 1.0f;
	}
	if( padStatus.hold & nn::hid::BUTTON_UP)		//　3DSで上を押したら
	{
		encounter++;
		if (encounter >= 50)						//　50以上、上下に動いたら
		{
			Encounter();
		}
			if (Boss_CheckCollision3D(g_posPolygon3D, 2.0f) == true && sura ->GetIsSlime() == false)　　　//　ボスとの当たり判定
			{
				boss -> SetTrueBoss();
			}
		g_posPolygon3D.y += nn::math::CosDeg(g_rotPolygon3D.y) * 1.0f;									 //　キャラクターの方向転換
		g_posPolygon3D.x += nn::math::SinDeg(g_rotPolygon3D.y) * -1.0f;
		
		
	}
	if( padStatus.hold & nn::hid::BUTTON_DOWN )															 //　3DSで下を押したら
	{
		encounter++;
		if (encounter >= 50)
		{
			Encounter();
		}
			if (Boss_CheckCollision3D(g_posPolygon3D, 2.0f) == true && sura->GetIsSlime() == false)		//　ボスとの当たり判定
			{
				boss->SetTrueBoss();
			}
		g_posPolygon3D.y -= nn::math::CosDeg(g_rotPolygon3D.y) * 1.0f;									//　方向転換
		g_posPolygon3D.x -= nn::math::SinDeg(g_rotPolygon3D.y) * -1.0f;
	}

/*
	if( padStatus.hold & nn::hid::BUTTON_R)	g_rotPolygon3DHead.y -= 1.0f;
	if( padStatus.hold & nn::hid::BUTTON_L)	g_rotPolygon3DHead.y += 1.0f;

	if( padStatus.hold & nn::hid::BUTTON_EMULATION_UP)		g_posPolygon3D.y += 1.0f;
	if( padStatus.hold & nn::hid::BUTTON_EMULATION_DOWN)	g_posPolygon3D.y -= 1.0f;
	if( padStatus.trigger & nn::hid::BUTTON_A)
	
	if (padStatus.trigger & nn::hid::BUTTON_B)
	{
		vel = 2.0f;
	}

	vel += gravity;
	g_posPolygon3D.z += vel;
	if (g_posPolygon3D.z <= 0)
	{
		g_posPolygon3D.z = 0;
		vel = 0;
	}

	if( padStatus.trigger & nn::hid::BUTTON_X)
	{
		g_posPolygon3D.y += 3.0f;
	}

	if (padStatus.trigger & nn::hid::BUTTON_Y)
	{
		g_posPolygon3D.y -= 3.0f;
	}
	*/

	/*
	if( padStatus.hold & nn::hid::BUTTON_R )
	{
		if( padStatus.hold & nn::hid::BUTTON_X )		g_rotPolygon3D.x += 1.0f;
		else if( padStatus.hold & nn::hid::BUTTON_Y )	g_rotPolygon3D.y += 1.0f;
		else											g_rotPolygon3D.z += 1.0f;
	}
	if( padStatus.hold & nn::hid::BUTTON_L )
	{
		if( padStatus.hold & nn::hid::BUTTON_X )		g_rotPolygon3D.x -= 1.0f;
		else if( padStatus.hold & nn::hid::BUTTON_Y )	g_rotPolygon3D.y -= 1.0f;
		else											g_rotPolygon3D.z -= 1.0f;
	}
	*/
	
}

void Encounter()
{
	random_Encount = g_Mer.GenerateRandomN(100) + 1;					//　乱数生成
	if(random_Encount <= 5)												//　乱数が当たれば
	{
		sura->SetTrueSlime();
		encounter = 0;
	}
}

// 3Dポリゴン描画(上画面)
void DrawPolygon3D()
{
	Change_3D();
	nn::math::Matrix34 tempMtx;
	if (g_nAlpha) {
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texrabbit);
		tempMtx = CreateMatrix3D(g_posPolygon3D, g_rotPolygon3D, nn::math::Vector3(1.0f, 1.0f, 1.0f));
		DrawPolygonMain(4, 24, true);
		DrawPolygonMain(4, 28, true);
		DrawPolygonMain(4, 32, true);
		DrawPolygonMain(4, 36, true);
		DrawPolygonMain(4, 40, true);
		DrawPolygonMain(4, 44, true);
	}

	if (g_nAlpha) {
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texrabbit);
		CreateMatrix3DHierarchy(tempMtx, g_posPolygon3DHead, g_rotPolygon3DHead, nn::math::Vector3(1.0f, 1.0f, 1.0f));
		DrawPolygonMain(4, 48, true);
		DrawPolygonMain(4, 52, true);
		DrawPolygonMain(4, 56, true);
		DrawPolygonMain(4, 60, true);
		DrawPolygonMain(4, 64, true);
		DrawPolygonMain(4, 68, true);
	}
}



// 3Dポリゴン描画(下画面)
void DrawPolygon3DSub()
{
	if (g_nAlpha) {
		CreateMatrix3D( g_posPolygon3D, g_rotPolygon3D, nn::math::Vector3(1.0f,1.0f,1.0f) );
		DrawPolygonSub(4,16);
	}
}

//　フェードイン（アウト）用の変数をtrueにする
void Fade_True_Boss()
{
	fade_boss = true;
}

 // 位置取得
nn::math::Vector3 GetPosPolygon3D()
{
	return g_posPolygon3D;
}

nn::math::Vector3 GetRotPolygon3D()
{
	return g_rotPolygon3D;
}

//--------------------------------------------------------------
// 矩形描画 上画面										先生のコード
//--------------------------------------------------------------
void FillRectMainPolygon3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
// 矩形描画 下画面										先生のコード
//--------------------------------------------------------------
void FillRectSubPolygon3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
}
