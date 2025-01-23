#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h> 
#include <GLFW\glfw3.h>

class GameCamera
{
public:
    GameCamera(const glm::vec3& cameraPos,
               const glm::vec3& cameraFront,
               const glm::vec3& cameraUp)
    {
         this->cameraPos = cameraPos;
         this->cameraFront = cameraFront;
         this->cameraUp = cameraUp;
    }

    glm::mat4 GetViewMatrix() const
    {
        //手动计算View
        /*glm::vec3 Look = -cameraFront;
        glm::vec3 Right = glm::cross(cameraUp, Look);
        glm::vec3 Up = glm::cross(Look, Right);

        float values[16] = {
            Right.x, Right.y, Right.z, 0.0f,
            Up.x, Up.y, Up.z, 0.0f,
            Look.x, Look.y, Look.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        glm::mat4 view1 = glm::make_mat4(values);

        float values2[16] = {
            1.0f, 0.0f, 0.0f, -cameraPos.x,
            0.0f, 1.0f, 0.0f, -cameraPos.y,
            0.0f, 0.0f, 1.0f, -cameraPos.z,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        glm::mat4 view2 = glm::make_mat4(values2);

        view1 = glm::transpose(view1);
        view2 = glm::transpose(view2);
        return view1 * view2;*/

        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }

    void KeyCallback(int key, float deltaTime)
    {
        float cameraSpeed = CameraMoveSpeed * deltaTime;
        if(key == GLFW_KEY_W)
        {
            cameraPos += cameraSpeed * cameraFront;
        }
        if(key == GLFW_KEY_S)
        {
            cameraPos -= cameraSpeed * cameraFront;
        }
        if(key == GLFW_KEY_A)
        {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if(key == GLFW_KEY_D)
        {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }

        //cameraPos.y = 0.0f;
    }

    void MouseCallback(float xoffset, float yoffset, float deltaTime)
    {
        float sensitivity = MouseSensitivity * deltaTime;
        yaw   += xoffset * sensitivity;
        pitch += yoffset * sensitivity;

        if(pitch > 89.0f) //pitch需要限制, 但是yaw不需要, 可以环顾四周
          pitch =  89.0f;
        if(pitch < -89.0f)
          pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        cameraFront = glm::normalize(front);
    }
    
    glm::vec3 CameraPos() const { return cameraPos; }
    glm::vec3 CameraFront() const { return cameraFront; }

private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    float yaw = -90.f;
    float pitch = 0.f;

    float CameraMoveSpeed = 2.5f;
    float MouseSensitivity = 2.5f;
};

