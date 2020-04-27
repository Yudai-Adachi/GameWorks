//==============================================================
//  GxInit.cpp
//
//--------------------------------------------------------------
//                                    Author : Nakagawa Hiroki
//                                             Michiba  Hiroaki
//                                             HAL OSAKA
//==============================================================

//==============================================================
// インクルード
//==============================================================

//------------------------先生のコード-------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------

#include <nn/gx.h>
#include <nn/math.h>
#include <nn/fs.h>
#include <nn/os.h>
#include <nn/init.h>
#include <nn/applet.h>
#include <nn/fnd/fnd_ExpHeap.h>

#include "TexUtils.h"
#include "demo.h"
#include "Polygon3D.h"
#include "Land.h"
#include "Enemy.h"
#include "Boss.h"
#include "Status.h"
#include "Boss.h"

#include <nn/gd.h>

//--------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------
void InitObjects(void);
void Initialize_Tex(void);

//Display buffers
u32 s_displaybuffer0[2];
u32 s_displaybuffer1[2];
u32 s_CurrentDisplaybuffer0 = 0;
u32 s_CurrentDisplaybuffer1 = 0;

//Depth stencil
nn::gd::DepthStencilState* depthStencil_Enabled = 0;
nn::gd::DepthStencilState* depthStencil_Disabled = 0;

//Texture combiner
nn::gd::CombinerState* s_texComState = 0;

//FrameBuffers_Main
nn::gd::Texture2DResource* s_texture2DResource_MainColorBuffer = 0;
nn::gd::Texture2DResource* s_texture2DResource_MainDepthStencilBuffer = 0;
nn::gd::RenderTarget* s_MainRenderTarget = 0;
nn::gd::DepthStencilTarget* s_MainDepthStencilTarget = 0;

//FrameBuffers_Sub ************************************************************
nn::gd::Texture2DResource* s_texture2DResource_SubColorBuffer = 0;
nn::gd::Texture2DResource* s_texture2DResource_SubDepthStencilBuffer = 0;
nn::gd::RenderTarget* s_SubRenderTarget = 0;
nn::gd::DepthStencilTarget* s_SubDepthStencilTarget = 0;
//*****************************************************************************

//Shader
nn::gd::ShaderBinary* shaderBinary = 0;
nn::gd::ShaderPipeline* shaderPipeline = 0;
nn::gd::Shader* vertexShader = 0;

//Vertex input
nn::gd::InputLayout* inputLayout = 0;
nn::gd::VertexBufferResource* bufferCoord = 0;
nn::gd::VertexBufferResource* bufferColor = 0;
nn::gd::VertexBufferResource* bufferTexCoord = 0;
nn::gd::VertexBufferResource* bufferIndex = 0;

nn::gd::VertexBufferResource* bufferTex4x4[16] = {0};
nn::gd::VertexBufferResource* bufferCoord2 = 0;

nn::gd::VertexBufferResource* bufferTex256[256] = {0};
nn::gd::VertexBufferResource* bufferCoord3 = 0;

nn::gd::UniformLocation s_shaderVariable_proj;
nn::gd::UniformLocation s_shaderVariable_view;

extern nn::gd::Texture2DResource* s_texture2D_res;

/* ExpHeap for app. */
nn::fnd::ExpHeap s_AppHeap;
uptr s_HeapForGx;
const u32 s_GxHeapSize = 0x400000;


extern CBoss *boss;
//--------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------
u32 s_CmdlistID;

#define PRINT(__msg) NN_LOG __msg

nn::gd::VertexBufferResource* bufferCoordBoss = 0;
nn::gd::VertexBufferResource* bufferTexCoordBoss = 0;
nn::gd::VertexBufferResource* bufferIndexBoss = 0;

nn::gd::VertexBufferResource* bufferCoordHero = 0;
nn::gd::VertexBufferResource* bufferTexCoordHero = 0;
nn::gd::VertexBufferResource* bufferIndexHero = 0;

nn::gd::VertexBufferResource* bufferCoordSlime = 0;
nn::gd::VertexBufferResource* bufferTexCoordSlime = 0;
nn::gd::VertexBufferResource* bufferIndexSlime = 0;


//==============================================================
// プログラム本編
//==============================================================
//gdAPI API callback function
void callbackErrorFunction(nnResult result, const char* funcname)
{
    char* str = 0;
    NN_UNUSED_VAR(str);
    NN_UNUSED_VAR(funcname);

    if (funcname != NULL) {NN_LOG("Return from \"%s\"\n",  funcname);}
    if ((str = nn::gd::System::GetErrorStringFromResult(result)) != NULL) {NN_LOG("Error: %s\n", str);}

	NN_ASSERTMSG( 0, "callBack Error function called.");}

void InitShader()
{
    nn::fs::FileReader file(L"rom:/shader.shbin");
    size_t fileSize = file.GetSize();
    void* buf = s_AppHeap.Allocate(fileSize);

    s32 read = file.Read(buf, fileSize);
    nnResult res;
    res = nn::gd::ShaderStage::CreateShaderBinary(buf, read, &shaderBinary);              if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}
    res = nn::gd::ShaderStage::CreateShader(shaderBinary, 0, &vertexShader);              if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}
    res = nn::gd::ShaderStage::CreateShaderPipeline(vertexShader, NULL, &shaderPipeline); if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

    s_shaderVariable_proj = nn::gd::ShaderStage::GetShaderUniformLocation(shaderPipeline, "uProjection");
    s_shaderVariable_view = nn::gd::ShaderStage::GetShaderUniformLocation(shaderPipeline, "uModelView");
    NN_ASSERT(s_shaderVariable_proj.IsValid());
    NN_ASSERT(s_shaderVariable_view.IsValid());

    nn::gd::ShaderStage::SetShaderPipeline(shaderPipeline);

    file.Finalize();
    s_AppHeap.Free(buf);
}

void Initialize_GD()
{
    //common
    nn::gd::DepthStencilStateDescription desc;
    desc.ToDefault();
    desc.m_DepthEnable = GD_FALSE;
    desc.m_DepthFunc = nn::gd::OutputStage::DEPTH_FUNCTION_LESS;
    nn::gd::OutputStage::CreateDepthStencilState(&desc, &depthStencil_Disabled);
    nn::gd::OutputStage::SetDepthStencilState(depthStencil_Disabled, 0);
    nn::gd::RasterizerStage::SetCulling(nn::gd::RasterizerStage::CULLING_NONE);
}
void Initialize_GD_3D()
{
    //common
    nn::gd::DepthStencilStateDescription desc;
    desc.ToDefault();
    desc.m_DepthEnable = GD_TRUE;
    desc.m_DepthFunc = nn::gd::OutputStage::DEPTH_FUNCTION_LESS;
    nn::gd::OutputStage::CreateDepthStencilState(&desc, &depthStencil_Enabled);
    nn::gd::OutputStage::SetDepthStencilState(depthStencil_Enabled, 0);
    nn::gd::RasterizerStage::SetCulling(nn::gd::RasterizerStage::CULLING_NONE);
}

//FPS management
#define FPS_AVG_FRAME_COUNT 300
int s_curFpsCount = 0;
double s_tmpFpsSum = 0.0;

s64 GetTimeMicroSeconds()
{
    nn::os::Tick ticks = nn::os::Tick::GetSystemCurrent();
    nn::fnd::TimeSpan TimeSpan = ticks;
    return TimeSpan.GetMicroSeconds();
}


void Finalize()
{
	// 3D後片付け処理
	UninitPolygon3D();
	//UninitEnemy3D();
	UninitLand();
	boss -> UninitBoss();
	UninitStatus();

    nngxStopCmdlist();

    //Release gd objects
    if (s_texComState) nn::gd::CombinerStage::ReleaseTextureCombinerState(s_texComState);

    if (depthStencil_Enabled) nn::gd::OutputStage::ReleaseDepthStencilState(depthStencil_Enabled);
    if (depthStencil_Disabled) nn::gd::OutputStage::ReleaseDepthStencilState(depthStencil_Disabled);

    if (bufferCoord) nn::gd::Resource::ReleaseVertexBufferResource(bufferCoord);
    if (bufferColor) nn::gd::Resource::ReleaseVertexBufferResource(bufferColor);
    if (bufferIndex) nn::gd::Resource::ReleaseVertexBufferResource(bufferIndex);
    if (inputLayout) nn::gd::VertexInputStage::ReleaseInputLayout(inputLayout);

    if (shaderPipeline) nn::gd::ShaderStage::ReleaseShaderPipeline(shaderPipeline);
    if (vertexShader) nn::gd::ShaderStage::ReleaseShader(vertexShader);
    if (shaderBinary) nn::gd::ShaderStage::ReleaseShaderBinary(shaderBinary);

    if (s_MainRenderTarget) nn::gd::OutputStage::ReleaseRenderTarget(s_MainRenderTarget);
    if (s_texture2DResource_MainColorBuffer) nn::gd::Resource::ReleaseTexture2DResource(s_texture2DResource_MainColorBuffer);
    if (s_MainDepthStencilTarget) nn::gd::OutputStage::ReleaseDepthStencilTarget(s_MainDepthStencilTarget);
    if (s_texture2DResource_MainDepthStencilBuffer) nn::gd::Resource::ReleaseTexture2DResource(s_texture2DResource_MainDepthStencilBuffer);

    if (s_texture2D_res) nn::gd::Resource::ReleaseTexture2DResource(s_texture2D_res);
	if (bufferTexCoord) nn::gd::Resource::ReleaseVertexBufferResource(bufferTexCoord);

	for (int i = 0; i < 16; ++i) {
		if (bufferTex4x4[i]) nn::gd::Resource::ReleaseVertexBufferResource(bufferTex4x4[i]);
	}
    if (bufferCoord2) nn::gd::Resource::ReleaseVertexBufferResource(bufferCoord2);

	for (int i = 0; i < 256; ++i) {
		if (bufferTex256[i]) nn::gd::Resource::ReleaseVertexBufferResource(bufferTex256[i]);
	}
    if (bufferCoord3) nn::gd::Resource::ReleaseVertexBufferResource(bufferCoord3);

	extern nn::gd::BlendState* bd;
	if (bd) {
		nn::gd::OutputStage::ReleaseBlendState(bd);
		bd = NULL;
	}
	
	if (bufferCoordBoss)	nn::gd::Resource::ReleaseVertexBufferResource(bufferCoordBoss);
	if (bufferTexCoordBoss)	nn::gd::Resource::ReleaseVertexBufferResource(bufferTexCoordBoss);
	if (bufferIndexBoss)	nn::gd::Resource::ReleaseVertexBufferResource(bufferIndexBoss);

	if (bufferCoordHero)	nn::gd::Resource::ReleaseVertexBufferResource(bufferCoordHero);
	if (bufferTexCoordHero)	nn::gd::Resource::ReleaseVertexBufferResource(bufferTexCoordHero);
	if (bufferIndexHero)	nn::gd::Resource::ReleaseVertexBufferResource(bufferIndexHero);

	if (bufferCoordSlime)	nn::gd::Resource::ReleaseVertexBufferResource(bufferCoordSlime);
	if (bufferTexCoordSlime)	nn::gd::Resource::ReleaseVertexBufferResource(bufferTexCoordSlime);
	if (bufferIndexSlime)	nn::gd::Resource::ReleaseVertexBufferResource(bufferIndexSlime);


    //release gd api
    nn::gd::System::Finalize();

    //release display buffers
    nngxBindDisplaybuffer(0);
    nngxDeleteDisplaybuffers(2, s_displaybuffer0);
    nngxDeleteDisplaybuffers(2, s_displaybuffer1);
    s_displaybuffer0[0] = s_displaybuffer0[1] = 0;
    s_displaybuffer1[0] = s_displaybuffer1[1] = 0;

   // Stop command list execution.
    nngxStopCmdlist();

    //release commad list
    nngxDeleteCmdlists(1, &s_CmdlistID);

    // Finalize DMPGL
    nngxFinalize();
    
    //release memory
    demo::FinalizeMemoryManager();
}

/* initialization */
int Initialize(void)
{
    nn::fs::Initialize();

    //init memory
    const size_t ROMFS_BUFFER_SIZE = 1024 * 64;
    static char buffer[ROMFS_BUFFER_SIZE];
    NN_UTIL_PANIC_IF_FAILED(nn::fs::MountRom(16, 16, buffer, ROMFS_BUFFER_SIZE));

    s_AppHeap.Initialize(nn::os::GetDeviceMemoryAddress(), nn::os::GetDeviceMemorySize() );
    s_HeapForGx = reinterpret_cast<uptr>(s_AppHeap.Allocate(s_GxHeapSize));

    demo::InitializeMemoryManager(s_HeapForGx, s_GxHeapSize);
    nngxInitialize(demo::GetAllocator, demo::GetDeallocator);

    // Init command list
    nngxGenCmdlists(1, &s_CmdlistID);
    nngxBindCmdlist(s_CmdlistID);
    nngxCmdlistStorage(0x40000, 128);

    //We run the command list now in order that any new request inserted can be executed in parallel
    nngxRunCmdlist();

    // Init display buffers
    nngxGenDisplaybuffers(2, s_displaybuffer0);
    nngxActiveDisplay(NN_GX_DISPLAY0);
    nngxDisplayEnv(0, 0);
    nngxBindDisplaybuffer(s_displaybuffer0[0]);
    nngxDisplaybufferStorage(GL_RGB8_OES, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT, NN_GX_MEM_FCRAM);

    nngxBindDisplaybuffer(s_displaybuffer0[1]);
    nngxDisplaybufferStorage(GL_RGB8_OES, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT, NN_GX_MEM_FCRAM);

    nngxGenDisplaybuffers(2, s_displaybuffer1);
    nngxActiveDisplay(NN_GX_DISPLAY1);
    nngxDisplayEnv(0, 0);
    nngxBindDisplaybuffer(s_displaybuffer1[0]);
    nngxDisplaybufferStorage(GL_RGB8_OES, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT, NN_GX_MEM_FCRAM);

    nngxBindDisplaybuffer(s_displaybuffer1[1]);
    nngxDisplaybufferStorage(GL_RGB8_OES, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT, NN_GX_MEM_FCRAM);

    //Init GD API
    nnResult result = nn::gd::System::Initialize();
    if ( GD_NNRESULT_IS_FAILURE(result) ) return -1;
    nn::gd::System::SetCallbackFunctionError(callbackErrorFunction);

    /* Init main frame buffers */
    nn::gd::Texture2DResourceDescription Text2DResDesc_ColorBuffer = {nn::gx::DISPLAY0_WIDTH, 
		                                                              nn::gx::DISPLAY0_HEIGHT, 
																	  1, 
																	  nn::gd::Resource::NATIVE_FORMAT_RGBA_8888, 
																	  nn::gd::Memory::LAYOUT_BLOCK_8, 
																	  nn::gd::Memory::VRAMA
	                                                                 };
    nnResult res = nn::gd::Resource::CreateTexture2DResource(&Text2DResDesc_ColorBuffer, 0, GD_FALSE, &s_texture2DResource_MainColorBuffer);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

    nn::gd::RenderTargetDescription descRenderTarget = {0};
    res = nn::gd::OutputStage::CreateRenderTarget(s_texture2DResource_MainColorBuffer, &descRenderTarget, &s_MainRenderTarget);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

    //Depth Stencil buffer
    nn::gd::Texture2DResourceDescription Text2DResDesc_DepthStencilBuffer = {nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT, 1, nn::gd::Resource::NATIVE_FORMAT_DEPTH_24_STENCIL_8, nn::gd::Memory::LAYOUT_BLOCK_8, nn::gd::Memory::VRAMB};
    res = nn::gd::Resource::CreateTexture2DResource(&Text2DResDesc_DepthStencilBuffer, 0, GD_FALSE, &s_texture2DResource_MainDepthStencilBuffer);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

    nn::gd::DepthStencilTargetDescription descDepthStencilTarget = {0};
    res = nn::gd::OutputStage::CreateDepthStencilTarget(s_texture2DResource_MainDepthStencilBuffer, &descDepthStencilTarget, &s_MainDepthStencilTarget);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}


    /* Init sub frame buffers */
	//**************************************************************************************************************************************************
    nn::gd::Texture2DResourceDescription Text2DResDesc_ColorBuffer2 = {nn::gx::DISPLAY1_WIDTH,
																		nn::gx::DISPLAY1_HEIGHT,
																		1,
																		nn::gd::Resource::NATIVE_FORMAT_RGBA_8888,
																		nn::gd::Memory::LAYOUT_BLOCK_8,
																		nn::gd::Memory::VRAMA};
    res = nn::gd::Resource::CreateTexture2DResource(&Text2DResDesc_ColorBuffer2, 0, GD_FALSE, &s_texture2DResource_SubColorBuffer);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

    nn::gd::RenderTargetDescription descRenderTarget2 = {0};
    res = nn::gd::OutputStage::CreateRenderTarget(s_texture2DResource_SubColorBuffer, &descRenderTarget2, &s_SubRenderTarget);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

    //Depth Stencil buffer
    nn::gd::Texture2DResourceDescription Text2DResDesc_DepthStencilBuffer2 = {nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT, 1, nn::gd::Resource::NATIVE_FORMAT_DEPTH_24_STENCIL_8, nn::gd::Memory::LAYOUT_BLOCK_8, nn::gd::Memory::VRAMB};
    res = nn::gd::Resource::CreateTexture2DResource(&Text2DResDesc_DepthStencilBuffer2, 0, GD_FALSE, &s_texture2DResource_SubDepthStencilBuffer);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}

    nn::gd::DepthStencilTargetDescription descDepthStencilTarget2 = {0};
    res = nn::gd::OutputStage::CreateDepthStencilTarget(s_texture2DResource_SubDepthStencilBuffer, &descDepthStencilTarget2, &s_SubDepthStencilTarget);
    if ( GD_NNRESULT_IS_FAILURE(res) ) {NN_PANIC("\n");}
	//**************************************************************************************************************************************************


	InitShader();
    InitObjects();
    Initialize_GD();
	Initialize_GD_3D();
	Initialize_Tex(); /* テクスチャ初期化 */

	// 3D初期化処理
	InitPolygon3D();
	InitLand();
	boss -> InitBoss();
	InitStatus();

    return 0;
}
