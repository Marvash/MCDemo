#pragma once
#include "Core/CoreEventDispatcher.h"
#include "Core/Services/CoreService.h"
#include "CameraRenderingData.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraSystem : public CoreService {
public:

	CameraSystem(CoreEventDispatcher* coreEventDispatcher);
	void onNotify(Event& newEvent) override;
	void setPlayerPosition(glm::vec3& position);
	void setCameraOffset(glm::vec3& offset);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);
	
	CameraRenderingData* getCameraRenderingData();
    glm::vec3 getCameraPosition();

    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

private:
    void updateViewMatrix();
    void updateCameraVectors();
    void updateRenderingData();

	CameraRenderingData m_cameraRenderingData;
    glm::vec3 m_cameraOffset;
	glm::vec3 m_cameraPosition;

    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 60.0f;

    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;

    float m_mouseSensitivity;
    float m_zoom;
    glm::mat4 m_viewMatrix;
};