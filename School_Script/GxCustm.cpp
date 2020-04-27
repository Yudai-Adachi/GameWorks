//==============================================================
//  GxCustm.cpp
//
//--------------------------------------------------------------
//                                    Author : Nakagawa Hiroki
//                                             Michiba  Hiroaki
//                                             HAL OSAKA
//==============================================================

//==============================================================
// �C���N���[�h
//==============================================================

//------------------------�搶�̃R�[�h-------------------------------------------------------------------------
#include <nn/gx.h>
#include <nn/math.h>
#include <nn/fs.h>
#include <nn/os.h>
#include <nn/init.h>
#include <nn/applet.h>
#include <nn/fnd/fnd_ExpHeap.h>

#include "TexUtils.h"
#include "takarabako.h"	
#include "demo.h"
#include "rabbit.h"

#include <nn/gd.h>

#define WAIT_VSYNC
#define PRINT(__msg) NN_LOG __msg


//Display buffers
extern u32 s_displaybuffer0[2];
extern u32 s_displaybuffer1[2];
extern u32 s_CurrentDisplaybuffer0;
extern u32 s_CurrentDisplaybuffer1;

//Depth stencil
extern nn::gd::DepthStencilState* depthStencil_Enabled;
extern nn::gd::DepthStencilState* depthStencil_Disabled;

//Texture combiner
extern nn::gd::CombinerState* s_texComState;

//FrameBuffers
extern nn::gd::Texture2DResource* s_texture2DResource_MainColorBuffer;
extern nn::gd::Texture2DResource* s_texture2DResource_MainDepthStencilBuffer;
extern nn::gd::RenderTarget* s_MainRenderTarget;
extern nn::gd::DepthStencilTarget* s_MainDepthStencilTarget;

//FrameBuffers *******************************************************************
extern nn::gd::Texture2DResource* s_texture2DResource_SubColorBuffer;
extern nn::gd::Texture2DResource* s_texture2DResource_SubDepthStencilBuffer;
extern nn::gd::RenderTarget* s_SubRenderTarget;
extern nn::gd::DepthStencilTarget* s_SubDepthStencilTarget;
//********************************************************************************

//Shader
extern nn::gd::ShaderBinary* shaderBinary;
extern nn::gd::ShaderPipeline* shaderPipeline;
extern nn::gd::Shader* vertexShader;

//Vertex input
extern nn::gd::InputLayout* inputLayout;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferColor;
extern nn::gd::VertexBufferResource* bufferTexCoord;
extern nn::gd::VertexBufferResource* bufferIndex;

extern nn::gd::VertexBufferResource* bufferTex4x4[];
extern nn::gd::VertexBufferResource* bufferCoord2;

extern nn::gd::VertexBufferResource* bufferTex256[];
extern nn::gd::VertexBufferResource* bufferCoord3;

extern nn::gd::UniformLocation s_shaderVariable_proj;
extern nn::gd::UniformLocation s_shaderVariable_view;

#define FPS_AVG_FRAME_COUNT 300
extern int s_curFpsCount;
extern double s_tmpFpsSum;

/* ExpHeap for app. */
extern nn::fnd::ExpHeap s_AppHeap;
extern uptr s_HeapForGx;
extern const u32 s_GxHeapSize;

//Linear
extern nn::gd::SamplerState* s_samplerDefault;		
extern nn::gd::SamplerState* s_samplerLinear;		
extern nn::gd::Texture2DResource* s_texture2D_res;	

int disp0_Format = 0, disp0_Width = 0, disp0_Height = 0;
int disp1_Format = 0, disp1_Width = 0, disp1_Height = 0;

nn::gd::BlendState* bd;

s64 GetTimeMicroSeconds();

extern nn::math::Vector3	g_posPolygon3D;
extern nn::math::Vector3	g_rotPolygon3D;

//--------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------
int Initialize(void);
void Finalize(void);
void Combiner(void);
void BlendStateDesc(void);

//--------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------
extern nn::gd::VertexBufferResource* bufferCoordBoss;
extern nn::gd::VertexBufferResource* bufferTexCoordBoss;
extern nn::gd::VertexBufferResource* bufferIndexBoss;
extern nn::gd::VertexBufferResource* bufferCoordHero;
extern nn::gd::VertexBufferResource* bufferTexCoordHero;
extern nn::gd::VertexBufferResource* bufferIndexHero;
extern nn::gd::VertexBufferResource* bufferCoordSlime;
extern nn::gd::VertexBufferResource* bufferTexCoordSlime;
extern nn::gd::VertexBufferResource* bufferIndexSlime;


//==============================================================
// �v���O�����{��
//==============================================================
//--------------------------------------------------------------
// ���_�f�[�^������
//--------------------------------------------------------------
void InitObjects(void)
{
//------------------------------------------�������玩��-------------------------------------------------

//-----------------------------------------------------------------------------------------------------

	u16 idxs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138, 139, 140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218};
    nnResult res;

	/* �|���S�����_ */
    float vertex_coord[] = {
		-0.5f * nn::gx::DISPLAY0_HEIGHT - 120.0f, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		0.5f * nn::gx::DISPLAY0_HEIGHT,-0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		-0.5f * nn::gx::DISPLAY0_HEIGHT - 120.0f,-0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,

		-0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		 0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		 0.5f * nn::gx::DISPLAY0_HEIGHT,-0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		-0.5f * nn::gx::DISPLAY0_HEIGHT,-0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,

		-64.0f, 64.0f, 0.0f, 1.0f,
		 64.0f, 64.0f, 0.0f, 1.0f,
		 64.0f,-64.0f, 0.0f, 1.0f,
		-64.0f,-64.0f, 0.0f, 1.0f,

        -128.0f, 256.0f, 0.0f, 1.0f,
         128.0f, 256.0f, 0.0f, 1.0f,
         128.0f,-256.0f, 0.0f, 1.0f,
		-128.0f,-256.0f, 0.0f, 1.0f,

		// 3D�p
		-2.0f, 2.0f, 0.0f, 1.0f,
         2.0f, 2.0f, 0.0f, 1.0f,
         2.0f,-2.0f, 0.0f, 1.0f,
		-2.0f,-2.0f, 0.0f, 1.0f,                //19

		// �n�ʗp
		-20.0f, 0.0f, 20.0f, 1.0f,
         20.0f, 0.0f, 20.0f, 1.0f,
         20.0f, 0.0f,-20.0f, 1.0f,
		-20.0f, 0.0f,-20.0f, 1.0f,

		//z���W1�Œ�
		-1.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
		1.0f,-1.0f,1.0f,1.0f,
		-1.0f,-1.0f,1.0f,1.0f,

		//z���W-1�Œ�
		1.0f,1.0f,-1.0f,1.0f,
		-1.0f,1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,-1.0f,1.0f,
		1.0f,-1.0f,-1.0f,1.0f,

		//x���W1�Œ�
		1.0f,1.0f,1.0f,1.0f,
		1.0f,-1.0f,1.0f,1.0f,
		1.0f,-1.0f,-1.0f,1.0f,
		1.0f,1.0f,-1.0f,1.0f,

		//x���W-1�Œ�
		-1.0f,-1.0f,1.0f,1.0f,
		-1.0f,1.0f,1.0f,1.0f,
		-1.0f,1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,-1.0f,1.0f,

		//y���W1�Œ�
		1.0f,1.0f,-1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
		-1.0f,1.0f,1.0f,1.0f,
		-1.0f,1.0f,-1.0f,1.0f,

		//y���W-1�Œ�
		1.0f,-1.0f,1.0f,1.0f,
		1.0f,-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,1.0f,1.0f,   //47

		//z���W1�Œ�			//�㕔��
		-0.5f,0.5f,0.5f,1.0f,
		0.5f,0.5f,0.5f,1.0f,
		0.5f,-0.5f,0.5f,1.0f,
		-0.5f,-0.5f,0.5f,1.0f,

		//z���W-1�Œ�
		0.5f,0.5f,-0.5f,1.0f,
		-0.5f,0.5f,-0.5f,1.0f,
		-0.5f,-0.5f,-0.5f,1.0f,
		0.5f,-0.5f,-0.5f,1.0f,

		//x���W1�Œ�
		0.5f,0.5f,0.5f,1.0f,
		0.5f,-0.5f,0.5f,1.0f,
		0.5f,-0.5f,-0.5f,1.0f,
		0.5f,0.5f,-0.5f,1.0f,

		//x���W-1�Œ�
		-0.5f,-0.5f,0.5f,1.0f,
		-0.5f,0.5f,0.5f,1.0f,
		-0.5f,0.5f,-0.5f,1.0f,
		-0.5f,-0.5f,-0.5f,1.0f,

		//y���W1�Œ�
		0.5f,0.5f,-0.5f,1.0f,
		0.5f,0.5f,0.5f,1.0f,
		-0.5f,0.5f,0.5f,1.0f,
		-0.5f,0.5f,-0.5f,1.0f,

		//y���W-1�Œ�
		0.5f,-0.5f,0.5f,1.0f,
		0.5f,-0.5f,-0.5f,1.0f,
		-0.5f,-0.5f,-0.5f,1.0f,
		-0.5f,-0.5f,0.5f,1.0f,

		
		//�e�e�̏������W1
		0.0f,-1.1f,0.0f,1.0f,
		1.0f,0.6f,0.0f,1.0f,
		0.0f,0.0f,1.6f,1.0f,

		//�e�e�̏������W2
		1.0f,-1.1f,0.0f,1.0f,
		1.0f,0.6f,0.0f,1.0f,
		1.0f,-0.6f,0.0f,1.0f,

		//�e�e�̏������W3
		1.0f,-1.1f,0.0f,1.0f,
		0.0f,0.0f,1.6f,1.0f,
		1.0f,-0.6f,0.0f,1.0f,

		//�e�e�̏������W4
		1.0f,0.6f,0.0f,1.0f,
		0.0f,0.0f,1.6f,1.0f,
		1.0f,-0.6f,0.0f,1.0f,     //83

		//�G���I
		-2.0f, 2.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f, 1.0f,
		2.0f, -2.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, 0.0f, 1.0f,  //87

		//�X���C���p
		-150.0f, -78.0f, 0.0f, 1.0f,
		150.0f, -78.0f, 0.0f, 1.0f,
		150.0f, -128.0f, 0.0f, 1.0f,
		-150.0f, -128.0f, 0.0f, 1.0f,//91

		//�X�e�[�^�X�p
		-200.0f, 120.0f, 0.0f, 1.0f,
		-50.0f, 120.0f, 0.0f, 1.0f,
	    -50.0f, 0.0f, 0.0f, 1.0f,
		-200.0f, 0.0f, 0.0f, 1.0f,//95

		//�R�}���h�p
		-160.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, -200.0f, 0.0f, 1.0f,
		-160.0f, -200.0f, 0.0f, 1.0f,//99

		//�R�}���h�J�[�\��1�p
		-250.0f, 0.0f, 0.0f, 1.0f,
		-160.0f, 0.0f, 0.0f, 1.0f,
		-160.0f, -200.0f, 0.0f, 1.0f,
		-250.0f, -200.0f, 0.0f, 1.0f,//103

		//�R�}���h�J�[�\��2�p
		-250.0f, -25.0f, 0.0f, 1.0f,
		-160.0f, -25.0f, 0.0f, 1.0f,
		-160.0f, -225.0f, 0.0f, 1.0f,
		-250.0f, -225.0f, 0.0f, 1.0f,//107

		//�R�}���h�J�[�\��3�p
		-250.0f, -50.0f, 0.0f, 1.0f,
		-160.0f, -50.0f, 0.0f, 1.0f,
		-160.0f, -250.0f, 0.0f, 1.0f,
		-250.0f, -250.0f, 0.0f, 1.0f,//111

		//�R�}���h�J�[�\��4�p
		-250.0f, -75.0f, 0.0f, 1.0f,
		-160.0f, -75.0f, 0.0f, 1.0f,
		-160.0f, -275.0f, 0.0f, 1.0f,
		-250.0f, -275.0f, 0.0f, 1.0f,//115

		//�X�e�[�^�X���ʕ\��
		-256.0f, 128.0f, 0.0f, 1.0f,
		256.0f, 128.0f, 0.0f, 1.0f,
		256.0f, -128.0f, 0.0f, 1.0f,
		-256.0f, -128.0f, 0.0f, 1.0f, //119

		// �X�e�[�W�\��
		-0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		0.5f * nn::gx::DISPLAY0_HEIGHT, -0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		-0.5f * nn::gx::DISPLAY0_HEIGHT, -0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,			//123

		//�X�e�[�W���ʕ\��
		5.0f, 5.0f, 0.0f, 1.0f,
		5.0f, -5.0f, 0.0f, 1.0f,
		-5.0f, -5.0f, 0.0f, 1.0f,
		-5.0f, 5.0f, 0.0f, 1.0f,//127

		
		//�{�X�\���p
		3.0f, 3.0f, 0.0f, 1.0f,
		3.0f, -3.0f, 0.0f, 1.0f,
		-3.0f, -3.0f, 0.0f, 1.0f,
		-3.0f, 3.0f, 0.0f, 1.0f, //131

		//�{�X�S�̕\���p
		-0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		0.5f * nn::gx::DISPLAY0_HEIGHT, -0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		-0.5f * nn::gx::DISPLAY0_HEIGHT, -0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,  // 135

		// �N���A���
		-0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		0.5f * nn::gx::DISPLAY0_HEIGHT, -0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,
		-0.5f * nn::gx::DISPLAY0_HEIGHT, -0.5f * nn::gx::DISPLAY0_WIDTH, 0.0f, 1.0f,  // 139

		// �o���l
		40.0f,   120.0f, 0.0f, 1.0f,    // 140
		200.0f, 120.0f, 0.0f, 1.0f,
		200.0f, 100.0f,  0.0f, 1.0f,
		40.0f,   100.0f,  0.0f, 1.0f,

		// �_���[�W�\��
		-150.0f, -78.0f, 0.0f, 1.0f,	// 144
		150.0f, -78.0f, 0.0f, 1.0f,
		150.0f, -128.0f, 0.0f, 1.0f,
		-150.0f, -128.0f, 0.0f, 1.0f,  

	};
	float vertex_coord2[] = {
		-16.0f,  16.0f, 0.0f, 1.0f,
		 16.0f,  16.0f, 0.0f, 1.0f,
		 16.0f, -16.0f, 0.0f, 1.0f,
		-16.0f, -16.0f, 0.0f, 1.0f   
	};
	float vertex_coord3[] = {
		-8.0f,  8.0f, 0.0f, 1.0f,
		 8.0f,  8.0f, 0.0f, 1.0f,
		 8.0f, -8.0f, 0.0f, 1.0f,
		-8.0f, -8.0f, 0.0f, 1.0f
	};


	/* �e�N�X�`���@*/
	float texture_coord[]={
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,		//3

		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,		//7

		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,		//11

		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,		//15

		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,		//19

		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		//4�@�������X�^�[�g
		0.0f, 0.5f, 0.0f,
		0.33f, 0.5f, 0.0f,
		0.33f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		//3
		0.66f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.5f, 0.0f,
		0.66f, 0.5f, 0.0f,

		//6
		0.66f, 0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.66f, 0.0f, 0.0f,

		//1
		0.0f, 1.0f, 0.0f,
		0.33f, 1.0f, 0.0f,
		0.33f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,			//39

		//2
		0.33f, 1.0f, 0.0f,
		0.66f, 1.0f, 0.0f,
		0.66f, 0.5f, 0.0f,
		0.33f, 0.5f, 0.0f,

		//5 �������I���
		0.33f, 0.5f, 0.0f,
		0.66f, 0.5f, 0.0f,
		0.66f, 0.0f, 0.0f,
		0.33f, 0.0f, 0.0f,

		//4�@�㕔���X�^�[�g
		0.0f, 0.5f, 0.0f,
		0.33f, 0.5f, 0.0f,
		0.33f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		//3
		0.66f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.5f, 0.0f,
		0.66f, 0.5f, 0.0f,

		//6
		0.66f, 0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.66f, 0.0f, 0.0f,			//59

		//1
		0.0f, 1.0f, 0.0f,
		0.33f, 1.0f, 0.0f,
		0.33f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,

		//2
		0.33f, 1.0f, 0.0f,
		0.66f, 1.0f, 0.0f,
		0.66f, 0.5f, 0.0f,
		0.33f, 0.5f, 0.0f,

		//5 �㕔���I���
		0.33f, 0.5f, 0.0f,
		0.66f, 0.5f, 0.0f,
		0.66f, 0.0f, 0.0f,
		0.33f, 0.0f, 0.0f,

		//�e�e�p1����
		0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.0f,
		

		//�e�e�p2�E��
		0.5f, 0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
		1.0f, 0.0f, 0.0f,
		

		//�e�e�p3����
		0.0f, 1.0f, 0.0f,
		0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,			//80
		

		//�e�e�p4�E��
		0.5f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.5f, 0.0f,
		
		//�G���I
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		
		//�X���C���p
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,


		//�X�e�[�^�X�p
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		//�R�}���h�p
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,			//99

		//�R�}���h�J�[�\��1�p
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		//�R�}���h�J�[�\��2�p
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		//�R�}���h�J�[�\��3�p
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		//�R�}���h�J�[�\��4�p
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		//�X�e�[�^�X���ʕ\��
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,			//119

		//�t�B�[���h�\��
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,			//123

		//�X�e�[�W����
		0.1953125f, 1.0f, 0.0f,
		0.2929687f, 1.0f, 0.0f,
		0.2929687f, 0.90234375f, 0.0f,
		0.1953125f, 0.90234375f, 0.0f,	//127

		//�{�X�\��
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,               //131

		//�{�X�S�̕\��
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,               //135

		//�{�X�S�̕\��
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,               //139

		// �o���l
		0.0f, 1.0f, 0.0f,               //140
		1.0f, 1.0f, 0.0f,
		1.0f, 0.84375, 0.0f,
		0.0f, 0.84375, 0.0f,

		//�_���[�W�p
		0.0f, 1.0f, 0.0f,				//144
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

	};
//----------------------------�����܂Ŏ���----------------------------------------------

//------------------------------------------------------------------------------------
	/*
	  �f�[�^�t�H�[�}�b�g�쐬
	  ��1����:�z��ID�@0:vertex_coord 1:texture_coord
	�@��2����:�f�[�^���
	�@��3����:�f�[�^�^
	  ��4����:��g�̃f�[�^�� 4:x,y,z,w  3:u,v,z
	  ��5����:�z��̃C���f�b�N�X(�ǂ�����g�p���邩)
	*/
	nn::gd::InputElementDescription descs[] = {
		{ 0, "aPosition", nn::gd::VertexInputStage::STREAM_TYPE_FLOAT, 4, 0},
		{ 1, "aTexCoord", nn::gd::VertexInputStage::STREAM_TYPE_FLOAT, 3, 0}
	};

	u32 strides[] = { sizeof(float) * 4, sizeof(float) * 3 };   /* ID�� ��g�̃f�[�^�T�C�Y */
	
	/*
	  inputLayout�ɑ΂��Ēl���Z�b�g
	  ��1����:�f�[�^�t�H�[�}�b�g�̔z��̃|�C���^
	�@��2����:�t�H�[�}�b�g��
	�@��3����:��g�̃f�[�^���̔z����������|�C���^
	  ��4����:�V�F�[�_�I�u�W�F�N�g�̃|�C���^
	  ��5����:��L�̃f�[�^���Z�b�g����\���̂̃|�C���^
	*/
    res = nn::gd::VertexInputStage::CreateInputLayout(descs, 2, strides, vertexShader, &inputLayout);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}


    nn::gd::VertexBufferResourceDescription desc;
    /* ���_ */
	desc.m_ByteSize = sizeof(vertex_coord);
    desc.m_MemLocation = nn::gd::Memory::FCRAM;
    res = nn::gd::Resource::CreateVertexBufferResource(&desc, vertex_coord, &bufferCoord);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	desc.m_ByteSize = sizeof(vertex_coord2);
    desc.m_MemLocation = nn::gd::Memory::FCRAM;
    res = nn::gd::Resource::CreateVertexBufferResource(&desc, vertex_coord2, &bufferCoord2);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	desc.m_ByteSize = sizeof(vertex_coord3);
    desc.m_MemLocation = nn::gd::Memory::FCRAM;
    res = nn::gd::Resource::CreateVertexBufferResource(&desc, vertex_coord3, &bufferCoord3);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	// �{�X
	desc.m_ByteSize = sizeof(vertex_data_takarabako);
    desc.m_MemLocation = nn::gd::Memory::FCRAM;
	res = nn::gd::Resource::CreateVertexBufferResource(&desc, vertex_data_takarabako, &bufferCoordBoss);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	desc.m_ByteSize = sizeof(texture_uv_data_takarabako);
    desc.m_MemLocation = nn::gd::Memory::FCRAM;
	res = nn::gd::Resource::CreateVertexBufferResource(&desc, texture_uv_data_takarabako, &bufferTexCoordBoss);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	desc.m_ByteSize = sizeof(idxs_takarabako);
	res = nn::gd::Resource::CreateVertexBufferResource(&desc, idxs_takarabako, &bufferIndexBoss);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	//	�q�[���[
	desc.m_ByteSize = sizeof(vertex_data_rabbit);
    desc.m_MemLocation = nn::gd::Memory::FCRAM;
	res = nn::gd::Resource::CreateVertexBufferResource(&desc, vertex_data_rabbit, &bufferCoordHero);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	desc.m_ByteSize = sizeof(texture_uv_data_rabbit);
    desc.m_MemLocation = nn::gd::Memory::FCRAM;
	res = nn::gd::Resource::CreateVertexBufferResource(&desc, texture_uv_data_rabbit, &bufferTexCoordHero);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	desc.m_ByteSize = sizeof(idxs_rabbit);
	res = nn::gd::Resource::CreateVertexBufferResource(&desc, idxs_rabbit, &bufferIndexHero);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	

	/* �e�N�X�`�� */
	desc.m_ByteSize = sizeof(texture_coord);
    desc.m_MemLocation = nn::gd::Memory::FCRAM;
    res = nn::gd::Resource::CreateVertexBufferResource(&desc, texture_coord, &bufferTexCoord);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	float uv[3 * 4];
	desc.m_ByteSize = sizeof(uv);
	desc.m_MemLocation = nn::gd::Memory::FCRAM;
	for (int v = 0; v < 4; ++v) {
		for (int u = 0; u < 4; ++u) {
			uv[0] = u * 0.25f; uv[1] = (v + 1) * 0.25f; uv[2] = 0.0f;
			uv[3] = (u + 1) * 0.25f; uv[4] = (v + 1) * 0.25f; uv[5] = 0.0f;
			uv[6] = (u + 1) * 0.25f; uv[7] = v * 0.25f; uv[8] = 0.0f;
			uv[9] = u * 0.25f; uv[10] = v * 0.25f; uv[11] = 0.0f;
			res = nn::gd::Resource::CreateVertexBufferResource(&desc, uv, &bufferTex4x4[v * 4 + u]);
			if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}
		}
	}
	for (int v = 0; v < 16; ++v) {
		for (int u = 0; u < 16; ++u) {
			uv[0] = u * 0.0625f; uv[1] = (v + 1) * 0.0625f; uv[2] = 0.0f;
			uv[3] = (u + 1) * 0.0625f; uv[4] = (v + 1) * 0.0625f; uv[5] = 0.0f;
			uv[6] = (u + 1) * 0.0625f; uv[7] = v * 0.0625f; uv[8] = 0.0f;
			uv[9] = u * 0.0625f; uv[10] = v * 0.0625f; uv[11] = 0.0f;
			res = nn::gd::Resource::CreateVertexBufferResource(&desc, uv, &bufferTex256[v * 16 + u]);
			if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}
		}
	}

	/* �C���f�b�N�X */
    desc.m_ByteSize = sizeof(idxs);
    res = nn::gd::Resource::CreateVertexBufferResource(&desc, idxs, &bufferIndex);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

	nn::gd::VertexBufferResource* buffers[] = {bufferCoord, bufferTexCoord};
	u32 offsets[] = {0, 0};

	nn::gd::VertexInputStage::SetVertexBuffers(0, 2, buffers, offsets);

    nn::gd::VertexInputStage::SetInputLayout(inputLayout);
        
    nn::gd::VertexInputStage::SetIndexBuffer(bufferIndex, nn::gd::VertexInputStage::INDEX_FORMAT_USHORT, 0);

	/* �v���~�e�B�u�̎w�� */
	nn::gd::VertexInputStage::SetPrimitiveTopology(nn::gd::VertexInputStage::PRIMITIVE_TOPOLOGY_TRIANGLEFAN);

}

//--------------------------------------------------------------
// �������e�ϊ� �r���[�|�[�g�ϊ��ݒ�@ �o�b�N�o�b�t�@�쐬
//--------------------------------------------------------------
void InitFrameMain(void)
{
    static nn::gd::TargetProperties mainRenderTargetProperty;
    nngxActiveDisplay(NN_GX_DISPLAY0);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_FORMAT, &disp0_Format);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_WIDTH, &disp0_Width);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_HEIGHT, &disp0_Height);

  	nngxActiveDisplay(NN_GX_DISPLAY1);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_FORMAT, &disp1_Format);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_WIDTH, &disp1_Width);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_HEIGHT, &disp1_Height);
    nn::gd::OutputStage::GetRenderTargetProperties(s_MainRenderTarget, &mainRenderTargetProperty);

    //Set the color/depthstencil targets
    nn::gd::OutputStage::SetRenderTarget(s_MainRenderTarget);
    nn::gd::OutputStage::SetDepthStencilTarget(s_MainDepthStencilTarget);
  
    //Set the viewport
    nn::gd::Viewport viewPort(0, 0, mainRenderTargetProperty.m_Width, mainRenderTargetProperty.m_Height);
    nn::gd::RasterizerStage::SetViewport(viewPort);

    //Projection matrix
    nn::math::Matrix44 proj;
    //nn::math::MTX44Frustum(&proj, -0.02f, 0.02f, -0.02f*nn::gx::DISPLAY0_HEIGHT/nn::gx::DISPLAY0_WIDTH, 0.02f*nn::gx::DISPLAY0_HEIGHT/nn::gx::DISPLAY0_WIDTH, 0.2f, 100.f);
	nn::math::MTX44Ortho(&proj, -0.5f * nn::gx::DISPLAY0_WIDTH, 0.5f * nn::gx::DISPLAY0_WIDTH, -0.5f * nn::gx::DISPLAY0_HEIGHT, 0.5f * nn::gx::DISPLAY0_HEIGHT, 0.2f, 100.0f);
    nn::gd::ShaderStage::SetShaderPipelineConstantFloat(shaderPipeline, s_shaderVariable_proj, static_cast<f32*>(proj));
    //���������e�ϊ��̂��߂̍s����V�F�[�_�p�C�v���C���ɃZ�b�g���Ă���

	BlendStateDesc();
}

//**********************************************************************************************************************************
void InitFrameSub(void)
{
    static nn::gd::TargetProperties subRenderTargetProperty;

	nngxActiveDisplay(NN_GX_DISPLAY1);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_FORMAT, &disp1_Format);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_WIDTH, &disp1_Width);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_HEIGHT, &disp1_Height);

	//s_SubRenderTarget�̏���mainRenderTargetProperty�ɓ����
    nn::gd::OutputStage::GetRenderTargetProperties(s_SubRenderTarget, &subRenderTargetProperty);

    //Set the color/depthstencil targets
    nn::gd::OutputStage::SetRenderTarget(s_SubRenderTarget);
    nn::gd::OutputStage::SetDepthStencilTarget(s_SubDepthStencilTarget);

	//Set the viewport
    nn::gd::Viewport viewPort(0, 0, subRenderTargetProperty.m_Width, subRenderTargetProperty.m_Height);
    nn::gd::RasterizerStage::SetViewport(viewPort);

    //Projection matrix
    nn::math::Matrix44 proj;
    //nn::math::MTX44Frustum(&proj, -0.02f, 0.02f, -0.02f*nn::gx::DISPLAY1_HEIGHT/nn::gx::DISPLAY1_WIDTH, 0.02f*nn::gx::DISPLAY1_HEIGHT/nn::gx::DISPLAY1_WIDTH, 0.2f, 100.f);
	nn::math::MTX44Ortho(&proj, -0.5f * nn::gx::DISPLAY1_WIDTH, 0.5f * nn::gx::DISPLAY1_WIDTH, -0.5f * nn::gx::DISPLAY1_HEIGHT, 0.5f * nn::gx::DISPLAY1_HEIGHT, 0.2f, 100.0f);
    nn::gd::ShaderStage::SetShaderPipelineConstantFloat(shaderPipeline, s_shaderVariable_proj, static_cast<f32*>(proj));
	//���������e�ϊ��̂��߂̍s����V�F�[�_�p�C�v���C���ɃZ�b�g���Ă���

	if (bd) {
		nn::gd::OutputStage::ReleaseBlendState(bd);
		bd = NULL;
	}
    nn::gd::BlendStateDescription desc;
    desc.ToDefault();
    desc.m_BlendType = nn::gd::OutputStage::BLEND_TYPE_BLENDING;
    desc.SetBlendFunc(	nn::gd::OutputStage::BLEND_FUNCTION_SRC_ALPHA,
							nn::gd::OutputStage::BLEND_FUNCTION_ONE_MINUS_SRC_ALPHA,
							nn::gd::OutputStage::BLEND_EQUATION_ADD);
    nn::gd::OutputStage::CreateBlendState(&desc, &bd);
	nn::gd::OutputStage::SetBlendState(bd);
}
//**********************************************************************************************************************************


//**********************************************************************************************************************************
//--------------------------------------------------------------
// �|���S���`�� ����
//--------------------------------------------------------------
void DrawPolygonMain(u32 p_prim,u32 p_index, bool b3D)
{   
	//Texture combiner
    nn::gd::CombinerDescription combiner;
    combiner.ToDefault();

	// ���̏��@TextureColor + �萔 + �萔
    combiner.SetSourceRGB(	nn::gd::CombinerStage::UNIT0,				//input combiner ID
							nn::gd::CombinerStage::SOURCE_TEXTURE0,		//input soruce RGB 0
							nn::gd::CombinerStage::SOURCE_TEXTURE0,		//input soruce RGB 1
							nn::gd::CombinerStage::SOURCE_CONSTANT);	//input soruce RGB 2
	// ���̏��@TextureAlpha + �萔 + �萔
	combiner.SetSourceAlpha(nn::gd::CombinerStage::UNIT0,				//input combiner ID
							nn::gd::CombinerStage::SOURCE_TEXTURE0,		//input source Alpha 0
							nn::gd::CombinerStage::SOURCE_CONSTANT,		//input source Alpha 1
							nn::gd::CombinerStage::SOURCE_CONSTANT);	//input source Alpha 2

	combiner.SetOperandRGB(	nn::gd::CombinerStage::UNIT0,					//combiner ID
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR ,	//input0 RGB�ł�RGB���ׂĎg�p
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,	//input1 RGB�ł�RGB���ׂĎg�p
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR);	//input2 RGB�ł�RGB���ׂĎg�p

    combiner.SetOperandAlpha(nn::gd::CombinerStage::UNIT0,					//combiner ID
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,	//input0 Alpha�ł̓A���t�@�̒l�𔽓]���Ďg��
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,	//input1 Alpha�ł̓A���t�@�̒l�����̂܂܎g��
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA);//input2 Alpha�ł̓A���t�@�̒l�����̂܂܎g��

	combiner.SetCombineRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::COMBINE_RGB_REPLACE);

    combiner.SetCombineAlpha(nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::COMBINE_ALPHA_REPLACE);

	combiner.SetCombinerInUse(nn::gd::CombinerStage::UNIT0, GD_TRUE);

	nn::gd::CombinerState* texComState;
	nn::gd::CombinerStage::CreateTextureCombinerState(&combiner, &texComState);
    nn::gd::CombinerStage::SetTextureCombinerState(texComState);

	if( b3D )   nn::gd::OutputStage::SetDepthStencilState(depthStencil_Enabled, 0);
	else		nn::gd::OutputStage::SetDepthStencilState(depthStencil_Disabled, 0);

    nn::gd::System::DrawIndexed(p_prim, p_index);

	nn::gd::CombinerStage::ReleaseTextureCombinerState(texComState);


}

//--------------------------------------------------------------
// �|���S���`�� �����
//--------------------------------------------------------------
void DrawPolygonSub(u32 p_prim,u32 p_index)
{   
    nn::gd::CombinerDescription combiner;
    combiner.ToDefault();

	// ���̏��@TextureColor + �萔 + �萔
    combiner.SetSourceRGB(	nn::gd::CombinerStage::UNIT0,				//input combiner ID
							nn::gd::CombinerStage::SOURCE_TEXTURE0,		//input soruce RGB 0
							nn::gd::CombinerStage::SOURCE_TEXTURE0,		//input soruce RGB 1
							nn::gd::CombinerStage::SOURCE_CONSTANT);	//input soruce RGB 2
	// ���̏��@TextureAlpha + �萔 + �萔
	combiner.SetSourceAlpha(nn::gd::CombinerStage::UNIT0,				//input combiner ID
							nn::gd::CombinerStage::SOURCE_TEXTURE0,		//input source Alpha 0
							nn::gd::CombinerStage::SOURCE_CONSTANT,		//input source Alpha 1
							nn::gd::CombinerStage::SOURCE_CONSTANT);	//input source Alpha 2

	combiner.SetOperandRGB(	nn::gd::CombinerStage::UNIT0,					//combiner ID
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR ,	//input0 RGB�ł�RGB���ׂĎg�p
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,	//input1 RGB�ł�RGB���ׂĎg�p
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR);	//input2 RGB�ł�RGB���ׂĎg�p

    combiner.SetOperandAlpha(nn::gd::CombinerStage::UNIT0,					//combiner ID
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,	//input0 Alpha�ł̓A���t�@�̒l�𔽓]���Ďg��
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,	//input1 Alpha�ł̓A���t�@�̒l�����̂܂܎g��
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA);//input2 Alpha�ł̓A���t�@�̒l�����̂܂܎g��

	combiner.SetCombineRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::COMBINE_RGB_REPLACE);

    combiner.SetCombineAlpha(nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::COMBINE_ALPHA_REPLACE);

	combiner.SetCombinerInUse(nn::gd::CombinerStage::UNIT0, GD_TRUE);

	nn::gd::CombinerState* texComState;
	nn::gd::CombinerStage::CreateTextureCombinerState(&combiner, &texComState);
    nn::gd::CombinerStage::SetTextureCombinerState(texComState);

//	tex_init();
    nn::gd::System::DrawIndexed(p_prim, p_index);
//	tex_finalize();

	nn::gd::CombinerStage::ReleaseTextureCombinerState(texComState);
}
//**********************************************************************************************************************************


//--------------------------------------------------------------
// �o�b�N�o�b�t�@�̓]�� ��ʏo��
//--------------------------------------------------------------
void AfterRender(void)
{
	//Transfer framebuffer to display buffer
	{
        int dstAddr;
        nngxActiveDisplay(NN_GX_DISPLAY0);
        nngxBindDisplaybuffer(s_displaybuffer0[s_CurrentDisplaybuffer0]);

		nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_ADDRESS, &dstAddr);
        nn::gd::Memory::CopyTexture2DResourceBlockToLinear(
            s_texture2DResource_MainColorBuffer,                    //source
            0,                                                      //sourceMipLevelIndex
            0,                                                      //srcOffestY
            (u8*)dstAddr,                                           //dstAddr
            disp0_Width,                                            //dstWidth
            disp0_Height,                                           //dstHeight
            nn::gd::Resource::NATIVE_FORMAT_RGB_888,                //dstFormat
            nn::gd::Memory::DOWNSCALING_NONE,                       //DownScalingMode
            GD_FALSE                                                //yFlip
        );
    }

	//*****************************************************************************************
	{
        int dstAddr;
		nngxActiveDisplay(NN_GX_DISPLAY1);
		nngxBindDisplaybuffer(s_displaybuffer1[s_CurrentDisplaybuffer1]);
	
		nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_ADDRESS, &dstAddr);
		nn::gd::Memory::CopyTexture2DResourceBlockToLinear(
			s_texture2DResource_SubColorBuffer,                    //source
			0,                                                      //sourceMipLevelIndex
			0,                                                      //srcOffestY
			(u8*)dstAddr,                                           //dstAddr
			disp1_Width,                                            //dstWidth
			disp1_Height,                                           //dstHeight
			nn::gd::Resource::NATIVE_FORMAT_RGB_888,                //dstFormat
			nn::gd::Memory::DOWNSCALING_NONE,                       //DownScalingMode
			GD_FALSE                                                //yFlip
		);
	}
	//******************************************************************************************

    // Wait till all command requests are processed
	//�`�揈���i�\���ł���悤�ɂȂ�܂Łj��҂�
    nngxWaitCmdlistDone();
	
	nngxSwapBuffers(NN_GX_DISPLAY_BOTH);//�`���I�������A�_�u���o�b�t�@��؂�ւ���B
	
	s_CurrentDisplaybuffer1 = (s_CurrentDisplaybuffer1 == 0 ? 1 : 0);
    s_CurrentDisplaybuffer0 = (s_CurrentDisplaybuffer0 == 0 ? 1 : 0);

    //Clear the command list
    nngxClearCmdlist();	
    nngxRunCmdlist();
}

//--------------------------------------------------------------
// �R���o�C�i�ݒ�
//--------------------------------------------------------------
void Combiner(void)
{
	nn::gd::CombinerDescription combiner;
    combiner.ToDefault();

	// ���̏��@TextureColor + �萔 + �萔
    combiner.SetSourceRGB(	nn::gd::CombinerStage::UNIT0,				//input combiner ID
							nn::gd::CombinerStage::SOURCE_TEXTURE0,		//input soruce RGB 0
							nn::gd::CombinerStage::SOURCE_CONSTANT,		//input soruce RGB 1
							nn::gd::CombinerStage::SOURCE_CONSTANT);	//input soruce RGB 2
	// ���̏��@TextureAlpha + �萔 + �萔
	combiner.SetSourceAlpha(nn::gd::CombinerStage::UNIT0,				//input combiner ID
							nn::gd::CombinerStage::SOURCE_TEXTURE0,		//input source Alpha 0
							nn::gd::CombinerStage::SOURCE_CONSTANT,		//input source Alpha 1
							nn::gd::CombinerStage::SOURCE_CONSTANT);	//input source Alpha 2

	combiner.SetOperandRGB(	nn::gd::CombinerStage::UNIT0,					//combiner ID
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR ,	//input0 RGB�ł�RGB���ׂĎg�p
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR,	//input1 RGB�ł�RGB���ׂĎg�p
							nn::gd::CombinerStage::OPERAND_RGB_SRC_COLOR);	//input2 RGB�ł�RGB���ׂĎg�p

    combiner.SetOperandAlpha(nn::gd::CombinerStage::UNIT0,					//combiner ID
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,	//input0 Alpha�ł̓A���t�@�̒l�𔽓]���Ďg��
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA,	//input1 Alpha�ł̓A���t�@�̒l�����̂܂܎g��
							nn::gd::CombinerStage::OPERAND_ALPHA_SRC_ALPHA);//input2 Alpha�ł̓A���t�@�̒l�����̂܂܎g��

	combiner.SetCombineRGB(	nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::COMBINE_RGB_REPLACE);

    combiner.SetCombineAlpha(nn::gd::CombinerStage::UNIT0,
							nn::gd::CombinerStage::COMBINE_ALPHA_REPLACE);

	combiner.SetCombinerInUse(nn::gd::CombinerStage::UNIT0, GD_TRUE);

	if (s_texComState) nn::gd::CombinerStage::ReleaseTextureCombinerState(s_texComState);
	nn::gd::CombinerStage::CreateTextureCombinerState(&combiner, &s_texComState);
    nn::gd::CombinerStage::SetTextureCombinerState(s_texComState);

}

//--------------------------------------------------------------
// �u�����h�X�e�C�g�ݒ�
//--------------------------------------------------------------
void BlendStateDesc(void)
{
	if (bd) {
		nn::gd::OutputStage::ReleaseBlendState(bd);
		bd = NULL;
	}
    nn::gd::BlendStateDescription desc;
    desc.ToDefault();
    desc.m_BlendType = nn::gd::OutputStage::BLEND_TYPE_BLENDING;
    desc.SetBlendFunc(	nn::gd::OutputStage::BLEND_FUNCTION_SRC_ALPHA,
	     				nn::gd::OutputStage::BLEND_FUNCTION_ONE_MINUS_SRC_ALPHA,
						nn::gd::OutputStage::BLEND_EQUATION_ADD);
    nn::gd::OutputStage::CreateBlendState(&desc, &bd);
    nn::gd::OutputStage::SetBlendState(bd);

	// �A���t�@�e�X�g
	nn::gd::OutputStage::SetAlphaTest(GD_TRUE, nn::gd::OutputStage::ALPHA_FUNCTION_GREATER, 0);
}

void SetFrame(int frame)
{
	nn::gd::VertexBufferResource* buffers[2];
	if (frame >= 0 && frame < 16) {
		buffers[0] = bufferCoord2;
		buffers[1] = bufferTex4x4[frame];
	} else {
		buffers[0] = bufferCoord;
		buffers[1] = bufferTexCoord;
	}
	u32 offsets[] = {0, 0};
	nn::gd::VertexInputStage::SetVertexBuffers(0, 2, buffers, offsets);
	nn::gd::VertexInputStage::SetIndexBuffer(bufferIndex, nn::gd::VertexInputStage::INDEX_FORMAT_USHORT, 0);

}

