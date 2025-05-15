
#include "ArcballCamera.h"
#include <stringHelp.h>
#include "helper.h"

using namespace std;
using namespace glm;

//
// Private API
//

// update position, orientation and view matrices when camera rotation and radius is modified
void ArcballCamera::calculateDerivedValues() {

	const float theta_ = glm::radians<float>(m_theta);
	const float phi_ = glm::radians<float>(m_phi);

	// calculate position vector
	//cameraPos = glm::vec4(sinf(phi_) * cosf(-theta_) * radius, sinf(-theta_) * radius, cosf(phi_) * cosf(-theta_) * radius, 1.0f);
	m_pos = glm::vec4(sinf(phi_) * cosf(-theta_) * m_radius, sinf(-theta_) * m_radius, cosf(phi_) * cosf(-theta_) * m_radius, 1.0f); 

	// calculate orientation basis R
	//R = glm::eulerAngleY(phi_) * glm::eulerAngleX(theta_);
		
	// calculate view and projection transform matrices
	m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -m_radius)) * glm::eulerAngleX(-theta_) * glm::eulerAngleY(-phi_);
	m_projectionMatrix = glm::perspective(glm::radians<float>(m_fovY), m_aspect, m_nearPlane, m_farPlane);

	mat4 cameraTransform = projectionTransform() * viewTransform();

	mat4 cameraProjection = projectionTransform();
	mat4 cameraView = viewTransform() * translate(identity<mat4>(), glm::vec3(0, 0, 0));  
}


//
// Public method implementation
//

// ArcballCamera constructors

// initialise camera parameters so it is placed at the origin looking down the -z axis (for a right-handed camera) or +z axis (for a left-handed camera)
ArcballCamera::ArcballCamera() {

	m_type = "ARCBALLCAMERA";
	/*m_theta = 0.0f;
	m_phi = 0.0f;
	m_radius = 15.0f;

	m_fovY = 55.0f;
	m_aspect = 1.0f;
	m_nearPlane = 0.1f;
	m_farPlane = 500.0f;*/

	//F = ViewFrustum(55.0f, 1.0f, 0.1f, 500.0f);
	
	// calculate derived values
	//calculateDerivedValues();
	//F.calculateWorldCoordPlanes(C, R);
}




// create a camera with orientation <theta, phi> representing Euler angles specified in degrees and Euclidean distance 'init_radius' from the origin.  The frustum / viewplane projection coefficients are defined in init_fovy, specified in degrees spanning the entire vertical field of view angle, init_aspect (w/h ratio), init_nearPlane and init_farPlane.  If init_farPlane = 0.0 (as determined by equalf) then the resulting frustum represents an infinite perspective projection.  This is the default
ArcballCamera::ArcballCamera(float _theta, float _phi, float _radius, float _fovY, float _aspect, float _nearPlane, float _farPlane) {

	this->m_theta = _theta;
	this->m_phi = _phi;
	this->m_radius = std::max<float>(0.0f, _radius);

	this->m_fovY = _fovY;
	this->m_aspect = _aspect;
	this->m_nearPlane = _nearPlane;
	this->m_farPlane = _farPlane;

	//F = ViewFrustum(init_fovy, init_aspect, init_nearPlane, init_farPlane);

	// calculate derived values
	calculateDerivedValues();
	//F.calculateWorldCoordPlanes(C, R);
}

void ArcballCamera::Init()
{
	calculateDerivedValues(); 
}

void ArcballCamera::Tick(float _dt)
{
	calculateDerivedValues();
}

void ArcballCamera::Load(ifstream& _file)
{
	//StringHelp::String(_file, "TYPE", m_type);
	StringHelp::String(_file, "NAME", m_name);
	StringHelp::Float3(_file, "POS", m_pos.x, m_pos.y, m_pos.z); 
	StringHelp::Float3(_file, "LOOKAT", m_lookAt.x, m_lookAt.y, m_lookAt.z); 
	StringHelp::Float(_file, "THETA", m_theta);
	StringHelp::Float(_file, "PHI", m_phi);
	StringHelp::Float(_file, "RADIUS", m_radius);
	StringHelp::Float(_file, "FOVY", m_fovY);
	StringHelp::Float(_file, "FOV", m_fov); 
	StringHelp::Float(_file, "ASPECT", m_aspect);
	StringHelp::Float(_file, "NEAR", m_nearPlane); 
	StringHelp::Float(_file, "FAR", m_farPlane); 

	//m_pos.x = -5.0f; m_pos.y = 5.0f; m_pos.z = 0.0f; //might not need, fixed loading errors

	calculateDerivedValues();
	/*
	TYPE: ARCBALLCAMERA
NAME: CAM5ARC
THETA: 0.0 
PHI: 0.0
RADIUS: 1.98595
FOVY: 55.0
ASPECT: 1.0
NEAR: 0.1
FAR: 500.0*/
}

#pragma region Accessor methods for stored values

// return the pivot rotation around the x axis (theta) in degrees
float ArcballCamera::getTheta() {

	return m_theta;
}

// return the pivot rotation around the y axis (phi) in degrees
float ArcballCamera::getPhi() {

	return m_phi;
}

void ArcballCamera::rotateCamera(float _dTheta, float _dPhi) {

	m_theta += _dTheta;
	m_phi += _dPhi;

	calculateDerivedValues();
}

float ArcballCamera::getRadius() {

	return m_radius;
}

void ArcballCamera::scaleRadius(float _s) {

	m_radius *= _s;
	calculateDerivedValues();
}

void ArcballCamera::incrementRadius(float _i) {

	m_radius = std::max<float>(m_radius + _i, 0.0f);
	calculateDerivedValues();
}

float ArcballCamera::getFovY() {

	return m_fovY;
}

void ArcballCamera::setFovY(float _fovY) {

	this->m_fovY = _fovY;
	calculateDerivedValues();
}

float ArcballCamera::getAspect() {

	return m_aspect;
}

void ArcballCamera::setAspect(float _aspect) {

	this->m_aspect = _aspect;
	calculateDerivedValues();
}

float ArcballCamera::getNearPlaneDistance() {

	return m_nearPlane;
}

void ArcballCamera::setNearPlaneDistance(float _nearPlaneDistance) {

	this->m_nearPlane = _nearPlaneDistance;
	calculateDerivedValues();
}

float ArcballCamera::getFarPlaneDistance() {

	return m_farPlane;
}

void ArcballCamera::setFarPlaneDistance(float _farPlaneDistance) {

	this->m_farPlane = _farPlaneDistance;
	calculateDerivedValues();
}

#pragma endregion


#pragma region Accessor methods for derived values

// return the camera location in world coordinate space
//glm::vec4 ArcballCamera::getPosition() {
//
//	return cameraPos;
//}

// return a const reference to the camera's orientation matrix in world coordinate space
//glm::mat4 ArcballCamera::getOrientationBasis() {
//
//	return R;
//}

// return a const reference to the view transform matrix for the camera
glm::mat4 ArcballCamera::viewTransform() {

	return m_viewMatrix;
}

// return a const reference the projection transform for the camera
glm::mat4 ArcballCamera::projectionTransform() {

	return m_projectionMatrix;
}

void ArcballCamera::SetRenderValues(unsigned int _prog)
{
	GLint loc;

	calculateDerivedValues();

	//matrix for the view transform
	if (Helper::SetUniformLocation(_prog, "viewMatrix", &loc))
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(GetView()));

	//matrix for the projection transform
	if (Helper::SetUniformLocation(_prog, "projMatrix", &loc))
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(GetProj()));

	//the current camera is at this position
	if (Helper::SetUniformLocation(_prog, "camPos", &loc))
		glUniform3fv(loc, 1, glm::value_ptr(GetPos())); 
}

#pragma endregion