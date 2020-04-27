// 3D�|���S������
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
// �O���[�o���ϐ��錾------------------------------------------------
int appear_count = 0;
int change_count = 0;
int change_count2 = 0;
int flashing_count = 0;
int flashing_second = 0;
//-------------------------------------------------------------------

// �X���C���̏����l
CSlime::CSlime()
{
	strcpy(name, "�X���C��");
	hp = 5;
	mp = 0;
	atk = 2;
	def = 1;
	speed = 1;
	flash = false;
}

//�@�f�X�g���N�^
CSlime::~CSlime()
{

}

void CSlime::InitSlime()
{	// �ϐ��̏������Ȃǂ���΂����ōs��
	g_posSlime = nn::math::Vector3(0.0f, 0.0f, 0.0f);
	g_rotSlime = nn::math::Vector3(0.0f, 0.0f, 0.0f);

	
}

void CSlime::UninitSlime()
{	// �������̊J���Ȃǂ���΂����ōs��
}

// 3D�|���S���X�V
void CSlime::UpdateSlime()
{
}

// 3D�|���S���`��(����)
void CSlime::DrawSlime()
{
	if (GetFlashEnemy() == true)							//�@�U�����󂯂��G�͓_�ł���
	{
		if (flashing_count % 2 == 0 && flashing_second <= 15)		//�@�_�Ŏ���
		{
			flashing_count++;
			flashing_second++;

			Change_2D();

			nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texsuraimu);
			nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

			CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
			DrawPolygonMain(4, 0);			// �|���S���\���i�O�p�`���f�[�^�O����j
			this->slime_draw = true;

			if (random_enemy == 1 && change_count == 0)				//�_�ł���G�̎w��
			{
				change_count++;
//				ChangeBMP(s_texsuraimu, "suraimu.bmp");
			}

			if (random_enemy == 2 && change_count == 0)				//�_�ł���G�̎w��
			{
				change_count++;
//				ChangeBMP(s_texsuraimu, "doriruman.bmp");

			}


			if (random_enemy == 3 && change_count == 0)				//�_�ł���G�̎w��
			{
				change_count++;
//				ChangeBMP(s_texsuraimu, "bee.bmp");
			}
		}
		else if(flashing_second > 15)							�@�@//�_�Ŏ��Ԍo�ߔ���
		{
			flashing_second = 0;
			SetFlashFalse();
			flashing_count++;
		}
		else if(flashing_count % 2 != 0)						�@ //�or����
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

		CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
		DrawPolygonMain(4, 0);			// �|���S���\���i�O�p�`���f�[�^�O����j
		this->slime_draw = true;
		
		if (random_enemy == 1 && change_count == 0)�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@//�@�X���C���̕`��
		{
			change_count++;
			ChangeTGA(s_texsuraimu, "suramu.tga");
		}

		if (random_enemy == 2 && change_count == 0)								//�@�h�����}���̕`��
		{
			change_count++;
			ChangeTGA(s_texsuraimu, "doriruman.tga");

		}


		if (random_enemy == 3 && change_count == 0)								//�@�r�[�̕`��
		{
			change_count++;
			ChangeTGA(s_texsuraimu, "bee.tga");
		}

	}

}



// 3D�|���S���`��(�����)
void CSlime::DrawSlimeSub()
{

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texsuraimu);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonMain(4, 0);			// �|���S���\���i�O�p�`���f�[�^�O����j
}

 // �X���C���̕\�����O
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

		CreateMatrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	// �|���S���\���ʒu�Z�b�g
		DrawPolygonMain(4, 88);			// �|���S���\���i�O�p�`���f�[�^�O����
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

//�@���S����
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

//�@�_���[�W�v�Z��̃q�[���[��HP
void CSlime::Attack()
{
	hero->SetHpHero(sura ->Attack_Calculation());
}

//�@�q�[���[�̃_���[�W�v�Z
int CSlime::Attack_Calculation()
{
	return (hero->GetHpHero() - sura->GetAtkSlime());
}

//�@�X���C�����`�悳��Ă��邩�ǂ����̕ϐ���Ԃ�
int CSlime::GetIsSlime()
{
	return this->is;
}

//�@�X���C�������݂��Ă��邱�Ƃ�ϐ��ɑ��
void CSlime::SetTrueSlime()
{
	this->is = true;
}

//�@�X���C�����`�悳��Ă��邩�ǂ�����Ԃ�
int CSlime::GetDrawSlime()
{
	return this->slime_draw;
}

//�@�X���C���o���O�̉摜�̕`�悪�ł��Ă��邩��\���ϐ���Ԃ�
int CSlime::GetIsAppear()
{
	return this->slime_appear_draw;
}

//�@�X���C���o���O�̕`�悪�ł��Ă��邱�Ƃ�ϐ��ɑ��
void CSlime::SetTrueAppear()
{
	this->slime_appear_draw = true;
}

//�@�X���C���o���܂��̕`�悪�ł��Ă��Ȃ����Ƃ�ϐ��ɑ��
void CSlime::SetfalseAppear()
{
	this->slime_appear_draw = false;
}

//�@�X���C���̑��x�����
int CSlime::GetSpeedSlime()
{
	return this->speed;
}

//�@�X���C����HP��Ԃ�
int CSlime::GetHpSlime()
{
	return this->hp;
}
y
//�@�X���C����HP���Z�b�g
void CSlime::SetHpSlime(int hp)
{
	this -> hp = hp;
}

//�@�X���C���̍U���͂�Ԃ�
int CSlime::GetAtkSlime()
{
	return this->atk;
}

//�@�_�ł��Ă��邩�ǂ����̕ϐ���Ԃ�
int CSlime::GetFlashEnemy()
{
	return this->flash;
}

//�@�_�ł��Ă��Ȃ����Ƃ�ϐ��ɑ��
void CSlime::SetFlashFalse()
{
	flash = false;
}

//�@�_�ł��Ă��邱�Ƃ�ϐ��ɑ��
void CSlime::SetFlashTrue()
{
	flash = true;
}


// �ʒu�擾
nn::math::Vector3 CSlime::GetPosSlime()
{
	return g_posSlime;
}

nn::math::Vector3 CSlime::GetRotSlime()
{
	return g_rotSlime;
}


//--------------------------------------------------------------
// ��`�`�� ����									�搶�̃R�[�h
//--------------------------------------------------------------
void FillRectMainSlime(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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
// ��`�`�� �����									�搶�̃R�[�h
//--------------------------------------------------------------
void FillRectSubSlime(u8 colorR, u8 colorG, u8 colorB, u8 colorA)
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

