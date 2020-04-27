#ifndef ___H_TEXTURE
#define ___H_TEXTURE

#include <nn/gd.h>
//--------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------
extern nn::gd::SamplerState* s_samplerDefault;
extern nn::gd::Texture2D* s_texture2D_BMP2;
extern nn::gd::Texture2D* s_texture2D_BMP;
extern nn::gd::Texture2D* s_texture2D_TGA;
extern nn::gd::Texture2D* s_texEnemy1;
extern nn::gd::Texture2D* s_texEnemy2;
extern nn::gd::Texture2D* s_texNumber;
extern nn::gd::Texture2D* s_texTitle;
extern nn::gd::Texture2D* s_texTitle_under;
extern nn::gd::Texture2D* s_texclear;
extern nn::gd::Texture2D* s_texEndRoll;
extern nn::gd::Texture2D* s_texFlare;
extern nn::gd::Texture2D* s_texSmoke;
extern nn::gd::Texture2D* s_texWater;
extern nn::gd::Texture2D* s_texLand;
extern nn::gd::Texture2D* s_texdice;
extern nn::gd::Texture2D* s_textakarabako;
extern nn::gd::Texture2D* s_texrabbit;
extern nn::gd::Texture2D* s_texsuraimu;
extern nn::gd::Texture2D* s_texsurasura;
extern nn::gd::Texture2D* s_texmetal;
extern nn::gd::Texture2D* s_texmonster;
extern nn::gd::Texture2D* s_texstatus;
extern nn::gd::Texture2D* s_texcommand;
extern nn::gd::Texture2D* s_texcursor;
extern nn::gd::Texture2D* s_texboss;
extern nn::gd::Texture2D* s_texstage_effect;
extern nn::gd::Texture2D* s_texboss_final;
extern nn::gd::Texture2D* s_texboss_finalwhole;
extern nn::gd::Texture2D* s_texclear;
extern nn::gd::Texture2D* s_texgameover;
extern nn::gd::Texture2D* s_texfield_under;
extern nn::gd::Texture2D* s_texexperience;
extern nn::gd::Texture2D* s_texhero_damage;

//--------------------------------------------------------------
// 関数プロトタイプ
//--------------------------------------------------------------
bool ChangeBMP(nn::gd::Texture2D* pTex, const char* fname);                     //??????
bool ChangeTGA(nn::gd::Texture2D* pTex, const char* fname);                     //??????

#endif // ___H_TEXTURE
