#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Battle.h"
#include "Slime.h"
#include "Main.h"
#include "Texture.h"
#include "string.h"
#include "Boss.h"
//-----------------------------------------------------------------------------------------------
//�}�N����`

#define TATAKAU         0
#define MAHOU           1
#define DOUGU           2
#define NIGERU          3

//------------------------�搶�̃R�[�h-------------------------------------------------------------------------

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;
//--------------------------END------------------------------------------------------------------------------

//�@�O���[�o���ϐ��錾----------------------------------------------------------------------------
extern nn::math::Vector3	g_posbattle(0.0f, 0.0f, 0.0f);
extern nn::math::Vector3	g_rotbattle(0.0f, 0.0f, 0.0f);
//-----------------------------------------------------------------------------------------------

// �C���X�^���X��--------------------------------------------------------------------------------
extern CSlime *sura;
extern CEnemy *mon;
extern CBoss *boss;
//-----------------------------------------------------------------------------------------------

//�@�񎟌��ɕϊ����ĕ`��
void CBattle::DrawCommand()
{
	Change_2D();

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcommand);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonMain(4, 96);			// �|���S���\���i�O�p�`���f�[�^�O����j
}

// �퓬���̃J�[�\���̕\��
void CBattle::DrawCursor(int number)
{
	Change_2D();

	switch (number)
	{
	case TATAKAU:
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcursor);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
		DrawPolygonMain(4, 100);			// �|���S���\���i�O�p�`���f�[�^�O����j
		break;

	case MAHOU:
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcursor);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
		DrawPolygonMain(4, 104);			// �|���S���\���i�O�p�`���f�[�^�O����j
		break;

	case DOUGU:
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcursor);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
		DrawPolygonMain(4, 108);			// �|���S���\���i�O�p�`���f�[�^�O����j
		break;

	case NIGERU:
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texcursor);
		nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

		CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
		DrawPolygonMain(4, 112);			// �|���S���\���i�O�p�`���f�[�^�O����j
		break;
	}
}

//�@�R���X�g���N�^
CBattle::CBattle()
{
}

//�@�f�X�g���N�^
CBattle::~CBattle()
{
}
