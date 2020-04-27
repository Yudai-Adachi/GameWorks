#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Bee.h"
#include "Main.h"
#include "Texture.h"
#include "string.h"
#include "Battle.h"
#include "Hero.h"
#include "Boss.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;

extern nn::math::Vector3	g_posBee(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_rotBee(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_posBeeHead(0.0f, 2.0f, 0.0f);
extern nn::math::Vector3	g_rotBeeHead(0.0f, 0.0f, 0.0f);

extern bool fade_slime;

extern CBee *bee;
extern CEnemy *mon;
extern CBattle *btl;
extern CHero *hero;
extern CBoss *boss;

//-------------------------------------------------------------------

// �r�[�̏����l
CBee::CBee()
{
	strcpy(name, "�r�[");
	hp = 30;
	mp = 15;
	atk = 12;
	def = 15;
	speed = 3;
}

//�@�f�X�g���N�^
CBee::~CBee()
{

}

void CBee::InitBee()
{	// �ϐ��̏������Ȃǂ���΂����ōs��
	g_posBee = nn::math::Vector3(0.0f, 0.0f, 0.0f);
	g_rotBee = nn::math::Vector3(0.0f, 0.0f, 0.0f);


}

// �U�����̃_���[�W�v�Z
void CBee::Attack()
{
	hero->SetHpHero(bee->Attack_Calculation());
}

//�@�U�����̒l��Ԃ�
int CBee::Attack_Calculation()
{
	return (hero->GetHpHero() - bee->GetAtkBee());
}

//�@�r�[�̑��x��Ԃ�
int CBee::GetSpeedBee()
{
	return this->speed;
}

//�@HP��Ԃ�
int CBee::GetHpBee()
{
	return this->hp;
}

//�@HP���Z�b�g����
void CBee::SetHpBee(int hp)
{
	this->hp = hp;
}

//�@�U���͂�Ԃ�
int CBee::GetAtkBee()
{
	return this->atk;
}



// �ʒu�擾
nn::math::Vector3 CBee::GetPosBee()
{
	return g_posBee;
}

nn::math::Vector3 CBee::GetRotBee()
{
	return g_rotBee;
}


//--------------------------------------------------------------
// ��`�`�� ����            �搶�̃R�[�h
//--------------------------------------------------------------
void FillRectMainBee(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
// ��`�`�� �����                  �搶�̃R�[�h
//--------------------------------------------------------------
void FillRectSubBee(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
