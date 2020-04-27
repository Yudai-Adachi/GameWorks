#include <math.h>
#include <nn/gx.h>
#include <nn/math.h>
#include <nn/fs.h>
#include <nn/os.h>
#include <nn/init.h>
#include <nn/applet.h>
#include <nn/fnd/fnd_ExpHeap.h>

#include "TexUtils.h"
#include "demo.h"

#include <nn/gd.h>


#include "Main.h"
#include "Fade.h"
#include "Texture.h"
#include "Polygon3D.h"
#include "Land.h"
#include "Enemy.h"
#include "Hero.h"
#include "Status.h"
#include "Boss.h"
#include "Slime.h"
#include "Battle.h"
#include "Boss.h"
#include "End.h"
#include "Doriruman.h"
#include "Bee.h"

//Shader
extern nn::gd::ShaderPipeline* shaderPipeline;
extern nn::gd::UniformLocation s_shaderVariable_proj;
extern nn::gd::UniformLocation s_shaderVariable_view;

/* ExpHeap for app. */
extern nn::fnd::ExpHeap s_AppHeap;
extern uptr s_HeapForGx;
extern const u32 s_GxHeapSize;

extern nn::gd::RenderTarget* s_MainRenderTarget;
extern nn::gd::DepthStencilTarget* s_MainDepthStencilTarget;
/**********************************************************************/
extern nn::gd::RenderTarget* s_SubRenderTarget;
extern nn::gd::DepthStencilTarget* s_SubDepthStencilTarget;
/**********************************************************************/

//--------------------------------------------------------------
// �}�N����`
//--------------------------------------------------------------
#define SPEED			1.0f

#define PLAYER_WIDTH	32
#define PLAYER_HEIGHT	32
#define PLAYER_HIT_W	16
#define PLAYER_HIT_H	16

#define ON_POS_X			-102.0f
#define ON_POS_Y			81.0f
#define ON_POS_X_2			-102.0f
#define ON_POS_Y_2			60.0f
#define ON_POS_X_3			-102.0f
#define ON_POS_Y_3			38.0f
#define ON_POS_X_4			170.0f
#define ON_POS_Y_4			110.0f
#define UNDER_POS_X			-162.0f
#define UNDER_POS_Y			84.0f
#define HISCORE_X		64.0f
#define HISCORE_Y		SCORE_Y
#define HP_X			-64.0f
#define HP_Y			120.0f
#define HP_MAX			5

#define BOSS1HP_X		-128.0f
#define BOSS1HP_Y		-88.0f

#define ENDROLL_START	-400.0f
#define ENDROLL_END		300.0f

#define COMMENT_X		-184.0f
#define COMMENT_Y		104.0f
#define TATAKAU         0
#define MAHOU           1
#define DOUGU			2
#define NIGERU          3
//--------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------
void DrawFrame(void);
int  Initialize(void);
void Finalize();
void InitFrameSub(void);
void InitFrameMain(void);
void DrawPolygonSub(u32,u32);
void AfterRender(void);

void UpdateKey(void);
void PolyMove(void);

//--------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------
nn::hid::PadStatus padStatus;			// �L�[���Z�b�g
nn::hid::TouchPanelStatus tpStatus;		// �^�b�`�p�l�����Z�b�g
nn::hid::AccelerationFloat accel;		// �d�͂���Ƃ����l�ɕϊ��������̂��Z�b�g

float player_x;
float player_y;

int dir = 3;
int pat = 0;
int cnt = 0;
int idle = 1;
int fade_count = 0;
int fade_count2 = 0;
int instance_count = 0;
int instance_count2 = 0;
int instance_count3 = 0;
int instance_count4 = 0;
bool fade_slime = false;
bool fade_boss = false;
int sound_count0 = 0;
int sound_count1 = 0;
int sound_count2 = 0;
int sound_count3 = 0;
int sound_count4 = 0;
int sound_count5 = 0;
int sound_count6 = 0;
int sound_count7 = 0;
int sound_count8 = 0;
extern int random_enemy = 0;

int time_count = 0;

s32 player_stat = 1;
static nn::math::Vector3 g_camPos( 0.0f, 50.0f, 100.0f );	// ���_
static nn::math::Vector3 g_camUp(0.0f, 1.0f, 0.0f);		// �A�b�v�x�N�g��
static nn::math::Vector3 g_target(0.0f, 0.0f, 0.0f);		// �����_
static nn::math::Vector3 g_camPostarget(0.0f, 0.0f, 0.0f);		//��̎��_

SimplePlayer app;

s32 g_stage = 0;
s32 g_score = 0;
s32 g_highscore = 0;
extern s32 g_fadeout = 0;

extern nn::math::Vector3	g_posPolygon3D;
extern int music_count = 0;
int count = 0;
int count2 = 0;
int command = 0;

CSlime *sura = NULL;
CEnemy *mon = new CEnemy();
CBattle *btl = new CBattle();
CHero *hero = NULL;
CBoss *boss = NULL;
CEnd *end = new CEnd();
CDoriruman *dori = NULL;
CBee *bee = NULL;
//==============================================================
// �v���O�����{��
//==============================================================
//--------------------------------------------------------------
// �}�g���N�X�쐬
//--------------------------------------------------------------
void UpdateCamera()
{
	int type = 0;

	switch( type )
	{
	case 0:		// �o�[�h�r���[
		g_target = GetPosPolygon3D();
		g_camPos.x = g_target.x ;
		g_camPos.y = g_target.y + 50.0f;
		g_camPos.z = g_target.z + 100.0f;
		break;

	case 1:		// �r�n�C���h�r���[
		g_target = GetPosPolygon3D();
		g_camPos.y = g_target.y + 100.0f;
		g_camPos.x = g_target.x -
			nn::math::SinDeg(GetRotPolygon3D().y)
			* 100.0f;
		g_camPos.z = g_target.z -
			nn::math::CosDeg(GetRotPolygon3D().y)
			* 100.0f;
		break;

		case 2:		// FPS
		g_camPos = GetPosPolygon3D();

		g_target.y = g_camPos.y;
		// + nn::math::SinDeg(GetRotPolygon3D().x);
		g_target.x = g_camPos.x +
			nn::math::SinDeg(GetRotPolygon3D().y);
		g_target.z = g_camPos.z +
			nn::math::CosDeg(GetRotPolygon3D().y);
		break;

		case 3:
		g_target = GetPosPolygon3D();

		g_camPostarget.y = g_target.y + 100.0f;
		g_camPostarget.x = g_target.x - nn::math::SinDeg(GetRotPolygon3D().y) * 100.0f;
		g_camPostarget.z = g_target.z - nn::math::CosDeg(GetRotPolygon3D().y) * 100.0f;

		nn::math::Vector3 g_camPosdown(g_camPostarget.x - g_camPos.x, g_camPostarget.y - g_camPos.y,g_camPostarget.z - g_camPos.z );

		g_camPos.y += g_camPosdown.y / 10;
		g_camPos.x += g_camPosdown.x / 10;
		g_camPos.z += g_camPosdown.z / 10;
			
		break;
	}
}

void CreateMatrix(f32 vec_tx, f32 vec_ty, f32 vec_tz, f32 angle, f32 sizeX, f32 sizeY, f32 sizeZ)
{
	nn::math::Matrix34 trans;						// ���s�ړ��p�s��̕ϐ�

	nn::math::Matrix34 eye;							// �J�������W�n�ϊ��s��p

	nn::math::Vector3  transVec(vec_tx, vec_ty, vec_tz);		// �ړ������̃x�N�g��(x,y,z�̏��ŃZ�b�g)
	nn::math::Vector3  camPos(0.0f, 0.0f, 9.5f);	// �J�����̈ʒu(X,Y,Z)
	nn::math::Vector3  camUp(-1.0f, 0.0f, 0.0f);	// �J�����̏���������߂�x�N�g��(X,Y,Z)
	nn::math::Vector3  target(0.0f, 0.0f, 0.0f);	// �J���������Ă���_(X,Y,Z)

	//---------------------------------------------------------------------------	
	nn::math::MTX34LookAt(&eye, camPos, camUp, target);	    // ����ϊ��s������o��


	nn::math::MTX34Translate(&trans, &transVec );			    // �ړ������x�N�g�����畽�s�ړ��s����쐬
	nn::math::MTX34Mult(&eye, &eye, &trans);				    // ����ϊ��s��ƍ��W�ϊ��s��i�ړ��j������

	nn::math::Vector3 zoom(sizeX, sizeY, sizeZ);
	nn::math::Matrix34 scale;
	nn::math::MTX34Scale(&scale, &zoom);
	nn::math::MTX34Mult(&eye, &eye, &scale);

	if (angle != 0.0f) {
		nn::math::Matrix34 rotate;
		nn::math::MTX34RotXYZDeg(&rotate, 0.0f, 0.0f, angle);
		nn::math::MTX34Mult(&eye, &eye, &rotate);
	}

	nn::math::Matrix44 mv(eye);								    // ��������3*4�s���4*4�s��ɃZ�b�g

	nn::gd::ShaderStage::SetShaderPipelineConstantFloat(shaderPipeline, s_shaderVariable_view, static_cast<f32*>(mv));
}

nn::math::Matrix34 CreateMatrix3D(const nn::math::Vector3 pos, const nn::math::Vector3 rot, const nn::math::Vector3 scale, bool billboard)
{


	nn::math::Matrix34 mtxTrans;						// ���s�ړ��p�s��̕ϐ�
	nn::math::Matrix34 mtxRot;
	nn::math::Matrix34 mtxScale;

	nn::math::Matrix34 eye;							// �J�������W�n�ϊ��s��

	nn::math::MTX34LookAt(&eye, &g_camPos, &g_camUp, &g_target);	    // ����ϊ��s������o��

	nn::math::Matrix34 mtxRot90;
	nn::math::MTX34RotAxisDeg( &mtxRot90,
		nn::math::Vector3(0.0f,0.0f,1.0f), -90.0f);
	nn::math::MTX34Mult( &eye, &mtxRot90, &eye );
	//---------------------------------------------------------------------------	

	nn::math::MTX34Translate(&mtxTrans, &pos );			    // �ړ������x�N�g�����畽�s�ړ��s����쐬
	nn::math::MTX34Mult(&eye, &eye, &mtxTrans);				    // ����ϊ��s��ƍ��W�ϊ��s��i�ړ��j������

	nn::math::MTX34Scale(&mtxScale, &scale);
	nn::math::MTX34Mult(&eye, &eye, &mtxScale);

	if (billboard)
	{	// �r���{�[�h�̉�]�����̓J�����s��̋t�s��
		nn::math::MTX34 mt;
#if 0		// �p�^�[���P�F�]�u�s����쐬����
		mt.f._00 = eye->f._00;
		mt.f._01 = eye->f._10;
		mt.f._02 = eye->f._20;
		mt.f._10 = eye->f._01;
		mt.f._11 = eye->f._11;
		mt.f._12 = eye->f._21;
		mt.f._20 = eye->f._02;
		mt.f._21 = eye->f._12;
		mt.f._22 = eye->f._22;
#else		// �p�^�[���Q�F�t�s����쐬����
		nn::math::MTX34Inverse(&mt, eye);
#endif
		mt.f._03 = mt.f._13 = mt.f._23 = 0.0f;	// ���s�ړ��������O�ɂ���
		nn::math::MTX34Mult(&eye, &eye, &mt);
	}
	else {
		nn::math::MTX34RotXYZDeg(&mtxRot, rot.x, rot.y, rot.z);
		nn::math::MTX34Mult(&eye, &eye, &mtxRot);
	}

	nn::math::Matrix44 mv(eye);								    // ��������3*4�s���4*4�s��ɃZ�b�g

	nn::gd::ShaderStage::SetShaderPipelineConstantFloat(shaderPipeline, s_shaderVariable_view, static_cast<f32*>(mv));
	return eye;
}

nn::math::Matrix34 CreateMatrix3DHierarchy(nn::math::Matrix34 mtx,const nn::math::Vector3 pos,const nn::math::Vector3 rot,const nn::math::Vector3 scale )
{
	nn::math::Matrix34 mtxTrans;						// ���s�ړ��p�s��̕ϐ�
	nn::math::Matrix34 mtxRot;
	nn::math::Matrix34 mtxScale;

	nn::math::MTX34Translate(&mtxTrans, &pos );			    // �ړ������x�N�g�����畽�s�ړ��s����쐬
	nn::math::MTX34Mult(&mtx, &mtx, &mtxTrans);				    // ����ϊ��s��ƍ��W�ϊ��s��i�ړ��j������

	nn::math::MTX34Scale(&mtxScale, &scale);
	nn::math::MTX34Mult(&mtx, &mtx, &mtxScale);

	nn::math::MTX34RotXYZDeg(&mtxRot, rot.x, rot.y, rot.z);
	nn::math::MTX34Mult(&mtx, &mtx, &mtxRot);

	nn::math::Matrix44 mv(mtx);								    // ��������3*4�s���4*4�s��ɃZ�b�g
	nn::gd::ShaderStage::SetShaderPipelineConstantFloat(shaderPipeline, s_shaderVariable_view, static_cast<f32*>(mv));

	return mtx;
}

void Change_2D()
{
	//Projection matrix
	nn::math::Matrix44 proj;
	//nn::math::MTX44Frustum(&proj, -0.02f, 0.02f, -0.02f*nn::gx::DISPLAY0_HEIGHT/nn::gx::DISPLAY0_WIDTH, 0.02f*nn::gx::DISPLAY0_HEIGHT/nn::gx::DISPLAY0_WIDTH, 0.2f, 100.f);
	nn::math::MTX44Ortho(&proj, -0.5f * nn::gx::DISPLAY0_WIDTH, 0.5f * nn::gx::DISPLAY0_WIDTH, -0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_HEIGHT, 0.2f, 100.0f);
	nn::gd::ShaderStage::SetShaderPipelineConstantFloat(shaderPipeline, s_shaderVariable_proj, static_cast<f32*>(proj));
	//���������e�ϊ��̂��߂̍s����V�F�[�_�p�C�v���C���ɃZ�b�g���Ă���
}

void Change_3D()
{
	//Projection matrix
	nn::math::Matrix44 proj;
	nn::math::MTX44Frustum(&proj,	// �o�͐�s��
		-0.02f,													// left
		0.02f,													// right
		-0.02f*nn::gx::DISPLAY0_HEIGHT / nn::gx::DISPLAY0_WIDTH,	// bottom
		0.02f*nn::gx::DISPLAY0_HEIGHT / nn::gx::DISPLAY0_WIDTH,	// top
		0.2f,													// near
		1000.0f);													// far
	nn::gd::ShaderStage::SetShaderPipelineConstantFloat(shaderPipeline, s_shaderVariable_proj, static_cast<f32*>(proj));
}

void DrawNumber(f32 number_x, f32 number_y, s32 number)
{
	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texNumber);
	s32 digit = 0;	// �ő�5����z��.
	if (number < 10)
	{
		digit = 1;
		CreateMatrix(number_x, number_y, 0.0f, 0.0f, 0.75f, 0.75f, 1.0f);
		SetFrame(number / digit);
		DrawPolygonSub(4, 0);
		number %= digit;
	}
	else if (number >= 10 && number < 100)
	{
		digit = 10;
		for (s32 i = 0; i < 2; i++) {
			CreateMatrix(number_x, number_y, 0.0f, 0.0f, 0.5f, 0.5f, 1.0f);
			SetFrame(number / digit);
			DrawPolygonSub(4, 0);
			number_x += 10;
			number %= digit;
			digit /= 10;
		}
	}

	else if (number >= 100 && number < 1000)
	{
		digit = 100;
		for (s32 i = 0; i < 3; i++) {
			
			CreateMatrix(number_x, number_y, 0.0f, 0.0f, 0.5f, 0.5f, 1.0f);
			SetFrame(number / digit);
			DrawPolygonSub(4, 0);
			number_x += 10;
			number %= digit;
			digit /= 10;
		}
	}
	
}


//--------------------------------------------------------------
// ���ʕ`��
//--------------------------------------------------------------


void score_up()
{
	g_highscore += 10;
	g_score += 10;
}

void extra_score_up()
{
	g_highscore += 100;
	g_score += 100;
}

int time_counter()
{
	time_count++;
	if (time_count >= 180)
	{
		return true;
	}
}

void DrawTitle(void)
{
		hero = new CHero();
		boss = new CBoss();

	//����FFFFF
	InitFrameMain();			//�|���S���\���O����


	instance_count = 0;


	u8 clearColor[] = { 25, 25, 122, 255 };	//�Z����
	nn::gd::Memory::ClearTargets(s_MainRenderTarget, s_MainDepthStencilTarget, clearColor, 1.f, 0);	//��ʃN���A

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texTitle);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);
	
	CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonMain(4, 0);			// �|���S���\���i�O�p�`���f�[�^�O����j

	DrawFade();

	//�����
	InitFrameSub();

	u8 clearColors[] = { 125, 0, 122, 255 };	// �Z����
	nn::gd::Memory::ClearTargets(s_SubRenderTarget, s_SubDepthStencilTarget, clearColors, 1.f, 0);	//��ʃN���A

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texTitle_under);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonSub(4, 0);			// �|���S���\���i�O�p�`���f�[�^�O����j

	DrawFadeSub();

	AfterRender();						 // �|���S���\���㏈��
}

void DrawGame(void)
{
	if (dori == NULL)
	{
		dori = new CDoriruman();
	}
	if (bee == NULL)
	{
		bee = new CBee();
	}

	// ����
	InitFrameMain();
	// �|���S���\���O����
	if (instance_count == 0)
	{
		// boss = new CBoss();
		sura = new CSlime();
	}
	instance_count++;


	u8 clearColor[] = { 0, 255, 255, 255 };	//���F
	nn::gd::Memory::ClearTargets(s_MainRenderTarget, s_MainDepthStencilTarget, clearColor, 1.f, 0);	//��ʃN���A


	Change_3D();
	// 3D�\��

	SetFrame();

	DrawLand();
	SetFrame();
	DrawPolygon3D();
	//DrawEnemy3D();


	// �������2D
	InitFrameMain();	// �֐������璷���ȁB�B�B
	SetFrame();

	if (sura->GetIsSlime() == true)
	{
		SetFrame();
		if (fade_count == 0)
		{
			sura->SetTrueAppear();
			mon->DrawMonster_appear();
			count2++;
		}
		if (count2 == 60)
		{
			FadeOut(0);

			g_fadeout = 1;

			Fade_True_Slime();
			g_stage = 3;
			random_enemy = g_Mer.GenerateRandomN(3) + 1;
			count2 = 0;
		}
	}

	if (boss->GetIsBoss() == true)
	{
		SetFrame();

		FadeOut(0);

		g_fadeout = 1;

		Fade_True_Boss();
		g_stage = 4;
	}


	SetFrame();
	DrawFade();

	//�����
	InitFrameSub();

	u8 clearColors[] = { 125, 0, 122, 255 };	// �Z����
	nn::gd::Memory::ClearTargets(s_SubRenderTarget, s_SubDepthStencilTarget, clearColors, 1.f, 0);	//��ʃN���A

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texfield_under);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonSub(4, 0);			// �|���S���\���i�O�p�`���f�[�^�O����j

	SetFrame();
	hero->DrawHero_2D();
	hero->DrawExperience();
	DrawNumber(ON_POS_X, ON_POS_Y, hero->GetLvHero());
	DrawNumber(ON_POS_X_2, ON_POS_Y_2, hero->GetHpHero());
	DrawNumber(ON_POS_X_3, ON_POS_Y_3, hero->GetMpHero());
	DrawNumber(ON_POS_X_4, ON_POS_Y_4, hero->GetExHero());
	DrawFadeSub();

	// 3D�\��
//	SetFrame();
//	DrawPolygon3D();

	AfterRender();					// �|���S���\���㏈��
}

void DrawBattle(void)
{
	//����
	InitFrameMain();			//�|���S���\���O����

	u8 clearColors[] = { 255, 255, 255, 255 };	// �Z����
	nn::gd::Memory::ClearTargets(s_MainRenderTarget, s_MainDepthStencilTarget, clearColors, 1.f, 0);	//��ʃN���A

	if (fade_slime == true)
	{
		if (fade_count == 0)
		{
			fade_count++;
		}

		
		sura->DrawSlime();
		sura->DrawSlime_apper();
		

	}
	
	DrawFade();

	//�����
	InitFrameSub();

	u8 clearColors1[] = { 0, 0, 0, 255 };	// �Z����
	nn::gd::Memory::ClearTargets(s_SubRenderTarget, s_SubDepthStencilTarget, clearColors1, 1.f, 0);	//��ʃN���A

	btl->DrawCommand();
	hero->DrawHero_2D_second();
	DrawNumber(ON_POS_X, ON_POS_Y, hero->GetLvHero());
	DrawNumber(ON_POS_X_2, ON_POS_Y_2, hero->GetHpHero());
	DrawNumber(ON_POS_X_3, ON_POS_Y_3, hero->GetMpHero());

	SetFrame();

	if (random_enemy == 1)
	{
		switch (command)
		{
		case TATAKAU:

			btl->DrawCursor(TATAKAU);
			if (padStatus.trigger & nn::hid::BUTTON_A)
			{
				//hero -> DrawHero_damage();

				if (hero->GetSpeedHero() >= sura->GetSpeedSlime())
				{
					hero->AttackHero_slime();
					sura->SetFlashTrue();//�q�[���[���U��

					if (sura->GetHpSlime() <= 0)
					{
						sura->Destroy();
						hero ->AddExHero(1);
						instance_count = 0;
						instance_count2++;
						instance_count3 = 0;
						fade_count = 0;
						g_stage = 2;
					}
					if (sura->GetIsSlime() == true)
					{
						sura->Attack();
						if (hero->GetHpHero() <= 0)
						{
							hero->Destroy();
						}

					}
				}
				else
				{
					sura->Attack();
					if (hero->GetHpHero() <= 0)
					{
						hero->Destroy();
					}
					if (sura->GetIsSlime() == true)
					{
						hero->AttackHero_slime();
						sura->SetFlashTrue();

						if (sura->GetHpSlime() <= 0)
						{
							sura->Destroy();
							hero->AddExHero(1);
							instance_count = 0;
							instance_count2++;
							instance_count3 = 0;
							fade_count = 0;
							g_stage = 2;
						}
					}
				}
				break;
			}


			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = MAHOU;
			}
			break;
		case MAHOU:

			btl->DrawCursor(MAHOU);

			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = NIGERU;
			}
			break;
		case DOUGU:
			btl->DrawCursor(DOUGU);

			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = DOUGU;
			}
			break;
		case NIGERU:

			btl->DrawCursor(NIGERU);

			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = TATAKAU;
			}
			break;
		}

		DrawFadeSub();

	}
	else if (random_enemy == 2)
	{
		switch (command)
		{
		case TATAKAU:

			btl->DrawCursor(TATAKAU);
			if (padStatus.trigger & nn::hid::BUTTON_A)
			{
				//hero -> DrawHero_damage();

				if (hero->GetSpeedHero() >= dori->GetSpeedDoriruman())
				{
					hero->AttackHero_doriruman();									//�q�[���[���U��
					sura->SetFlashTrue();//�q�[���[���U��

					if (dori->GetHpDoriruman() <= 0)
					{
						sura->Destroy();
						hero->AddExHero(5);
						instance_count = 0;
						instance_count2++;
						instance_count3 = 0;
						fade_count = 0;
						g_stage = 2;
					}
					if (sura->GetIsSlime() == true)
					{
						dori->Attack();
						if (hero->GetHpHero() <= 0)
						{
							hero->Destroy();
						}

					}
				}
				else
				{
					dori->Attack();
					if (hero->GetHpHero() <= 0)
					{
						hero->Destroy();
					}
					if (sura->GetIsSlime() == true)
					{
						hero->AttackHero_doriruman();
						sura->SetFlashTrue();//�q�[���[���U��

						if (dori->GetHpDoriruman() <= 0)
						{
							sura->Destroy();
							hero->AddExHero(5);
							instance_count = 0;
							instance_count2++;
							instance_count3 = 0;
							fade_count = 0;
							g_stage = 2;
						}
					}
				}
				break;
			}


			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = MAHOU;
			}
			break;
		case MAHOU:

			btl->DrawCursor(MAHOU);

			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = NIGERU;
			}
			break;
		case DOUGU:
			btl->DrawCursor(DOUGU);

			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = DOUGU;
			}
			break;
		case NIGERU:

			btl->DrawCursor(NIGERU);

			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = TATAKAU;
			}
			break;
		}

		DrawFadeSub();

	}
	else if (random_enemy == 3)
	{
		switch (command)
		{
		case TATAKAU:

			btl->DrawCursor(TATAKAU);
			if (padStatus.trigger & nn::hid::BUTTON_A)
			{
				//hero -> DrawHero_damage();

				if (hero->GetSpeedHero() >= bee->GetSpeedBee())
				{
					hero->AttackHero_bee();									//�q�[���[���U��
					sura->SetFlashTrue();//�q�[���[���U��

					if (bee->GetHpBee() <= 0)
					{
						sura->Destroy();
						hero->AddExHero(10);
						instance_count = 0;
						instance_count2++;
						instance_count3 = 0;
						fade_count = 0;
						g_stage = 2;
					}
					if (sura->GetIsSlime() == true)
					{
						bee->Attack();
						if (hero->GetHpHero() <= 0)
						{
							hero->Destroy();
						}

					}
				}
				else
				{
					bee->Attack();
					if (hero->GetHpHero() <= 0)
					{
						hero->Destroy();
					}
					if (sura->GetIsSlime() == true)
					{
						hero->AttackHero_bee();
						sura->SetFlashTrue();//�q�[���[���U��

						if (bee->GetHpBee() <= 0)
						{
							sura->Destroy();
							hero->AddExHero(10);
							instance_count = 0;
							instance_count2++;
							instance_count3 = 0;
							fade_count = 0;
							g_stage = 2;
						}
					}
				}
				break;
			}


			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = MAHOU;
			}
			break;
		case MAHOU:

			btl->DrawCursor(MAHOU);

			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = NIGERU;
			}
			break;
		case DOUGU:
			btl->DrawCursor(DOUGU);

			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = DOUGU;
			}
			break;
		case NIGERU:

			btl->DrawCursor(NIGERU);

			if (padStatus.trigger & nn::hid::BUTTON_DOWN)
			{
				command = TATAKAU;
			}
			break;
		}

		DrawFadeSub();

	}
	
	AfterRender();
}

void DrawBossBattle(void)
{
	//����
	InitFrameMain();			//�|���S���\���O����
	if (fade_boss == true)
	{
		if (fade_count2 == 0)
		{
			fade_count2++;
		}
		boss->DrawBossFinal();

	}

	DrawFade();

	//�����
	InitFrameSub();

	u8 clearColors[] = { 125, 0, 122, 255 };	// �Z����
	nn::gd::Memory::ClearTargets(s_SubRenderTarget, s_SubDepthStencilTarget, clearColors, 1.f, 0);	//��ʃN���A

	btl->DrawCommand();
	hero->DrawHero_2D_second();
	DrawNumber(ON_POS_X, ON_POS_Y, hero->GetLvHero());
	DrawNumber(ON_POS_X_2, ON_POS_Y_2, hero->GetHpHero());
	DrawNumber(ON_POS_X_3, ON_POS_Y_3, hero->GetMpHero());

	SetFrame();

	switch (command)
	{
	case TATAKAU:

		btl->DrawCursor(TATAKAU);
		if (padStatus.trigger & nn::hid::BUTTON_A)
		{
			if (hero->GetSpeedHero() >= boss->GetSpeedBoss())
			{
				hero->AttackHero_boss();									//�q�[���[���U��

				if (boss->GetHpBoss() <= 0)
				{
					boss->Destroy();
					instance_count = 0;
					instance_count2++;
					instance_count3 = 0;
					fade_count = 0;
				}
				if (boss->GetIsBoss() == true)
				{
					boss->Attack();
					hero->Destroy();

				}
			}
			else
			{
				boss->Attack();
				hero->Destroy();
				if (boss->GetIsBoss() == true)
				{
					hero->AttackHero_boss();

					if (boss->GetHpBoss() <= 0)
					{
						boss->Destroy();
						instance_count = 0;
						instance_count2++;
						instance_count3 = 0;
						fade_count = 0;
					}
				}
			}
			break;
		}


		if (padStatus.trigger & nn::hid::BUTTON_DOWN)
		{
			command = MAHOU;
		}
		break;
	case MAHOU:

		btl->DrawCursor(MAHOU);

		if (padStatus.trigger & nn::hid::BUTTON_DOWN)
		{
			command = NIGERU;
		}
		break;
	case DOUGU:
		btl->DrawCursor(DOUGU);

		if (padStatus.trigger & nn::hid::BUTTON_DOWN)
		{
			command = DOUGU;
		}
		break;
	case NIGERU:

		btl->DrawCursor(NIGERU);

		if (padStatus.trigger & nn::hid::BUTTON_DOWN)
		{
			command = TATAKAU;
		}
		break;
	}

	DrawFadeSub();

	AfterRender();						 // �|���S���\���㏈��
}

void DrawEnd(void)
{
	//����
	InitFrameMain();			//�|���S���\���O����
		end->DrawEnd();

	DrawFade();

	//�����
	InitFrameSub();

	u8 clearColors[] = { 125, 0, 255, 255 };	// �Z����
	nn::gd::Memory::ClearTargets(s_SubRenderTarget, s_SubDepthStencilTarget, clearColors, 1.f, 0);	//��ʃN���A

	DrawFadeSub();

	AfterRender();						 // �|���S���\���㏈��
}

void DrawGameover(void)
{
	//����
	InitFrameMain();			//�|���S���\���O����

	u8 clearColor[] = { 25, 25, 122, 255 };	//�Z����
	nn::gd::Memory::ClearTargets(s_MainRenderTarget, s_MainDepthStencilTarget, clearColor, 1.f, 0);	//��ʃN���A

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texfield_under);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonMain(4, 0);			// �|���S���\���i�O�p�`���f�[�^�O����j

	DrawFade();

	if (padStatus.release & nn::hid::CTR::BUTTON_START) {
		g_stage = 1;
		sura->Destroy();
		hero->Destroy();
		hero->SetExHero(0);
	}

	//�����
	InitFrameSub();

	nn::gd::Memory::ClearTargets(s_SubRenderTarget, s_SubDepthStencilTarget, clearColor, 1.f, 0);	//��ʃN���A

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texgameover);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);	// �|���S���\���ʒu�Z�b�g
	DrawPolygonSub(4, 0);			// �|���S���\���i�O�p�`���f�[�^�O����j

	DrawFadeSub();

	AfterRender();						 // �|���S���\���㏈��
}

void DrawFrame(void)
{
	switch (g_stage) {
	case 0:
		break;
	case 1:	// �^�C�g��
		DrawTitle();
		break;
	case 2:	// �Q�[��
		
		DrawGame();
		break;
	case 3: // �o�g��
		DrawBattle();
		break;
	case 4: // �{�X��
		DrawBossBattle();
		break;
	case 5: // �G���f�B���O
		DrawEnd();
		break;
	case 6: // �Q�[���I�[�o�[
		DrawGameover();
		break;
	}
}

//--------------------------------------------------------------
// ���W�X�V
//--------------------------------------------------------------
void PolyMoveGame(void)
{
	
	UpdatePolygon3D();
	UpdateCamera();
	//UpdateEnemy3D();
	hero -> UpdateHero();
	UpdateStatus();
	
}


//app.SetSoundState(0,1,0,0);// �Đ��g���b�NNo�i0�`7�j,�Đ�or��~�i0,1�j,���yNo�i0�`6�j, ���[�von/off�i1,0�j

void PolyMoveBeforeGameOver(void)
{
	// �X�^�[�g�{�^���������ꂽ���H
	if (padStatus.release & nn::hid::CTR::BUTTON_START) {
		g_fadeout = 1;
		FadeOut(1);
		return;
	}

	// ��莞�Ԍo�߂������H
	++player_stat;
	if (player_stat >= 0) {
		g_fadeout = 1;
		FadeOut(1);
		return;
	}

	cnt = (cnt + 1) % 15;
	if (cnt == 0) {
		pat = (pat + 1) % 2;
	}

}

void PolyMove(void)
{
	switch (g_stage) {
	case 0:	// ������

		g_stage = 1;
		app.SetSoundState(3, 0, 3, 1);
		SetFadeColor(0, 127, 63);
		FadeIn(1);
		// THRU
	case 1:	// �^�C�g��
		if (IsFadeIn()) {
			break;
		}
		if (g_fadeout) {
			if (IsFadeOut()) {
				break;
			}

			g_score = 0;
			player_x = player_y = 0.0f;
			dir = 3;
			pat = cnt = 0;
			idle = 1;
			player_stat = -60;
			g_score = 0;
			g_fadeout = 0;
			FadeIn(1);
			g_stage = 2; // �Q�[����ʂ�
			break;
		}
		if (padStatus.trigger & nn::hid::CTR::BUTTON_START) {
			app.SetSoundState(3, 1, 3, 1);
			g_fadeout = 1;
			FadeOut(1);
		}
		break;
	case 2: // �Q�[��
		if (IsFadeIn()) {
			break;
		}
		if (g_fadeout) {
			if (IsFadeOut()) {
				break;
			}

			g_fadeout = 0;
			FadeIn(1);
			break;
		}

		app.SetSoundState(0, 1, 0, 1);
		sound_count0 = 0;
		if (sound_count4 == 0)
		{
			app.SetSoundState(4, 0, 4, 1);
			sound_count4++;
		}
		if (sura->GetIsSlime() != true)
		{
			if (instance_count2 > 0)
			{
				if (instance_count3 == 0)
				{
					delete sura;
					sura = NULL;
					delete dori;
					dori = NULL;
					delete bee;
					bee = NULL;
					instance_count3++;
				}

			}
			PolyMoveGame();

		}
		break;

	case 3: // �o�g��
		if (IsFadeIn()) {
			app.SetSoundState(4, 1, 4, 1);
			sound_count4 = 0;
			break;
		}
		if (g_fadeout) {
			if (IsFadeOut()) {
				break;
			}
			g_fadeout = 0;
			FadeIn(1);
			break;
		}

		if (sound_count0 == 0)
		{
			app.SetSoundState(0, 0, 0, 1);
			sound_count0++;
		}


		break;

	case 4: // �{�X��
		if (IsFadeIn()) {
			app.SetSoundState(4, 1, 4, 1);
			break;
		}
		if (g_fadeout) {
			if (IsFadeOut()) {
				break;
			}
			g_fadeout = 0;
			FadeIn(1);
			app.SetSoundState(1, 0, 1, 1);
			break;
		}

		break;

	case 5: // �G���f�B���O
		if (IsFadeIn()) {
			app.SetSoundState(1, 1, 1, 1);
			app.SetSoundState(4, 1, 4, 1);
			break;
		}
		if (g_fadeout) {
			if (IsFadeOut()) {
				break;
			}
			g_fadeout = 0;
			FadeIn(1);
			app.SetSoundState(6, 0, 6, 1);
			break;
		}
		break;

	case 6: // �Q�[���I�[�o�[
		if (IsFadeIn()) {
			app.SetSoundState(1, 1, 1, 1);
			app.SetSoundState(4, 1, 4, 1);
			break;
		}
		if (g_fadeout) {
			if (IsFadeOut()) {
				break;
			}
			g_fadeout = 0;
			FadeIn(1);
			app.SetSoundState(0, 1, 0, 1);
			app.SetSoundState(1, 1, 1, 1);
			app.SetSoundState(6, 0, 6, 1);
			break;
		}
		break;
	}
		UpdateFade();
}


//--------------------------------------------------------------
// �L�[���X�V											�搶�̃R�[�h
//--------------------------------------------------------------
void UpdateKey(void)
{
	// Pad
	static nn::hid::PadReader padReader;
	padReader.ReadLatest(&padStatus);

	// Touch
	static nn::hid::TouchPanelReader tpReader;
	tpReader.ReadLatest(&tpStatus);

	// Acceleration
	static nn::hid::AccelerometerReader accReader; 
	nn::hid::AccelerometerStatus accStatus; 

	accReader.ReadLatest(&accStatus);
	accReader.ConvertToAcceleration(&accel, 1, &accStatus);
}

//--------------------------------------------------------------
// �Q�[�����C��											�搶�̃R�[�h
//--------------------------------------------------------------
void GameMain(void)
{
	UpdateKey();			// �L�[���擾
	PolyMove();				// �`����W�X�V
	DrawFrame();			// �`�揈��
}

//--------------------------------------------------------------
// �G���g���|�C���g										�搶�̃R�[�h
//--------------------------------------------------------------
void nnMain(void)
{
	nngxStartLcdDisplay();

	app.Initialize();
	Initialize();
	nn::hid::Initialize();
	app.Start();
	g_Mer.Initialize();

	for (;;) {
		GameMain();
		nngxWaitVSync(NN_GX_DISPLAY_BOTH); // VSync��҂�
	}
	g_Mer.Finalize();

	app.End();
	Finalize();
	app.Finalize();

	/* shutdown_display */
	s_AppHeap.Free(reinterpret_cast<void*>(s_HeapForGx));
	s_AppHeap.Finalize();
}

// �����蔻��
bool CheckCollision3D( nn::math::Vector3* pos1, f32 size1, nn::math::Vector3* pos2, f32 size2 )
{
	// �����̔���͍��W�̑召�����i���S������Ă��玮�͕ς��̂Œ��Ӂj�j
	if( pos1->y + size1/2 > pos2->y - size2/2 && pos1->y - size1/2 < pos2->y + size2/2 )
	{
		// ���ʂ̔����2�̍��W�̋���
		f32 length2;
		length2 = (pos1->x - pos2->x)*(pos1->x - pos2->x) + (pos1->z - pos2->z)*(pos1->z - pos2->z);
		if( length2 < (size1/2+size2/2)*(size1/2+size2/2) )
		{
			return true;
		}
	}
	return false;
}

bool Boss_CheckCollision3D(nn::math::Vector3 pos1, f32 size1)
{
	// �����̔���͍��W�̑召�����i���S������Ă��玮�͕ς��̂Œ��Ӂj�j
	if (pos1.y + size1 / 2 > 70.0f - 6.0f / 2 && pos1.y - size1 / 2 < 70.0f + 6.0f / 2)
	{
		// ���ʂ̔����2�̍��W�̋���
		f32 length2;
		length2 = (pos1.x - 45.0f)*(pos1.x - 45.0f) + (pos1.z - 2.0f)*(pos1.z - 2.0f);
		if (length2 < (size1 / 2 + 6.0f / 2)*(size1 / 2 + 6.0f / 2))
		{
			return true;
		}
	}
	return false;
}

void Fade_True_Slime()
{
	fade_slime = true;
}
