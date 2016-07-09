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

	int ModelHandle;

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
	{
		// エラーが発生したら直ちに終了
		return;
	}

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// ３Ｄ空間上に円錐を描画する
	DrawCone3D(VGet(320.0f, 400.0f, 0.0f), VGet(320.0f, 100.0f, 0.0f), 80.0f, 16, GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);




	// モデルの読み込み
	ModelHandle = MV1LoadModel("DxChara.x");

	// ライティングの計算をしないように設定を変更
	SetUseLighting(FALSE);

	// モデルをカメラの映る位置に移動
	MV1SetPosition(ModelHandle, VGet(320.0f, -300.0f, 600.0f));

	// モデルを描画
	MV1DrawModel(ModelHandle);

	// キーの入力待ち
	WaitKey();
	
	// ＤＸライブラリの後始末
	DxLib_End();
}