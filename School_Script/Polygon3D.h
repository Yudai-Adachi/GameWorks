// 3D�\���|���S����`
#ifndef ___H_POLYGON3D
#define ___H_POLYGON3D
#include <nn/os.h>

extern nn::math::MersenneTwister g_Mer;

void InitPolygon3D();                                                               //�@�ϐ��̏�����
void UninitPolygon3D();                                                             // 3D�\���|���S���`��(����)
void DrawPolygon3D();                                                               // 3D�\���|���S���`��(�����)
void DrawPolygon3DSub();                                                            // 3D�\���|���S���J���[�ݒ�
void SetPolygon3DColor(u8 colorR, u8 colorG, u8 colorB);                            // 3D�\���|���S���X�V
void UpdatePolygon3D();                                                             //�@�|���S���X�V�p

// �|���S���\���i�������A�t�F�[�h�Ŏg���Ă������̂Ȃ̂ō���͎g��Ȃ��j
void FillRectMainPolygon3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA);
void FillRectSubPolygon3D(u8 colorR, u8 colorG, u8 colorB, u8 colorA);

void Encounter();                                                                   //�@����������������
void Fade_True_Boss();                                                              //�@�t�F�[�h�p�ϐ���true�ɕϊ�

nn::math::Vector3 GetPosPolygon3D();                                                // �ʒu�擾
nn::math::Vector3 GetRotPolygon3D();                                                // �ʒu�擾

#endif // ___H_POLYGON3D
