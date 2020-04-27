// 3D表示ポリゴン定義
#ifndef ___H_POLYGON3D
#define ___H_POLYGON3D
#include <nn/os.h>

extern nn::math::MersenneTwister g_Mer;

void InitPolygon3D();                                                               //　変数の初期化
void UninitPolygon3D();                                                             // 3D表示ポリゴン描画(上画面)
void DrawPolygon3D();                                                               // 3D表示ポリゴン描画(下画面)
void DrawPolygon3DSub();                                                            // 3D表示ポリゴンカラー設定
void SetPolygon3DColor(u8 colorR, u8 colorG, u8 colorB);                            // 3D表示ポリゴン更新
void UpdatePolygon3D();                                                             //　ポリゴン更新用

// ポリゴン表示（ただし、フェードで使われていたものなので今回は使わない）
void FillRectMainPolygon3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA);
void FillRectSubPolygon3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA);

void Encounter();                                                                   //　乱数が当たったら
void Fade_True_Boss();                                                              //　フェード用変数をtrueに変換

nn::math::Vector3 GetPosPolygon3D();                                                // 位置取得
nn::math::Vector3 GetRotPolygon3D();                                                // 位置取得

#endif // ___H_POLYGON3D
