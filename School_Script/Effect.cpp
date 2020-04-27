#include "Effect.h"
#include <nn/gd.h>
#include <nn/snd.h>
#include "Land.h"
#include "Main.h"
#include "Texture.h"
#include "slime.h"
#include "Boss.h"
#include "Polygon3D.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;

static int			g_nAlpha = 255;

static nn::math::Vector3	g_posEffect(45.0f, 70.0f, 0.5f);
static nn::math::Vector3	g_rotEffect(0.0f, 0.0f, 0.0f);

extern nn::math::Vector3	g_posPolygon3D;
extern nn::math::Vector3	g_rotPolygon3D;

CEffect::CEffect()
{
}


CEffect::~CEffect()
{
}

//??????????????
void CEffect::BossStage()
{
	g_posPolygon3D = GetPosPolygon3D();
	Change_3D();
	if (g_nAlpha) {
		nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texstage_effect);
		CreateMatrix3D(g_posEffect, g_rotEffect, nn::math::Vector3(1.0f, 1.0f, 1.0f));
		DrawPolygonMain(4, 124, true);
	}
	
}

