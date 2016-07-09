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

	DrawPixel(170, 56, GetColor(34, 200, 240));
	DrawPixel(320, 230, GetColor(255, 24, 0));
	DrawOval(200, 45, 350, 240, GetColor(43, 43, 212), true);

	//キー取得用配列
	char key[256];

	//x座標
	int x = 300, y = 240;

	//グラフィックハンドル格納用配列
	int gh[12];

	//画像読み込み
	if (LoadDivGraph("charall.png", 12, 3, 4, 49, 66, gh) == -1) {
		WaitKey();
		return;
	}

	//移動係数
	float move = 1.0f;

	//横方向と縦方向のカウント数。
	int xcount = 0, ycount = 0;

	//添字用変数
	int ix = 0, iy = 0, result = 0;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
		if (key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_RIGHT] == 1) {
			if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
				//移動係数を０．７１に設定
				move = 0.71f;
			} else {
				//斜めじゃなければ１．０に設定
				move = 1.0f;
			}
		} else if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
			move = 1.0f;
		}

		if (key[KEY_INPUT_LEFT] == 1) {
			x -= (int) 4 * move;
		}
		if (key[KEY_INPUT_RIGHT] == 1) {
			x += (int) 4 * move;
		}
		if (key[KEY_INPUT_UP] == 1) {
			y -= (int) 4 * move;
		}
		if (key[KEY_INPUT_DOWN] == 1) {
			y += (int) 4 * move;
		}

		//左キーが押されてて、かつxcountが０以上なら０にしてから１引く。
		//それ以外は１引く
		if (key[KEY_INPUT_LEFT] == 1) {
			if (xcount > 0) {
				xcount = 0;
			}
			--xcount;
		}

		//右キーが押されてて、かつxcountが０以下なら０にしてから１足す。
		//それ以外は１引く
		if (key[KEY_INPUT_RIGHT] == 1) {
			if (xcount < 0) {
				xcount = 0;
			}
			++xcount;
		}

		//上キーが押されてて、かつycountが０以上なら０にしてから１引く。
		//それ以外は１引く
		if (key[KEY_INPUT_UP] == 1) {
			if (ycount > 0) {
				ycount = 0;
			}
			--ycount;
		}

		//下キーが押されてて、かつycountが０以下なら０にしてから１足す。
		//それ以外は１足す
		if (key[KEY_INPUT_DOWN] == 1) {
			if (ycount < 0) {
				ycount = 0;
			}
			++ycount;
		}

		//カウント数から添字を求める。
		ix = abs(xcount) % 30 / 10;
		iy = abs(ycount) % 30 / 10;

		if (xcount > 0) {
			//xカウントがプラスなら右向きなので2行目の先頭添字番号を足す。
			ix += 3;
			result = ix;
		} else if (xcount < 0) {
			//マイナスなら左向きなので、4行目の先頭添字番号を足す。
			ix += 9;
			result = ix;
		}

		if (ycount > 0) {
			//yカウントがプラスなら下向きなので、3行目の先頭添字番号を足す。
			iy += 6;
			result = iy;
		} else if (ycount < 0) {
			//１行目の先頭添字番号は０なので何もする必要なし。(分かりやすくするために書いときました)
			iy += 0;
			result = iy;
		}

		//斜め移動の場合は横顔を優先
		if (move == 0.71f) {
			result = ix;
		}

		//描画
		DrawGraph(x, y, gh[result], TRUE);

		//押されてなければカウントをゼロにする。
		if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
			xcount = 0;
		}

		if (key[KEY_INPUT_UP] != 1 && key[KEY_INPUT_DOWN] != 1) {
			ycount = 0;
		}

		if (key[KEY_INPUT_ESCAPE] == 1) {
			break;
		}

	}

	DxLib_End();
}