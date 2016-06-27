#pragma once
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
};

