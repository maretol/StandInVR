#include "VrData.h"
#include "DxLib.h"


// �v���O������ WinMain ����n�܂�܂�

VrData::VrData() {
	dd = new DxData();
}

VrData::~VrData() {
	delete dd;
}

void VrData::Init() {
	// VR������
//	eError = vr::VRInitError_None;
//	m_HMD = vr::VR_Init(&eError, vr::VRApplication_Scene); // �����Ƀr���h�G���[ LNK2019 ����
	// �Ƃ肠��������
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
	// �w�b�h�g���b�L���O����
}

void VrData::getPositionTracking() {
	// �|�W�V�����g���b�L���O����
}
