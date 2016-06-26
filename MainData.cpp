//---------------------------------------------------------------------------------
// Written by Motoharu Someya (@maretol)
// 2016-06-26
//---------------------------------------------------------------------------------

#include <DxLib.h>
#include <iostream>
#include "DxData.h"
#include "VrData.h"

//---------------------------------------------------------------------------------
// ��G�c�ȃt���[�`���[�g
// | start | -> | OpenVR init | -> | DxLib init | -> | DxLib�ɂ�郁�C�����[�v |
//		-> | DxLib shutdown | -> | OpenVR shutdown | -> | End |
//---------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hins, HINSTANCE hpreins, LPSTR lpcmdline, int nCmdShow) {
	VrData *vd = new VrData();
	vd->Init();
	return 0;
}