#pragma once


class Camera
{
public:
	Camera(float startAngle, float startRadius, float yPos)
		: angle(startAngle), radius(startRadius), yPos(yPos),
		angularVelocity(0.0f), targetAngularVelocity(0.0f)
	{
	}

	glm::mat4 GetViewMatrix() {
		glm::vec3 pos = glm::vec3(sin(angle) * radius, yPos, cos(angle) * radius);
		return glm::lookAt(pos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	}

	void Update(float deltaTime)
	{
		float inertiaFactor = 0.1f;
		angularVelocity += (targetAngularVelocity - angularVelocity) * inertiaFactor;
		angle += angularVelocity * deltaTime;
	}

	void SetRotationVelocity(float target) {
		targetAngularVelocity = target;
	}

	glm::vec3 GetPosition() {
		return glm::vec3(sin(angle) * radius, yPos, cos(angle) * radius);
	}

private:
	float angle, radius, yPos;

	float angularVelocity;
	float targetAngularVelocity;
};