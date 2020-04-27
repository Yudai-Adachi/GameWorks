#include <nn/gx.h>
#include <nn/applet.h>
#include "SimplePlayer.h"

// extern??
extern nn::hid::PadStatus padStatus;
extern float player_x;
extern float player_y;
extern int dir;
extern s32 player_stat;
extern s32 g_score;
extern SimplePlayer app;

// ????
void CreateMatrix(f32 x, f32 y, f32 z, f32 angle = 0.0f, f32 sizeX = 1.0f, f32 sizeY = 1.0f, f32 sizeZ = 1.0f);
nn::math::Matrix34 CreateMatrix3D(const nn::math::Vector3 pos, const nn::math::Vector3 rot, const nn::math::Vector3 scale, bool billboard = false);
nn::math::Matrix34 CreateMatrix3DHierarchy(nn::math::Matrix34 mtx,const nn::math::Vector3 pos,const nn::math::Vector3 rot,const nn::math::Vector3 scale );
void DrawPolygonMain(u32, u32, bool b3D = false);
void DrawPolygonSub(u32, u32);
void UpdateCamera();

void SetFrame(int frame = -1);

bool CheckCollision3D( nn::math::Vector3* pos1, f32 size1, nn::math::Vector3* pos2, f32 size2 );
bool Boss_CheckCollision3D(nn::math::Vector3 pos1, f32 size1);

void Change_2D();
void Change_3D();

void Fade_True_Slime();
