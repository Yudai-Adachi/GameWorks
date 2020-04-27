#pragma once
class CBattle
{
public:

	void DrawCommand();                //戦闘中のコマンド描画
	void DrawCursor(int number);       //戦闘中のカーソル描画

	CBattle();　                       //コンストラクタ
	~CBattle();                        //デストラクタ
};

