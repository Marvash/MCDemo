#include "CameraSystem.h"

CameraSystem::CameraSystem(CoreEventDispatcher* coreEventDispatcher) :
    CoreService(coreEventDispatcher),
    m_cameraOffset(glm::vec3(0.0f, 0.8f, 0.0f)),
    m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_worldUp(m_up),
    m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_mouseSensitivity(SENSITIVITY),
    m_zoom(ZOOM),
    m_yaw(YAW),
    m_pitch(PITCH),
    m_cameraPosition(m_cameraOffset) {
    updateRenderingData();
}

void CameraSystem::onNotify(Event& newEvent) {

}

void CameraSystem::updateRenderingData() {
    m_cameraRenderingData.zoom = m_zoom;
    updateViewMatrix();
    m_cameraRenderingData.viewMatrix = &m_viewMatrix;
}

void CameraSystem::setPlayerPosition(glm::vec3& position) {
	m_cameraPosition = position + m_cameraOffset;
}

void CameraSystem::setCameraOffset(glm::vec3& offset) {
	m_cameraOffset = offset;
}

CameraRenderingData* CameraSystem::getCameraRenderingData() {
	return &m_cameraRenderingData;
}

glm::vec3 CameraSystem::getCameraPosition() {
    return m_cameraPosition;
}

void CameraSystem::updateViewMatrix() {
    m_viewMatrix = glm::lookAt(m_cameraPosition, m_cameraPosition + m_front, m_up);
}

void CameraSystem::processMouseMovement(float xoffset, float yoffset, bool constrainpitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainpitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    updateCameraVectors();
    updateRenderingData();
}

void CameraSystem::processMouseScroll(float yoffset)
{
    m_zoom -= (float)yoffset;
    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    if (m_zoom > 60.0f)
        m_zoom = 60.0f;
    updateRenderingData();
}

void CameraSystem::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}