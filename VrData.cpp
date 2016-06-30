#include "VrData.h"
#include "DxLib.h"


// プログラムは WinMain から始まります

VrData::VrData() {
	dd = new DxData();
}

VrData::~VrData() {
	delete dd;
}

void VrData::Init() {
	// VR初期化
//	eError = vr::VRInitError_None;
//	m_HMD = vr::VR_Init(&eError, vr::VRApplication_Scene); // ここにビルドエラー LNK2019 発生
	// とりあえず現状
	eError = vr::VRInitError_Unknown;

	if (eError = vr::VRInitError_Unknown) {
		dd->setOutputDevice(DxData::MONITOR);
		dd->Init();

		dd->DxMain();
	}
	if (eError = vr::VRInitError_Init_HmdNotFound) {
		dd->setOutputDevice(DxData::MONITOR);
		dd->Init();
	} else if(eError = vr::VRInitError_None) {
		dd->setOutputDevice(DxData::HMD);
		dd->Init();
	} else {
		MessageBox(NULL, "ERROR ON INIT", "ERROR : " + eError, MB_OK);
		m_HMD = NULL;
//		vr::VR_Shutdown();
		return;
	}

}

void VrData::getHeadTracking() {
	// ヘッドトラッキング処理
}

void VrData::getPositionTracking() {
	// ポジショントラッキング処理
}
