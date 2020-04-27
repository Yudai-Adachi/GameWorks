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


static int			g_nAlpha = 255;	// �s�����x

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
// �O���[�o���ϐ��錾------------------------------------------------
int appear_count1 = 0;
//-------------------------------------------------------------------

// �{�X�̏����l
CBoss::CBoss()
{
	strcpy(name, "�]�[�}");
	hp = 1;
	mp = 10;
	atk = 20;
	def = 15;
	speed = 12;
}

//�R���X�g���N�^
CBoss::~CBoss()
{

}

void CBoss::InitBoss()
{	// �ϐ��̏������Ȃǂ���΂����ōs��
	
}

void CBoss::UninitBoss()
{	// �������̊J���Ȃǂ���΂����ōs��
}

// 3D�|���S���X�V
void CBoss::UpdateBoss()
{
}

// 3D�|���S���`��(����)
void CBoss::DrawChangeBoss()
{
	ChangeBMP(s_texsuraimu, "boss.bmp");
	this->boss_draw = true;
}



// 3D�|���S���`��(�����)
void CBoss::DrawBossSub()
{

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texboss);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonMain(4, 0);			// �|���S���\���i�O�p�`���f�[�^�O����j
}

// �X���C���̕\�����O
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

		CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// �|���S���\���ʒu�Z�b�g
		DrawPolygonMain(4, 87);			// �|���S���\���i�O�p�`���f�[�^�O����
	}
}

//�@�t�B�[���h�Ƀ{�X���r���{�[�h�ŕ`��
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

//�@�퓬���̃��X�{�X�`��
void CBoss::DrawBossFinal()
{
	Change_2D();

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texboss_final);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonMain(4, 132);			// �|���S���\���i�O�p�`���f�[�^�O����j
}

//�@���S����
void CBoss::Destroy()
{
	boss_draw = false;
	is = false;
	fade_boss = false;
	delete boss;
	g_fadeout = 1;
	g_stage = 5;
}

//�@�U����̎c��HP���Z�b�g
void CBoss::Attack()
{
	hero->SetHpHero(boss->Attack_Calculation());
}

//�@�U�����̃_���[�W�v�Z
int CBoss::Attack_Calculation()
{
	return (hero->GetHpHero() - boss->GetAtkBoss());
}

//�@�{�X�̑��݊m�F�̕ϐ���Ԃ�
int CBoss::GetIsBoss()
{
	return this->is;
}

//�@�{�X�̑��݂���̕ύX
void CBoss::SetTrueBoss()
{
	this->is = true;
}

//�@�{�X�̑��݂Ȃ��ɕύX
void CBoss::SetFalseBoss()
{
	this->is = false;
}

//�@�{�X�̑��݊m�F�̕ϐ���Ԃ�
int CBoss::GetDrawBoss()
{
	return this->boss_draw;
}

//�@�{�X�̏o���m�F�̕ϐ���Ԃ�
int CBoss::GetIsAppear()
{
	return this->boss_appear_draw;
}

//�@�{�X�̏o���̕ϐ���OK���o��
void CBoss::SetTrueAppear()
{
	this->boss_appear_draw = true;
}

//�@�{�X�̏o���̕ϐ���No���o��
void CBoss::SetfalseAppear()
{
	this->boss_appear_draw = false;
}

//�@�{�X�̑��x���擾
int CBoss::GetSpeedBoss()
{
	return this->speed;
}

//�@�{�X��HP���擾
int CBoss::GetHpBoss()
{
	return this->hp;
}

//�@�{�X��HP���Z�b�g
void CBoss::SetHpBoss(int hp)
{
	this->hp = hp;
}

//�@�{�X�̍U���͂�Ԃ�
int CBoss::GetAtkBoss()
{
	return this->atk;
}



// �ʒu�擾
nn::math::Vector3 CBoss::GetPosBoss()
{
	return g_posBoss;
}

nn::math::Vector3 CBoss::GetRotBoss()
{
	return g_rotBoss;
}


//--------------------------------------------------------------
// ��`�`�� ����             �搶�̃R�[�h
//--------------------------------------------------------------
void FillRectMainBoss(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
// ��`�`�� �����						�搶�̃R�[�h
//--------------------------------------------------------------
void FillRectSubBoss(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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

