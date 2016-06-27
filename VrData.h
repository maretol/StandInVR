#pragma once
#include <openvr.h>
#include "DxData.h"
#include <Windows.h>

class VrData {
public:
	vr::EVRInitError eError;
	DxData *dd;

	VrData();
	~VrData();
	void Init();
protected:
	bool DebugNoHMD = true;

private:
	vr::IVRSystem *m_HMD;

	void getHeadTracking();
	void getPositionTracking();
};