#include <nn/gx.h>
#include <nn/math.h>
#include <nn/fs.h>
#include <nn/os.h>
#include <nn/init.h>
#include <nn/applet.h>
#include <nn/fnd/fnd_ExpHeap.h>
#include <stdio.h>

#include "Texture.h"
#include "TexUtils.h"
#include "demo.h"

#include <nn/gd.h>

//--------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------
//Linear
nn::gd::SamplerState* s_samplerDefault;
nn::gd::SamplerState* s_samplerLinear;
nn::gd::Texture2DResource* s_texture2D_res;
nn::gd::Texture2D* s_texture2D_TGA;
nn::gd::Texture2D* s_texture2D_BMP;
nn::gd::Texture2D* s_texture2D_BMP2;
nn::gd::Texture2D* s_texTitle;
nn::gd::Texture2D* s_texTitle_under;
nn::gd::Texture2D* s_texclear;
nn::gd::Texture2D* s_texNumber;
nn::gd::Texture2D* s_texLand;
nn::gd::Texture2D* s_texrabbit;
nn::gd::Texture2D* s_texsuraimu;
nn::gd::Texture2D* s_texsurasura;
nn::gd::Texture2D* s_texmetal;
nn::gd::Texture2D* s_texmonster;
nn::gd::Texture2D* s_texstatus;
nn::gd::Texture2D* s_texcommand;
nn::gd::Texture2D* s_texcursor;
nn::gd::Texture2D* s_texboss;
nn::gd::Texture2D* s_texstage_effect;
nn::gd::Texture2D* s_texboss_final;
nn::gd::Texture2D* s_texboss_finalwhole;
nn::gd::Texture2D* s_texgameover;
nn::gd::Texture2D* s_texfield_under;
nn::gd::Texture2D* s_texexperience;
nn::gd::Texture2D* s_texhero_damage;


//Texture combiner
extern nn::fnd::ExpHeap s_AppHeap;

static const char* g_dir = "rom:/resources/%s";

//--------------------------------------------------------------
// 関数プロトタイプ
//--------------------------------------------------------------
static nn::gd::Texture2D* LoadBMP(const char* fname);
static nn::gd::Texture2D* LoadTGA(const char* fname);

//==============================================================
// プログラム本編
//==============================================================
void Initialize_Tex(void)
{
	
	s_texNumber = LoadTGA("number.tga");
    if (!s_texNumber) {NN_PANIC("\n");}

	s_texTitle = LoadBMP("title.bmp");
    if (!s_texTitle) {NN_PANIC("\n");}

	s_texTitle_under = LoadBMP("title_under.bmp");
	if (!s_texTitle_under) { NN_PANIC("\n"); }

	s_texLand = LoadBMP("land.bmp");
	if( !s_texLand ){NN_PANIC("\n");}

	s_texrabbit = LoadTGA("rabbit.tga");
    if (!s_texrabbit) {NN_PANIC("\n");}

	s_texsuraimu = LoadTGA("suramu.tga");
	if (!s_texsuraimu) { NN_PANIC("\n"); }

	s_texsurasura = LoadBMP("suramu.bmp");
	if (!s_texsurasura) { NN_PANIC("\n"); }

	s_texmonster = LoadBMP("monster.bmp");
	if (!s_texmonster) { NN_PANIC("\n"); }

	s_texstatus = LoadBMP("status_final.bmp");
	if (!s_texstatus) { NN_PANIC("\n");  }

	s_texcommand = LoadTGA("command.tga");
	if (!s_texcommand) { NN_PANIC("\n"); }

	s_texcursor= LoadTGA("cursor.tga");
	if (!s_texcursor) { NN_PANIC("\n"); }

	s_texboss = LoadBMP("boss.bmp");
	if (!s_texboss) { NN_PANIC("\n"); }

	s_texstage_effect = LoadTGA("stage_effect.tga");
	if (!s_texstage_effect) { NN_PANIC("\n"); }

	s_texboss_final = LoadTGA("boss.tga");
	if (!s_texboss_final) { NN_PANIC("\n"); }

	s_texboss_finalwhole = LoadBMP("boss.bmp");
	if (!s_texboss_finalwhole) { NN_PANIC("\n"); }

	s_texclear = LoadBMP("clear.bmp");
	if (!s_texclear) { NN_PANIC("\n"); }

	s_texgameover = LoadBMP("gameover.bmp");
	if (!s_texgameover) { NN_PANIC("\n"); }

	s_texfield_under = LoadBMP("field_under.bmp");
	if (!s_texfield_under) { NN_PANIC("\n"); }

	s_texexperience = LoadBMP("experience.bmp");
	if (!s_texexperience) { NN_PANIC("\n"); }

	s_texhero_damage = LoadBMP("hero_damage.bmp");
	if (!s_texhero_damage) { NN_PANIC("\n"); }

	/*
	s_texmetal = LoadTGA("metal.tga");
	if (!s_texmetal) { NN_PANIC("\n"); }
	*/

//------------------------------------------------------------------------------------------------------------
//									ここから下は先生のコード
//------------------------------------------------------------------------------------------------------------

	//Sampler states
    nn::gd::SamplerStateDescription descDefault;
    descDefault.ToDefault();
    nn::gd::TextureStage::CreateSamplerState(&descDefault, &s_samplerDefault);

    nn::gd::SamplerStateDescription descSamplerState;
    descSamplerState.SetMinFilter(nn::gd::TextureStage::SAMPLER_MIN_FILTER_LINEAR);
    descSamplerState.SetMagFilter(nn::gd::TextureStage::SAMPLER_MAG_FILTER_LINEAR);
    descSamplerState.SetWrapS(nn::gd::TextureStage::SAMPLER_WRAP_REPEAT);
    descSamplerState.SetWrapT(nn::gd::TextureStage::SAMPLER_WRAP_REPEAT);
    descSamplerState.SetBorderColor(0.0f, 1.0f, 0.0f, 1.0f);
    nn::gd::TextureStage::CreateSamplerState(&descSamplerState, &s_samplerLinear);
}

nn::gd::Texture2D* LoadBMP(const char* fname)
{
	char filename[260];
	sprintf(filename, g_dir, fname);

	u32 width = 0; u32 height = 0; u32 textureWidth = 0; u32 textureHeight = 0;
	nn::gd::Texture2D* pTex = NULL;

	u8* textureDataPtr = GetTextureData_BMP(filename, width, height,
		textureWidth, textureHeight, false, &s_AppHeap);

	nn::gd::Texture2DResourceDescription Text2DResDesc2 = {textureWidth, textureHeight,
		1, nn::gd::Resource::NATIVE_FORMAT_RGB_888, nn::gd::Memory::LAYOUT_BLOCK_8,
		nn::gd::Memory::VRAMA};
	nnResult res = nn::gd::Resource::CreateTexture2DResource(&Text2DResDesc2,
		textureDataPtr, GD_FALSE, &s_texture2D_res);
	s_AppHeap.Free(textureDataPtr);
	if (!GD_NNRESULT_IS_FAILURE(res)) {
		nn::gd::Texture2DDescription tex2DDesc = {0, -1};
		nn::gd::TextureStage::CreateTexture2D(s_texture2D_res, &tex2DDesc, &pTex);
		if (GD_NNRESULT_IS_FAILURE(res)) {
			pTex = NULL;
		}
	}

	return pTex;
}

nn::gd::Texture2D* LoadTGA(const char* fname)
{
	u32 type = 2;
	u32 format = 0;
    u32 width = 0; u32 height = 0; u32 bpp = 4;
	nn::gd::Resource::Format fmt = nn::gd::Resource::FORMAT_RGBA_8888;
	nn::gd::Resource::NativeFormat nf = nn::gd::Resource::NATIVE_FORMAT_RGBA_8888;
	nn::gd::Texture2D* pTex = NULL;

	char filename[260];
	sprintf(filename, g_dir, fname);
	u8* textureDataPtr = GetTextureData_TGA(filename, width, height, format, type, &s_AppHeap);
	if (format == GL_RGB) {
		bpp = 3;
		fmt = nn::gd::Resource::FORMAT_RGB_888;
		nf = nn::gd::Resource::NATIVE_FORMAT_RGB_888;
	}
	u8* textureDataConvert = static_cast<u8*>(s_AppHeap.Allocate(width * height * bpp));

	nn::gd::Resource::Helper::ConvertTextureResourceToNativeFormat(
		fmt, width, height, textureDataPtr, textureDataConvert, NULL);
	s_AppHeap.Free(textureDataPtr);

	nn::gd::Texture2DResourceDescription Text2DResDesc = {width, height,
		1, nf, nn::gd::Memory::LAYOUT_BLOCK_8, nn::gd::Memory::VRAMA};

	nnResult res = nn::gd::Resource::CreateTexture2DResource(&Text2DResDesc,
		textureDataConvert, GD_FALSE, &s_texture2D_res);
	s_AppHeap.Free(textureDataConvert);
	if (!GD_NNRESULT_IS_FAILURE(res)) {
		nn::gd::Texture2DDescription tex2DDesc = {0, -1};
		res = nn::gd::TextureStage::CreateTexture2D(s_texture2D_res, &tex2DDesc, &pTex);
		if (GD_NNRESULT_IS_FAILURE(res)) {
			pTex = NULL;
		}
	}

	return pTex;
}

// 生成済テクスチャの内容を差し替える(同一サイズの画像のみ可能)
bool ChangeBMP(nn::gd::Texture2D* pTex, const char* fname)
{
	u32 width = 0; u32 height = 0; u32 texWidth = 0; u32 texHeight = 0;

	char filename[260];
	sprintf(filename, g_dir, fname);
	u8* textureDataPtr = GetTextureData_BMP(filename, width, height,
		texWidth, texHeight, false, &s_AppHeap);

	nn::gd::Texture2DProperties prop;
	nn::gd::TextureStage::GetTexture2DProperties(pTex, &prop);

	// フォーマットチェック
	if (prop.m_Width != texWidth || prop.m_Height != texHeight ||
		prop.m_Format != nn::gd::Resource::NATIVE_FORMAT_RGB_888) {
		// 形式が異なるとコピーできない
		s_AppHeap.Free(textureDataPtr);
		return false;
	}

	// データをCOPY 転送元textureDataPtr 転送先pTex 転送量256 * 256 * 3
	nngxAddVramDmaCommand(textureDataPtr, prop.m_MemAddr, texWidth * texHeight * 3);
	// VRAMに送り終わったので解放
	s_AppHeap.Free(textureDataPtr);

	return true;
}

// 生成済テクスチャの内容を差し替える(同一サイズの画像のみ可能)
bool ChangeTGA(nn::gd::Texture2D* pTex, const char* fname)
{
	u32 width = 0; u32 height = 0;
	u32 format = 0;
	u32 type = 2;
	u32 bpp = 4;
	nn::gd::Resource::Format fmt = nn::gd::Resource::FORMAT_RGBA_8888;
	nn::gd::Resource::NativeFormat nf = nn::gd::Resource::NATIVE_FORMAT_RGBA_8888;

	char filename[260];
	sprintf(filename, g_dir, fname);
	u8* textureDataPtr = GetTextureData_TGA(filename, width, height, format, type, &s_AppHeap);
	if (format == GL_RGB) {
		bpp = 3;
		fmt = nn::gd::Resource::FORMAT_RGB_888;
		nf = nn::gd::Resource::NATIVE_FORMAT_RGB_888;
	}
	u8* textureDataConvert = static_cast<u8*>(s_AppHeap.Allocate(width * height * bpp));

	nn::gd::Resource::Helper::ConvertTextureResourceToNativeFormat(fmt, width, height, textureDataPtr, textureDataConvert, NULL);
	// コンバートが終わったので解放
	s_AppHeap.Free(textureDataPtr);

	nn::gd::Texture2DProperties prop;
	nn::gd::TextureStage::GetTexture2DProperties(pTex, &prop);

	// フォーマットチェック
	if (prop.m_Width != width || prop.m_Height != height || prop.m_Format != nf) {
		// 形式が異なるとコピーできない
		s_AppHeap.Free(textureDataConvert);
		return false;
	}

	// データをCOPY 転送元textureDataConvert 転送先pTex 転送量256 * 256 * 4
	nngxAddVramDmaCommand(textureDataConvert, prop.m_MemAddr, width * height * bpp);
	// VRAMに送り終わったので解放
	s_AppHeap.Free(textureDataConvert);

	return true;
}
