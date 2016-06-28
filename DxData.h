#pragma once
#include <DxLib.h>


class DxData {
public:
	enum OUTPUTDEVICE {
		HMD,
		MONITOR
	};
	DxData();
	~DxData();
	void Init();
	void setOutputDevice(OUTPUTDEVICE output);
	void DxMain();
};

