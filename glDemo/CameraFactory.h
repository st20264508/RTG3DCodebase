#pragma once
#include <string>
class Camera;
class ArcballCamera; 
//A rather simple Factory using the base class Camera
//generates a Camera based on its type
class CameraFactory
{
public:

	static Camera* makeNewCam(std::string type);
};