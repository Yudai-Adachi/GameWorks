#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Status.h"
#include "Main.h"
#include "Texture.h"
#include "Polygon3D.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;

static int			g_nAlpha = 255;	// 不透明度

extern nn::math::Vector3	g_posStatus(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_rotStatus(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_posStatusHead(0.0f, 2.0f, 0.0f);
extern nn::math::Vector3	g_rotStatusHead(0.0f, 0.0f, 0.0f);


void InitStatus()
{	// 変数の初期化などあればここで行う
	g_posStatus = nn::math::Vector3(0.0f, 0.0f, 0.0f);
	g_rotStatus = nn::math::Vector3(0.0f, 0.0f, 0.0f);
}

void UninitStatus()
{	// メモリの開放などあればここで行う
}

/*
// 3Dポリゴン更新
void UpdateStatus()
{
		g_posStatus = GetPosPolygon3D() + nn::math::Vector3(0.0f, 4.0f, 0.0f);

	// 毎フレームの更新処理をここで行う
	if (padStatus.hold & nn::hid::BUTTON_RIGHT)	g_rotStatus.y -= 1.0f;
	if (padStatus.hold & nn::hid::BUTTON_LEFT)	g_rotStatus.y += 1.0f;
	if (padStatus.hold & nn::hid::BUTTON_UP)
	{
		g_posStatus.z += nn::math::CosDeg(g_rotStatus.y) * 1.0f;
		g_posStatus.x += nn::math::SinDeg(g_rotStatus.y) * 1.0f;
	}
	if (padStatus.hold & nn::hid::BUTTON_DOWN)
	{
		g_posStatus.z -= nn::math::CosDeg(g_rotStatus.y) * 1.0f;
		g_posStatus.x -= nn::math::SinDeg(g_rotStatus.y) * 1.0f;
	}
	if (padStatus.hold & nn::hid::BUTTON_R)	g_rotStatusHead.y -= 1.0f;
	if (padStatus.hold & nn::hid::BUTTON_L)	g_rotStatusHead.y += 1.0f;

	if (padStatus.hold & nn::hid::BUTTON_EMULATION_UP)		g_posStatus.y += 1.0f;
	if (padStatus.hold & nn::hid::BUTTON_EMULATION_DOWN)	g_posStatus.y -= 1.0f;
	if (padStatus.trigger & nn::hid::BUTTON_A)
	if (padStatus.trigger & nn::hid::BUTTON_X)
	{
		g_posStatus.y -= 3.0f;
	}

	if (padStatus.trigger & nn::hid::BUTTON_B)
	{
		g_posStatus.y += 3.0f;
	}

	/*
	if( padStatus.hold & nn::hid::BUTTON_R )
	{
	if( padStatus.hold & nn::hid::BUTTON_X )		g_rotStatus.x += 1.0f;
	else if( padStatus.hold & nn::hid::BUTTON_Y )	g_rotStatus.y += 1.0f;
	else											g_rotStatus.z += 1.0f;
	}
	if( padStatus.hold & nn::hid::BUTTON_L )
	{
	if( padStatus.hold & nn::hid::BUTTON_X )		g_rotStatus.x -= 1.0f;
	else if( padStatus.hold & nn::hid::BUTTON_Y )	g_rotStatus.y -= 1.0f;
	else											g_rotStatus.z -= 1.0f;
	}
	*/

}
*/

// 3D主人公描画上画面)
void DrawStatus()
{
	CreateMatrix3D(g_posStatus, g_rotStatus, nn::math::Vector3(1.0f, 1.0f, 1.0f), true);

	nn::math::Matrix34 tempMtx;
	if (g_nAlpha) {
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texrabbit);
		tempMtx = CreateMatrix3D(g_posStatus, g_rotStatus, nn::math::Vector3(1.0f, 1.0f, 1.0f));
		DrawPolygonMain(4, 24, true);
		DrawPolygonMain(4, 28, true);
		DrawPolygonMain(4, 32, true);
		DrawPolygonMain(4, 36, true);
		DrawPolygonMain(4, 40, true);
		DrawPolygonMain(4, 44, true);
	}

	if (g_nAlpha) {
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texrabbit);
		CreateMatrix3DHierarchy(tempMtx, g_posStatusHead, g_rotStatusHead, nn::math::Vector3(1.0f, 1.0f, 1.0f));
		DrawPolygonMain(4, 48, true);
		DrawPolygonMain(4, 52, true);
		DrawPolygonMain(4, 56, true);
		DrawPolygonMain(4, 60, true);
		DrawPolygonMain(4, 64, true);
		DrawPolygonMain(4, 68, true);
	}
}



// 3Dポリゴン描画(下画面)
void DrawStatusSub()
{
	if (g_nAlpha) {
		CreateMatrix3D(g_posStatus, g_rotStatus, nn::math::Vector3(1.0f, 1.0f, 1.0f));
		DrawPolygonSub(4, 16);
	}
}

// 位置取得
nn::math::Vector3 GetPosStatus()
{
	return g_posStatus;
}

nn::math::Vector3 GetRotStatus()
{
	return g_rotStatus;
}

//--------------------------------------------------------------
// 矩形描画 上画面								先生のコード
//--------------------------------------------------------------
void FillRectMainStatus(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
void FillRectSubStatus(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
}
