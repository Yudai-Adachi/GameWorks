#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Doriruman.h"
#include "Main.h"
#include "Texture.h"
#include "string.h"
#include "Battle.h"
#include "Hero.h"
#include "Boss.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;

extern nn::math::Vector3	g_posDoriruman(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_rotDoriruman(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_posDorirumanHead(0.0f, 2.0f, 0.0f);
extern nn::math::Vector3	g_rotDorirumanHead(0.0f, 0.0f, 0.0f);

extern bool fade_slime;

extern CDoriruman *dori;
extern CEnemy *mon;
extern CBattle *btl;
extern CHero *hero;
extern CBoss *boss;

// �h�����}���̏����l
CDoriruman::CDoriruman()
{
	strcpy(name, "�h�����}��");
	hp = 21;
	mp = 5;
	atk = 3;
	def = 6;
	speed = 3;
}

//�@�f�X�g���N�^
CDoriruman::~CDoriruman()
{

}

void CDoriruman::InitDoriruman()
{	// �ϐ��̏������Ȃǂ���΂����ōs��
	g_posDoriruman = nn::math::Vector3(0.0f, 0.0f, 0.0f);
	g_rotDoriruman = nn::math::Vector3(0.0f, 0.0f, 0.0f);


}

//�@�U�����̌v�Z���ʂ��Z�b�g
void CDoriruman::Attack()
{
	hero->SetHpHero(dori->Attack_Calculation());
}

//�@�U�����̃_���[�W�v�Z
int CDoriruman::Attack_Calculation()
{
	return (hero->GetHpHero() - dori->GetAtkDoriruman());
}

//�@���x��Ԃ�
int CDoriruman::GetSpeedDoriruman()
{
	return this->speed;
}

//�@HP��Ԃ�
int CDoriruman::GetHpDoriruman()
{
	return this->hp;
}

//�@HP���Z�b�g����
void CDoriruman::SetHpDoriruman(int hp)
{
	this->hp = hp;
}

//�@�U���͂�Ԃ�
int CDoriruman::GetAtkDoriruman()
{
	return this->atk;
}

// �ʒu�擾
nn::math::Vector3 CDoriruman::GetPosDoriruman()
{
	return g_posDoriruman;
}

nn::math::Vector3 CDoriruman::GetRotDoriruman()
{
	return g_rotDoriruman;
}


//--------------------------------------------------------------
// ��`�`�� ����							�搶�̃R�[�h
//--------------------------------------------------------------
void FillRectMainDoriruman(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
{
	//Texture combiner
	nn::gd::CombinerDescription combiner;
	combiner.ToDefault();

	// ���̏��@TextureColor + �萔 + �萔
	combiner.SetSourceRGB(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT);
	// ���̏��@TextureAlpha + �萔 + �萔
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
// ��`�`�� �����								�搶�̃R�[�h
//--------------------------------------------------------------
void FillRectSubDoriruman(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
{
	nn::gd::CombinerDescription combiner;
	combiner.ToDefault();

	// ���̏��@TextureColor + �萔 + �萔
	combiner.SetSourceRGB(nn::gd::CombinerStage::UNIT0,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT,
		nn::gd::CombinerStage::SOURCE_CONSTANT);
	// ���̏��@TextureAlpha + �萔 + �萔
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
	/* �v���~�e�B�u�̎w�� */
	nn::gd::VertexInputStage::SetPrimitiveTopology(nn::gd::VertexInputStage::PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
}
