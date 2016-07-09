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

	VERTEX3DSHADER Vertex[4];
	unsigned short Index[6];
	int vshandle;
	int pshandle;
	int texhandle;
	int x;
	int xadd;
	float color;
	float coloradd;
	int ModelHandle;
	FLOAT4 f4;

	// 2D

	DrawBox(0, 0, 640, 480, GetColor(200, 200, 200), TRUE);	// 画面全体を希望の色で塗りつぶす


	//3D

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// ３Ｄ空間上にカプセルを描画する
	DrawCapsule3D(VGet(320.0f, 100.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(255, 0, 255), GetColor(255, 255, 255), TRUE);

	// カメラ

	// モデルの読み込み
	ModelHandle = MV1LoadModel("DxChara.x");

	// ライティングの計算をしないように設定を変更
	SetUseLighting(FALSE);

	// モデルをカメラの映る位置に移動
	MV1SetPosition(ModelHandle, VGet(320.0f, -300.0f, 600.0f));

	// モデルを描画
	MV1DrawModel(ModelHandle);

	//  シェーダーを使って２Ｄポリゴンを描画

	// ２ポリゴン分の頂点のデータをセットアップ
	Vertex[0].pos = VGet(2.0f, 540.0f,0.0f);
	Vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[0].dif = GetColorU8(255, 0, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].pos = VGet(420.0f, 340.0f, 0.0f);
	Vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[1].dif = GetColorU8(0, 0, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].pos = VGet(220.0f, 140.0f, 0.0f);
	Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[2].dif = GetColorU8(255, 255, 0, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].pos = VGet(420.0f, 140.0f, 0.0f);
	Vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[3].dif = GetColorU8(255, 255, 0, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	// ２ポリゴン分の頂点番号配列をセットアップ
	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 2;
	Index[3] = 2;
	Index[4] = 1;
	Index[5] = 3;

	// 頂点シェーダーを読み込む
	vshandle = LoadVertexShader("VertexShaderTestVS.vso");

	// ピクセルシェーダーを読み込む
	pshandle = LoadPixelShader("VertexShaderTestPS.pso");

	// 描画に使用する画像の読み込み
	texhandle = LoadGraph("Tex1.bmp");

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// 表示座標を移動する処理の初期化
	x = 0;
	xadd = 8;

	// 色を変化させる処理の初期化
	color = 0.0f;
	coloradd = 1.0f / 60.0f;

	// ESCキーが押されるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面を初期化
		ClearDrawScreen();

		// 座標を移動させる
		x += xadd;
		if (x > 200 || x < -200)
		{
			xadd = -xadd;
		}

		// 色の値を変化させる
		color += coloradd;
		if (color <= 0.0f || color >= 1.0f)
		{
			coloradd = -coloradd;
		}

		// 座標値を頂点シェーダー float4型定数０番にセット
		f4.x = (float)x;
		f4.y = 0.0f;
		f4.z = 0.0f;
		f4.w = 0.0f;
		SetVSConstF(0, f4);

		// 色の値をピクセルシェーダー float4型定数０番にセット
		f4.x = color;
		f4.y = color;
		f4.z = color;
		f4.w = 1.0f;
		SetPSConstF(0, f4);

		// 使用する頂点シェーダーのセット
		SetUseVertexShader(vshandle);

		// 使用するピクセルシェーダーをセット
		SetUsePixelShader(pshandle);

		// 使用するテクスチャを０番にセット
		SetUseTextureToShader(0, texhandle);

		// シェーダーを使用した２ポリゴンの描画
		DrawPolygonIndexed3DToShader(Vertex, 4, Index, 2);

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	// 使用した頂点シェーダーの float4型定数の設定を無効化する
	ResetVSConstF(0, 2);

	// 使用したピクセルシェーダーの float4型定数の設定を無効化する
	ResetPSConstF(0, 1);

	// 読み込んだ頂点シェーダーの削除
	DeleteShader(vshandle);

	// 読み込んだピクセルシェーダーの削除
	DeleteShader(pshandle);

	// キー入力待ちをする
	WaitKey();

	DxLib_End();
}