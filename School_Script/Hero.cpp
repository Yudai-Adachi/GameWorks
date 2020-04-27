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

static int			g_nAlpha = 255;	// �s�����x

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

//�@�C���X�^���X��
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
	strcpy(name, "�E��");
	hp = 100;
	mp = 20;
	atk = 3;
	def = 10;
	speed = 6;
	lv = 1;
	ex = 0;
}

void CHero::InitHero()
{	// �ϐ��̏������Ȃǂ���΂����ōs��
	g_posHero = nn::math::Vector3(0.0f,0.0f,0.0f);
	g_rotHero = nn::math::Vector3(0.0f,0.0f,0.0f);
}

void CHero::UninitHero()
{	// �������̊J���Ȃǂ���΂����ōs��
}

// 3D�|���S���X�V
void CHero::UpdateHero()
{
}

void CHero::DrawHero_2D()
{
	// �X�e�[�^�X�\��
		Change_2D();
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texstatus);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// �|���S���\���ʒu�Z�b�g
		DrawPolygonMain(4, 92);			// �|���S���\���i�O�p�`���f�[�^�O����j
}

void CHero::DrawHero_2D_second()
{
	// �X�e�[�^�X�\��
		Change_2D();
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texstatus);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// �|���S���\���ʒu�Z�b�g
		DrawPolygonMain(4, 92);			// �|���S���\���i�O�p�`���f�[�^�O����j
}

//�@�o���l�\��
void CHero::DrawExperience()
{
	Change_2D();
	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texexperience);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonMain(4, 140);			// �|���S���\���i�O�p�`���f�[�^�O����j
}

//�@�c��HP�̕\��
void CHero::DrawHero_damage()
{
	Change_2D();
	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texhero_damage);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonMain(4, 144);			// �|���S���\���i�O�p�`���f�[�^�O����j
}

// 3D�|���S���`��(�����)
void CHero::DrawHeroSub()
{
	if (g_nAlpha) {
		CreateMatrix3D( g_posHero, g_rotHero, nn::math::Vector3(1.0f,1.0f,1.0f) );
		DrawPolygonSub(4,16);
	}
}

//----------------------- �搶�̃\�[�X�R�[�h ----------------------------------------------
void CHero::SetHero()
{
	nn::gd::VertexBufferResource* buffers[2] = { bufferCoordHero, bufferTexCoordHero };
	u32 offsets[] = {0, 0};
	nn::gd::VertexInputStage::SetVertexBuffers(0, 2, buffers, offsets);
	nn::gd::VertexInputStage::SetIndexBuffer(bufferIndexHero, nn::gd::VertexInputStage::INDEX_FORMAT_USHORT, 0);
}
//-----------------------------END-------------------------------------------------------

//�@���S����
void CHero::Destroy()
{
	delete hero;
	g_fadeout = 1;
	g_stage = 6;
	change_count = 0;
	change_count2 = 0;
}

//�@���x���A�b�v���̃X�e�[�^�X�̕ω��ƌ��ʉ�
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

//�@�X���C�����U�����ꂽ���HP�Z�b�g
void CHero::AttackHero_slime()
{
	sura->SetHpSlime(hero->Attack_Calculation_slime());
}

//�@�X���C���̍U�����̃_���[�W�v�Z�����Ēl��Ԃ�
int CHero::Attack_Calculation_slime()
{
	return (sura -> GetHpSlime() - hero->GetAtkHero());
}

//�@�h�����}�����U�����ꂽ���HP�Z�b�g
void CHero::AttackHero_doriruman()
{
	dori->SetHpDoriruman(hero->Attack_Calculation_doriruman());
}

//�@�h�����}���̍U�����̃_���[�W�v�Z�����Ēl��Ԃ�
int CHero::Attack_Calculation_doriruman()
{
	return (dori->GetHpDoriruman() - hero->GetAtkHero());
}

//�@�r�[���U�����ꂽ���HP�Z�b�g
void CHero::AttackHero_bee()
{
	bee->SetHpBee(hero->Attack_Calculation_bee());
}

//�@�r�[�̍U�����̃_���[�W�v�Z�����Ēl��Ԃ�
int CHero::Attack_Calculation_bee()
{
	return (bee->GetHpBee() - hero->GetAtkHero());
}

//�@�{�X���U�����ꂽ���HP�Z�b�g
void CHero::AttackHero_boss()
{
	boss->SetHpBoss(hero->Attack_Calculation_boss());
}

//�@�{�X�̍U�����̃_���[�W�v�Z�����Ēl��Ԃ�
int CHero::Attack_Calculation_boss()
{
	return (boss->GetHpBoss() - hero->GetAtkHero());
}

//�@�q�[���[�̑��x��Ԃ�
int CHero::GetSpeedHero()
{
	return this->speed;
}

//�@�q�[���[��HP��Ԃ�
int CHero::GetHpHero()
{
	return this->hp;
}

//�@�q�[���[��HP���Z�b�g
void CHero::SetHpHero(int hp)
{
	this->hp = hp;
}

//�@�q�[���[��MP��Ԃ�
int CHero::GetMpHero()
{
	return this->mp;
}

//�@�q�[���[��MP���Z�b�g����
void CHero::SetMpHero(int mp)
{
	this->mp = mp;
}

//�@�q�[���[�̍U���͂�Ԃ�
int CHero::GetAtkHero()
{
	return this->atk;
}

//�@�q�[���[�̃��x����Ԃ�
int CHero::GetLvHero()
{
	return this->lv;
}

//�@�q�[���[�̃��x�����Z�b�g����
void CHero::SetLvHero(int lv)
{
	this->lv = lv;
}

//�@�q�[���[�̎擾�����o���l��Ԃ�
int CHero::GetExHero()
{
	return this->ex;
}

//�@�q�[���[�̑����o���l���v�Z����
void CHero::AddExHero(int ex)
{
	this->ex += ex;
}

//�@�q�[���[�̑����o���l���v�Z����
void CHero::SetExHero(int ex)
{
	this->ex += ex;
}

 // �ʒu�擾
nn::math::Vector3 GetPosHero()
{
	return g_posHero;
}

nn::math::Vector3 GetRotHero()
{
	return g_rotHero;
}

//--------------------------------------------------------------
// ��`�`�� ����								�搶�̃R�[�h
//--------------------------------------------------------------
void FillRectMainHero(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
// ��`�`�� �����								�搶�̃R�[�h
//--------------------------------------------------------------
void FillRectSubHero(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
	/* �v���~�e�B�u�̎w�� */
	nn::gd::VertexInputStage::SetPrimitiveTopology(nn::gd::VertexInputStage::PRIMITIVE_TOPOLOGY_TRIANGLEFAN);
}

