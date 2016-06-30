//written by Yusei
#include "DxData.h"
#include "DxLib.h"

// プログラムは WinMain から始まります

DxData::DxData() {
	// コンストラクタ。クラス変数などを定義したい場合ここを使う
	// 詳しくは調べる
}

DxData::~DxData() {
	// デストラクタ。今は考えなくてよい
}

void DxData::setOutputDevice(OUTPUTDEVICE output) {
	// VRデバイスがあると output = OUTPUTDEVICE.HMD が来る
	// なかったら output = OUTPUTDEVICE.MONITOR が来る。
	// 現在は考慮せずともよし

}

void DxData::Init() {
	// まず呼び出される初期化処理
	// ここで初期化する

	ChangeWindowMode(true); // ウィンドウで表示。falseで全画面モード（わかりにくければfalseにしてみるとよい）
	if (DxLib_Init() == -1) {
		return;
	}

}

void DxData::DxMain() {
	// ここにグラフィック処理を記入

	DrawPixel(320, 240, GetColor(255, 255, 255));
	DrawPixel(320, 230, GetColor(255, 200, 0));
	DrawBox(32, 42, 36, 65, GetColor(43, 43, 255), true);
	WaitKey();
	DxLib_End();
}