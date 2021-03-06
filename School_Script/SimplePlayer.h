﻿/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     SimplePlayer.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50863 $
 *---------------------------------------------------------------------------*/

 //------------------------先生のコード-------------------------------------------------------------------------

 //-----------------------------------------------------------------------------------------------------------

#ifndef NN_SAMPLE_DEMOS_SND_SIMPLE_PLAYER_H_
#define NN_SAMPLE_DEMOS_SND_SIMPLE_PLAYER_H_
#define SOUND_NUM 10
#include "SndDemoBase.h"

struct v_parameter{
	int stat;			//このvoiceが再生中／停止／ポーズ中／未使用　0/1/2/99
	int sound_no;		//再生しているときの音楽No.
	int loop_flg;		//再生している音がループするかどうか？　0:ループなし　1:ループあり
};

class SimplePlayer : public SndDemoBase
{
protected:
    virtual void OnInitialize();
    virtual void OnFinalize();
    virtual void OnUpdate();
    virtual void SoundThreadFuncImpl();


	//再生用トラック情報　同時に８音まで再生
	struct v_parameter v_param[8];

	//メモリ上に記憶する音楽データ　今回は４つの音楽
    int dataSize[SOUND_NUM];// = reader.GetDataSize();
    int channelCount[SOUND_NUM];// = reader.GetChannelCount();
    int sampleRate[SOUND_NUM];// = reader.GetSampleRate();
    int quantumBits[SOUND_NUM];// = reader.GetQuantumBits();
private:
    static const int SOUND_THREAD_PRIORITY = 2;
    static const size_t SOUND_THREAD_STACK_SIZE = 4096;
    nn::os::Thread m_SoundThread;
    bool m_SoundThreadFlag;
    NN_PADDING3;
    nn::os::CriticalSection m_CriticalSection;

public:
	void SetSoundState(int ,int, int, int );
};

#endif  // NN_SAMPLE_DEMOS_SND_SIMPLE_PLAYER_H_
