#pragma once
#include <openvr.h>

class VrData {
public:
	VrData();
	~VrData();
	void Init();
protected:

private:
	void getHeadTracking();
	void getPositionTracking();
};