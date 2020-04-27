#pragma once
// 3D表示ポリゴン定義
#ifndef ___H_STATUS
#define ___H_STATUS
#include <nn/os.h>

void InitStatus();
void UninitStatus();
// 3D主人公描画(上画面)
void DrawStatus();
// 3D表示ポリゴン描画(下画面)
void DrawStatusSub();
// 3D表示ポリゴンカラー設定
void SetStatusColor(u8 colorR, u8 colorG, u8 colorB);
// 3D表示ポリゴン更新
//void UpdateStatus();

// ポリゴン表示（ただし、フェードで使われていたものなので今回は使わない）
void FillRectMainStatus(u8 colorR, u8 colorG, u8 colorB, u8 colorA);
void FillRectSubStatus(u8 colorR, u8 colorG, u8 colorB, u8 colorA);

nn::math::Vector3 GetPosStatus();           //　位置情報
nn::math::Vector3 GetRotStatus();           //　位置情報

#endif // ___H_Status
