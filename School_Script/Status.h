#pragma once
// 3D�\���|���S����`
#ifndef ___H_STATUS
#define ___H_STATUS
#include <nn/os.h>

void InitStatus();
void UninitStatus();
// 3D��l���`��(����)
void DrawStatus();
// 3D�\���|���S���`��(�����)
void DrawStatusSub();
// 3D�\���|���S���J���[�ݒ�
void SetStatusColor(u8 colorR, u8 colorG, u8 colorB);
// 3D�\���|���S���X�V
//void UpdateStatus();

// �|���S���\���i�������A�t�F�[�h�Ŏg���Ă������̂Ȃ̂ō���͎g��Ȃ��j
void FillRectMainStatus(u8 colorR, u8 colorG, u8 colorB, u8 colorA);
void FillRectSubStatus(u8 colorR, u8 colorG, u8 colorB, u8 colorA);

nn::math::Vector3 GetPosStatus();           //�@�ʒu���
nn::math::Vector3 GetRotStatus();           //�@�ʒu���

#endif // ___H_Status
