#include "CameraFactory.h"
#include "Camera.h"
#include "ArcballCamera.h" 
#include <assert.h>

using std::string;

Camera* CameraFactory::makeNewCam(string _type)
{
	printf("CAM TYPE: %s \n", _type.c_str());
	if (_type == "CAMERA")
	{
		return new Camera();
		cout << "cam factory normal cam test" << "\n";
	}
	else if (_type == "ARCBALLCAMERA")
	{
		return new ArcballCamera(); 
		cout << "cam factory arcball test" << "\n";
	}
	else
	{
		printf("UNKNOWN CAMERA TYPE!");
		assert(0);
		return nullptr;
	}
}
