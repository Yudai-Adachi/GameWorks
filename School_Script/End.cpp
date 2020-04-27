#include <nn/gd.h>
#include <nn/snd.h>
#include <math.h>
#include "Main.h"
#include "Texture.h"
#include "string.h"
#include "End.h"

extern nn::gd::CombinerState* s_texComState;
extern nn::gd::VertexBufferResource* bufferCoord;
extern nn::gd::VertexBufferResource* bufferTexCoord;

CEnd::CEnd()
{
}


CEnd::~CEnd()
{
}

//?????????
void CEnd::DrawEnd() {
	Change_2D();

	nn::gd::TextureStage::SetTexture(nn::gd::TextureStage::TEXTURE_UNIT_0, *s_texclear);
	nn::gd::TextureStage::SetSamplerState(nn::gd::TextureStage::TEXTURE_UNIT_0, s_samplerDefault);

	CreateMatrix(0.0f, 0.0f, 0.0f);
	DrawPolygonMain(4,136);
}
