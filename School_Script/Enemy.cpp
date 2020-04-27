#include <nn/gd.h>
#include <nn/snd.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include <nn/math.h>
#include "Enemy.h"
#include "Main.h"
#include "Texture.h"
#include "Polygon3D.h"
#include "Status.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;

int count_Enemy[4] = {0,0,0,0};
int random_Enemy[4] = {0,0,0,0};
int random_Enemy_pos_x = 0;
int random_Enemy_pos_y = 0;
extern nn::math::Vector3	g_rotPolygon3D;

nn::math::MersenneTwister g_Mer;			//�@�����p

//-----------------------------------------------------------------------------------------

void CEnemy::UninitEnemy3D()
{	// �������̊J���Ȃǂ���΂����ōs��
	g_Mer.Finalize();
}

// �����o�����O
void CEnemy::DrawMonster_appear()
{

	Change_2D();
	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texmonster);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonMain(4, 4);			// �|���S���\���i�O�p�`���f�[�^�O����j
}


//--------------------------------------------------------------
// ��`�`�� ����									�搶�̃R�[�h
//--------------------------------------------------------------
void FillRectMainEnemy3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
{
	//Texture combiner
	nn::gd::CombinerDescription combiner;
	combiner.ToDefault();

	// ���̏��@TextureColor + �萔 + �萔
	combiner.SetSourceRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT);
	// ���̏��@TextureAlpha + �萔 + �萔
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
// ��`�`�� �����									�搶�̃R�[�h
//--------------------------------------------------------------
void FillRectSubEnemy3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
{
	nn::gd::CombinerDescription combiner;
	combiner.ToDefault();

	// ���̏��@TextureColor + �萔 + �萔
	combiner.SetSourceRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT,
							nn::gd::CombinerStage::SOURCE_CONSTANT);
	// ���̏��@TextureAlpha + �萔 + �萔
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
