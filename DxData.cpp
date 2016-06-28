//written by Yusei
#include "DxData.h"

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

	WaitKey();
	DxLib_End();
}