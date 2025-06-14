#pragma once

#include "glew.h"


class Projection
{
public:
    virtual ~Projection() = default;

    virtual glm::mat4 GetMatrix() const = 0;
    virtual void Zoom(float amount) = 0;

protected:
    Projection(int width, int height)
        : width(width), height(height),
        nearPlane(0.1f), farPlane(100.0f)
    {
    }

    int width, height;
    float nearPlane, farPlane;
};


class PerspectiveProjection : public Projection
{
public:
    PerspectiveProjection(int width, int height)
        : Projection(width, height), fov(45.0f) {
    }

    glm::mat4 GetMatrix() const override
    {
        return glm::perspective(glm::radians(fov), (float)width / (float)height, nearPlane, farPlane);
    }

    void Zoom(float amount) override
    {
        fov -= amount;
        if (fov < 15.0f) fov = 15.0f;
        if (fov > 75.0f) fov = 75.0f;
    }

private:
    float fov;
};


class OrthographicProjection : public Projection
{
public:
    OrthographicProjection(int width, int height)
        : Projection(width, height), orthoSize(10.0f) {
    }

    glm::mat4 GetMatrix() const override
    {
        float aspectRatio = (float)width / (float)height;
        float orthoWidth = orthoSize * aspectRatio;
        float orthoHeight = orthoSize;
        return glm::ortho(-orthoWidth / 2.0f, orthoWidth / 2.0f, -orthoHeight / 2.0f, orthoHeight / 2.0f, nearPlane, farPlane);
    }

    void Zoom(float amount) override
    {
        orthoSize -= amount;
        if (orthoSize < 2.0f) orthoSize = 2.0f;
        if (orthoSize > 13.0f) orthoSize = 13.0f;
    }

private:
    float orthoSize;
};