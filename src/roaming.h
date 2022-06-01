#pragma once

int cursorvisible = 0;
bool YES = false;
double timet = 0.0;
float OrbitRadius = 10.0f;
float OrbitX = 0, OrbitZ = OrbitRadius;

void TextureMapping::handleInput()
{
	bool firstMouse = true;
	const float angluarVelocity = 0.1f;
	const float angle = angluarVelocity * static_cast<float>(_deltaTime);
	const glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
	_sphere->rotation = glm::angleAxis(angle, axis) * _sphere->rotation;
	constexpr float cameraMoveSpeed = 0.05f;
	constexpr float cameraRotateSpeed = 0.02f;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	if (_keyboardInput.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE)
	{
		glfwSetWindowShouldClose(_window, true);
		return;
	}
	if (_keyboardInput.keyStates[GLFW_KEY_EQUAL] != GLFW_RELEASE)
	{
		_sphere->scale += glm::vec3(0.03f, 0.03f, 0.03f);
	}
	if (_keyboardInput.keyStates[GLFW_KEY_MINUS] != GLFW_RELEASE)
	{
		_sphere->scale -= glm::vec3(0.03f, 0.03f, 0.03f);
		if (_sphere->scale.x < 0.03 || _sphere->scale.y < 0.03 || _sphere->scale.z < 0.03)
			_sphere->scale = glm::vec3(0.03f, 0.03f, 0.03f);
	}
	if (_keyboardInput.keyStates[GLFW_KEY_R] != GLFW_RELEASE)
	{
		_sphere->position += glm::vec3(0.0f, 0.03f, 0.0f);
	}
	if (_keyboardInput.keyStates[GLFW_KEY_Y] != GLFW_RELEASE)
	{
		_sphere->position += glm::vec3(0.0f, -0.03f, 0.0f);
	}
	if (_keyboardInput.keyStates[GLFW_KEY_F] != GLFW_RELEASE)
	{
		_sphere->position += glm::vec3(-0.03f, 0.0f, 0.0f);
	}
	if (_keyboardInput.keyStates[GLFW_KEY_H] != GLFW_RELEASE)
	{
		_sphere->position += glm::vec3(0.03f, 0.0f, 0.0f);
	}
	if (_keyboardInput.keyStates[GLFW_KEY_T] != GLFW_RELEASE)
	{
		_sphere->position += glm::vec3(0.0f, 0.0f, -0.03f);
	}
	if (_keyboardInput.keyStates[GLFW_KEY_G] != GLFW_RELEASE)
	{
		_sphere->position += glm::vec3(0.0f, 0.0f, 0.03f);
	}
	if (_keyboardInput.keyStates[GLFW_KEY_SPACE] == GLFW_PRESS)
	{
		_camera.reset(new PerspectiveCamera(
			glm::radians(50.0f), 1.0f * _windowWidth / _windowHeight, 0.1f, 10000.0f));
		_camera->position.z = 10.0f;
		_camera->rotation = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	}
	if (_keyboardInput.keyStates[GLFW_KEY_B] == GLFW_PRESS)
	{
		_camera->fovy = 0.872664;
	}
	Camera* camera = _camera.get();
	if (_keyboardInput.keyStates[GLFW_KEY_O] != GLFW_RELEASE)
	{
		// cameraPos = cameraMoveSpeed * cameraFront;
		timet += 0.01;
		OrbitX = sin(timet) * OrbitRadius;
		OrbitZ = cos(timet) * OrbitRadius;
		// cameraPos = cameraMoveSpeed * _camera->getFront();
		//_camera->position += cameraPos;
		_camera->position = glm::vec3(OrbitX, _camera->position.y, OrbitZ);
	}
	if (_keyboardInput.keyStates[GLFW_KEY_W] != GLFW_RELEASE)
	{
		cameraPos = cameraMoveSpeed * _camera->getFront();
		_camera->position += cameraPos;
	}
	if (_keyboardInput.keyStates[GLFW_KEY_D] != GLFW_RELEASE)
	{
		cameraPos = _camera->getRight() * cameraMoveSpeed;
		_camera->position += cameraPos;
	}
	if (_keyboardInput.keyStates[GLFW_KEY_S] != GLFW_RELEASE)
	{
		cameraPos = cameraMoveSpeed * _camera->getFront();
		_camera->position -= cameraPos;
	}
	if (_keyboardInput.keyStates[GLFW_KEY_A] != GLFW_RELEASE)
	{
		cameraPos = _camera->getRight() * cameraMoveSpeed;
		_camera->position -= cameraPos;
	}
	if (_keyboardInput.keyStates[GLFW_KEY_E] != GLFW_RELEASE)
	{
		cameraPos = cameraMoveSpeed * cameraUp;
		_camera->position -= cameraPos;
	}
	if (_keyboardInput.keyStates[GLFW_KEY_Q] != GLFW_RELEASE)
	{
		cameraPos = cameraMoveSpeed * cameraUp;
		_camera->position += cameraPos;
	}
	if (_keyboardInput.keyStates[GLFW_KEY_ENTER] != GLFW_RELEASE)
	{
		YES = true;
	}
	if (YES == true && _keyboardInput.keyStates[GLFW_KEY_ENTER] == GLFW_RELEASE)
	{
		if (cursorvisible % 2 == 0)
		{
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			_mouseInput.move.xOld = _mouseInput.move.xCurrent = 0.5 * _windowWidth;
			_mouseInput.move.yOld = _mouseInput.move.yCurrent = 0.5 * _windowHeight;
			glfwSetCursorPos(_window, _mouseInput.move.xCurrent, _mouseInput.move.yCurrent);
			cursorvisible++;
		}
		else
		{
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			_mouseInput.move.xOld = _mouseInput.move.xCurrent = 0.5 * _windowWidth;
			_mouseInput.move.yOld = _mouseInput.move.yCurrent = 0.5 * _windowHeight;
			glfwSetCursorPos(_window, _mouseInput.move.xCurrent, _mouseInput.move.yCurrent);
			cursorvisible++;
		}
		YES = false;
	}
	if (cursorvisible % 2 == 0)
	{
		if (_mouseInput.move.xCurrent != _mouseInput.move.xOld)
		{
			// if (firstMouse)
			//{
			//	_mouseInput.move.xOld = _mouseInput.move.xCurrent;
			//	_mouseInput.move.yOld = _mouseInput.move.yCurrent;
			//	firstMouse = false;
			// }
			double mouse_movement_in_x_direction = -(_mouseInput.move.xCurrent - _mouseInput.move.xOld);
			glm::vec3 right = glm::vec3(0.0f, 1.0f, 0.0f);
			double thetax = 0.003 * mouse_movement_in_x_direction;
			camera->rotation = glm::quat{ (float)cos(thetax / 2), (float)sin(thetax / 2) * right } *camera->rotation;
			_mouseInput.move.xOld = _mouseInput.move.xCurrent;
		}
		if (_mouseInput.move.yCurrent != _mouseInput.move.yOld)
		{
			// if (firstMouse)
			//{
			//	_mouseInput.move.xOld = _mouseInput.move.xCurrent;
			//	_mouseInput.move.yOld = _mouseInput.move.yCurrent;
			//	firstMouse = false;
			// }
			double mouse_movement_in_y_direction = -(_mouseInput.move.yCurrent - _mouseInput.move.yOld);
			glm::vec3 up = camera->getRight();
			double thetay = 0.003 * mouse_movement_in_y_direction;
			camera->rotation = glm::quat{ (float)cos(thetay / 2), (float)sin(thetay / 2) * up } *camera->rotation;
			_mouseInput.move.yOld = _mouseInput.move.yCurrent;
		}
	}
	if (_mouseInput.scroll.y != 0)
	{
		printf("%f\n", _camera->fovy);
		if (_camera->fovy >= 0.05f && _camera->fovy <= 2.8f)
			_camera->fovy -= 0.02 * _mouseInput.scroll.y;
		if (_camera->fovy <= 0.05f)
			_camera->fovy = 0.05f;
		if (_camera->fovy >= 2.8f)
			_camera->fovy = 2.8f;
		_mouseInput.scroll.y = 0;
	}
}