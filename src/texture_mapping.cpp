#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

#include "media.h"
#include "shaders.h"
#include "texture_mapping.h"

std::vector<Vertex> cubeVertices;
std::vector<GLuint> cubeIndices;
std::vector<Vertex> coneVertices;
std::vector<GLuint> coneIndices;
std::vector<Vertex> cylinderVertices;
std::vector<GLuint> cylinderIndices;
std::vector<Vertex> roundtableVertices;
std::vector<GLuint> roundtableIndices;
std::vector<Vertex> newsphereVertices;
std::vector<GLuint> newsphereIndices;

bool gameOver = false;
bool importFlag = 0;
bool loseWindow = false;
bool winWindow = false;
Model *inputModel;
int _amount = 0;
float xd = -1.0, yd = 1.0;
bool knock = true;
bool knocky = false;
glm::mat4 view1;
int player = 0;
int hint = 1;
glm::vec3 camtemp;
double neng = 0.0;

TextureMapping::TextureMapping(const Options &options) : Application(options)
{
  genCube(cubeVertices, cubeIndices);
  genCone(coneVertices, coneIndices);
  genCylinder(cylinderVertices, cylinderIndices);
  genRoundTable(roundtableVertices, roundtableIndices);
  genShpere(newsphereVertices, newsphereIndices);
  // init model

  _sphere.reset(new Model(modelPath));
  _sphere->scale = glm::vec3(3.0f, 3.0f, 3.0f);
  _sphere->position = glm::vec3(-10.0f, 5.0f, 0.0f);
  _sphere->computeBoundingBox();

  _maze.reset(new Model(modelPath2));
  _maze->scale = glm::vec3(5.0f, 5.0f, 5.0f);
  _maze->position = glm::vec3(-10.0f, -15.0f, 0.0f);
  _maze->computeBoundingBox();
  _maze->changeBoundingBoxY(30); // to change the y bounding box for compute
  _maze->computeInBoundingBox(); // add this funtcion if you want to use octree

  _bear0.reset(new Model(modelPath8));
  _bear0->scale = glm::vec3(0.1f, 0.1f, 0.1f);
  _bear0->position = glm::vec3(-4.0f, -14.1f, 11.0f);
  _bear0->computeBoundingBox();

  _bear1.reset(new Model(modelPath8));
  _bear1->scale = glm::vec3(0.1f, 0.1f, 0.1f);
  _bear1->position = glm::vec3(-4.0f, -14.1f, 11.0f);
  _bear1->computeBoundingBox();

  _door.reset(new Model(modelPath4));
  _door->scale = glm::vec3(0.14f, 0.08f, 0.10f);
  //_door->computeBoundingBox();

  _arml.reset(new Model(modelPath6));
  _arml->scale = glm::vec3(3.0f, 3.0f, 3.0f);
  _arml->computeBoundingBox();

  _armr.reset(new Model(modelPath7));
  _armr->scale = glm::vec3(3.0f, 3.0f, 3.0f);
  _armr->computeBoundingBox();

  _cube.reset(new Model(cubeVertices, cubeIndices));
  _cube->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  _cube->position = glm::vec3(10.0f, -5.0f, 0.0f);
  _cube->computeBoundingBox();

  _cone.reset(new Model(coneVertices, coneIndices));
  _cone->scale = glm::vec3(2.0f, 2.0f, 2.0f);
  _cone->position = glm::vec3(-10.0f, -15.0f, 0.0f);
  _cone->computeBoundingBox();

  _cylinder.reset(new Model(cylinderVertices, cylinderIndices));
  _cylinder->scale = glm::vec3(2.0f, 2.0f, 2.0f);
  _cylinder->position = glm::vec3(-10.0f, -5.0f, 0.0f);
  _cylinder->computeBoundingBox();

  _roundtable.reset(new Model(roundtableVertices, roundtableIndices));
  _roundtable->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  _roundtable->position = glm::vec3(-10.0f, 18.5f, 0.0f);
  _roundtable->computeBoundingBox();

  _newsphere.reset(new Model(newsphereVertices, newsphereIndices));
  _newsphere->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  _newsphere->position = glm::vec3(-10.0f, 13.0f, 0.0f);
  _newsphere->computeBoundingBox();

  // init textures
  std::shared_ptr<Texture2D> earthTexture =
      std::make_shared<Texture2D>(earthTexturePath);
  std::shared_ptr<Texture2D> planetTexture =
      std::make_shared<Texture2D>(planetTexturePath);
  std::shared_ptr<Texture2D> groundTexture =
      std::make_shared<Texture2D>(groundTexturePath);


  // init materials
  _simpleMaterial.reset(new SimpleMaterial);
  _simpleMaterial->mapKd = planetTexture;

  _blendMaterial.reset(new BlendMaterial);
  _blendMaterial->kds[0] = glm::vec3(1.0f, 1.0f, 1.0f);
  _blendMaterial->kds[1] = glm::vec3(1.0f, 1.0f, 1.0f);
  _blendMaterial->mapKds[0] = groundTexture;
  _blendMaterial->mapKds[1] = earthTexture;
  _blendMaterial->blend = 0.0f;

  _checkerMaterial.reset(new CheckerMaterial);
  _checkerMaterial->repeat = 10;
  _checkerMaterial->colors[0] = glm::vec3(1.0f, 1.0f, 1.0f);
  _checkerMaterial->colors[1] = glm::vec3(0.0f, 0.0f, 0.0f);

  _lineMaterial.reset(new LineMaterial);
  _lineMaterial->color = glm::vec3(0.0f, 1.0f, 0.0f);
  _lineMaterial->width = 1.0f;

  // init skybox
  _skybox.reset(new SkyBox(skyboxTexturePaths));

  // init camera
  _camera.reset(new PerspectiveCamera(glm::radians(50.0f),
                                      1.0f * _windowWidth / _windowHeight, 0.1f,
                                      10000.0f));
  _camera->position.z = 10.0f;
  _camera->rotation =
      glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0),
                  glm::vec3(0.0, 1.0, 0.0));
  glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  _mouseInput.move.xOld = _mouseInput.move.xCurrent = 0.5 * _windowWidth;
  _mouseInput.move.yOld = _mouseInput.move.yCurrent = 0.5 * _windowHeight;
  glfwSetCursorPos(_window, _mouseInput.move.xCurrent,
                   _mouseInput.move.yCurrent);

  // init light
  _light.reset(new DirectionalLight());
  _light->rotation =
      glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

  _spotLight.reset(new SpotLight());
  _spotLight->position = glm::vec3(0.0f, 0.0f, 5.0f);
  _spotLight->rotation = glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

  _ambientLight.reset(new AmbientLight);

  // init shaders
  initSimpleShader();
  initBlendShader();
  initCheckerShader();
  initShader();
  initInstancedShader();

  // init imgui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(_window, true);
  ImGui_ImplOpenGL3_Init();

  // init bounding mode
  boundingmode = true;

  // add music
#if _WIN32
  PlayMusic(musicPath);
#endif
}

TextureMapping::~TextureMapping()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void TextureMapping::handleInput()
{
  if (gameOver)
  {
    if (_keyboardInput.keyStates[GLFW_KEY_ENTER] != GLFW_RELEASE)
    {
      YES = true;
    }
    if (YES && _keyboardInput.keyStates[GLFW_KEY_ENTER] == GLFW_RELEASE)
    {
      if (cursorvisible % 2 == 0)
      {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        _mouseInput.move.xOld = _mouseInput.move.xCurrent = 0.5 * _windowWidth;
        _mouseInput.move.yOld = _mouseInput.move.yCurrent = 0.5 * _windowHeight;
        glfwSetCursorPos(_window, _mouseInput.move.xCurrent,
                         _mouseInput.move.yCurrent);
        cursorvisible++;
      }
      else
      {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        _mouseInput.move.xOld = _mouseInput.move.xCurrent = 0.5 * _windowWidth;
        _mouseInput.move.yOld = _mouseInput.move.yCurrent = 0.5 * _windowHeight;
        glfwSetCursorPos(_window, _mouseInput.move.xCurrent,
                         _mouseInput.move.yCurrent);
        cursorvisible++;
      }
      YES = false;
    }
    return;
  }
  double t, k, y = 0;
  t = (float)glfwGetTime();
  k = (int)t % 8 + t - (int)t;
  if (k >= 0 && k < 2)
    y = (int)t % 2 + t - (int)t;
  else if (k >= 2 && k < 4)
    y = 2 - ((int)t % 2 + t - (int)t);
  else if (k >= 4 && k < 6)
    y = -((int)t % 2 + t - (int)t);
  else
    y = ((int)t % 2 + t - (int)t) - 2;

  bool firstMouse = true;
  const float angluarVelocity = 0.1f;
  const float angle = angluarVelocity * static_cast<float>(_deltaTime);
  const float anglel = 0.08 * y;
  const float angler = -0.08 * y;
  const glm::vec3 axis = _camera->getRight();

  _sphere->rotation = glm::angleAxis(angle, axis) * _sphere->rotation;
  _arml->rotation = _camera->rotation * glm::angleAxis(anglel, axis);
  _armr->rotation = _camera->rotation * glm::angleAxis(angler, axis);

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
    if (_sphere->scale.x < 0.03 || _sphere->scale.y < 0.03 ||
        _sphere->scale.z < 0.03)
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
    _camera.reset(new PerspectiveCamera(glm::radians(50.0f),
                                        1.0f * _windowWidth / _windowHeight,
                                        0.1f, 10000.0f));
    _camera->position.z = 0.0f;
    _camera->rotation =
        glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0),
                    glm::vec3(0.0, 1.0, 0.0));
  }
  if (_keyboardInput.keyStates[GLFW_KEY_B] == GLFW_PRESS)
  {
    _camera->fovy = 0.872664;
  }
  Camera *camera = _camera.get();
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
    if (player == 0)
    {
      cameraPos = cameraMoveSpeed * _camera->getFront();
      if (!checkBounding(_camera->position + 11.0f * cameraPos))
        _camera->position += cameraPos;
    }
    else
    {
      cameraPos = cameraMoveSpeed * _camera->getFront();
      if (!checkBounding(_camera->position + 11.0f * cameraPos))
      {
        _camera->position.x += cameraPos.x;
        _camera->position.z += cameraPos.z;
      }
    }
  }
  if (_keyboardInput.keyStates[GLFW_KEY_D] != GLFW_RELEASE)
  {
    if (player == 0)
    {
      cameraPos = _camera->getRight() * cameraMoveSpeed;
      if (!checkBounding(_camera->position + 11.0f * cameraPos))
        _camera->position += cameraPos;
    }
    else
    {
      cameraPos = _camera->getRight() * cameraMoveSpeed;
      if (!checkBounding(_camera->position + 11.0f * cameraPos))
      {
        _camera->position.x += cameraPos.x;
        _camera->position.z += cameraPos.z;
      }
    }
  }
  if (_keyboardInput.keyStates[GLFW_KEY_S] != GLFW_RELEASE)
  {
    if (player == 0)
    {
      cameraPos = cameraMoveSpeed * _camera->getFront();
      if (!checkBounding(_camera->position - 11.0f * cameraPos))
        _camera->position -= cameraPos;
    }
    else
    {
      cameraPos = cameraMoveSpeed * _camera->getFront();
      if (!checkBounding(_camera->position - 11.0f * cameraPos))
      {
        _camera->position.x -= cameraPos.x;
        _camera->position.z -= cameraPos.z;
      }
    }
  }
  if (_keyboardInput.keyStates[GLFW_KEY_A] != GLFW_RELEASE)
  {
    if (player == 0)
    {
      cameraPos = _camera->getRight() * cameraMoveSpeed;
      if (!checkBounding(_camera->position - 11.0f * cameraPos))
        _camera->position -= cameraPos;
    }
    else
    {
      cameraPos = _camera->getRight() * cameraMoveSpeed;
      if (!checkBounding(_camera->position - 11.0f * cameraPos))
      {
        _camera->position.x -= cameraPos.x;
        _camera->position.z -= cameraPos.z;
      }
    }
  }
  if (_keyboardInput.keyStates[GLFW_KEY_E] != GLFW_RELEASE)
  {
    if (player == 0)
    {
      cameraPos = cameraMoveSpeed * cameraUp;
      if (!checkBounding(_camera->position - 11.0f * cameraPos))
        _camera->position -= cameraPos;
    }
    else
    {
      _camera->position.y = -14.5;
      hint = 0;
    }
  }
  if (_keyboardInput.keyStates[GLFW_KEY_Q] != GLFW_RELEASE)
  {
    if (player == 0)
    {
      cameraPos = cameraMoveSpeed * cameraUp;
      if (!checkBounding(_camera->position + 11.0f * cameraPos))
        _camera->position += cameraPos;
    }
    else
    {
      _camera->position.y = 10.0;
      hint = 1;
    }
  }
  if (_keyboardInput.keyStates[GLFW_KEY_N] != GLFW_RELEASE)
  {
    _camera->position = glm::vec3(13.269848, -14.500000, 23.273075);
#if _WIN32
    PlayMusic(musicPath2);
#endif
  }
  if (_keyboardInput.keyStates[GLFW_KEY_M] != GLFW_RELEASE)
  {
    _camera->position = glm::vec3(13.438785, -14.500000, -23.279537);
    winWindow = true;
    gameOver = true;
  }

  if (_keyboardInput.keyStates[GLFW_KEY_P] != GLFW_RELEASE)
  {
#if _WIN32
    SaveScreenShot(_windowWidth, _windowHeight);
#endif
  }

  if (_keyboardInput.keyStates[GLFW_KEY_K] != GLFW_RELEASE)
  {
    knocky = true;
  }
  if (knocky == true && _keyboardInput.keyStates[GLFW_KEY_K] == GLFW_RELEASE)
  {
    knock = !knock;
    knocky = false;
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
      glfwSetCursorPos(_window, _mouseInput.move.xCurrent,
                       _mouseInput.move.yCurrent);
      cursorvisible++;
    }
    else
    {
      glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      _mouseInput.move.xOld = _mouseInput.move.xCurrent = 0.5 * _windowWidth;
      _mouseInput.move.yOld = _mouseInput.move.yCurrent = 0.5 * _windowHeight;
      glfwSetCursorPos(_window, _mouseInput.move.xCurrent,
                       _mouseInput.move.yCurrent);
      cursorvisible++;
    }
    YES = false;
  }
  if (cursorvisible % 2 == 0)
  {
    if (_mouseInput.move.xCurrent != _mouseInput.move.xOld)
    {
      double mouse_movement_in_x_direction =
          -(_mouseInput.move.xCurrent - _mouseInput.move.xOld);
      glm::vec3 right = glm::vec3(0.0f, 1.0f, 0.0f);
      double thetax = 0.003 * mouse_movement_in_x_direction;
      camera->rotation =
          glm::quat{(float)cos(thetax / 2), (float)sin(thetax / 2) * right} *
          camera->rotation;
      _mouseInput.move.xOld = _mouseInput.move.xCurrent;
    }
    if (_mouseInput.move.yCurrent != _mouseInput.move.yOld)
    {
      double mouse_movement_in_y_direction =
          -(_mouseInput.move.yCurrent - _mouseInput.move.yOld);
      glm::vec3 up = camera->getRight();
      double thetay = 0.003 * mouse_movement_in_y_direction;
      camera->rotation =
          glm::quat{(float)cos(thetay / 2), (float)sin(thetay / 2) * up} *
          camera->rotation;
      _mouseInput.move.yOld = _mouseInput.move.yCurrent;
    }
  }
  if (_mouseInput.scroll.y != 0)
  {
    if (_camera->fovy >= 0.05f && _camera->fovy <= 2.8f)
      _camera->fovy -= 0.02 * _mouseInput.scroll.y;
    if (_camera->fovy <= 0.05f)
      _camera->fovy = 0.05f;
    if (_camera->fovy >= 2.8f)
      _camera->fovy = 2.8f;
    _mouseInput.scroll.y = 0;
  }
}

void TextureMapping::renderFrame()
{
    printf("%f,%f,%f\n", _camera->position.x, _camera->position.y, _camera->position.z);

  glm::vec3 XYD{xd, yd, 1.0f};
  static bool wireframe = false;
  showFpsInWindowTitle();

  glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  if (wireframe)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  const glm::mat4 projection = _camera->getProjectionMatrix();
  const glm::mat4 view = _camera->getViewMatrix();
  glm::mat4 view1 = _camera->getViewMatrix();

  double t, k, y = 0;
  t = (float)glfwGetTime();
  k = (int)t % 8 + t - (int)t;
  if (k >= 0 && k < 2)
    y = (int)t % 2 + t - (int)t;
  else if (k >= 2 && k < 4)
    y = 2 - ((int)t % 2 + t - (int)t);
  else if (k >= 4 && k < 6)
    y = (int)t % 2 + t - (int)t;
  else
    y = 2 - ((int)t % 2 + t - (int)t);

  std::shared_ptr<Model> curNPC = NPC.changeModel();

  // draw planet
  switch (_renderMode)
  {
  case RenderMode::Game:
    player = 1;
    _blendShader->use();
    _blendShader->setMat4("projection", projection);
    _blendShader->setMat4("view", view);
    _blendShader->setMat4("model", _maze->getModelMatrix());
    _maze->draw();
    _armr->position = _camera->position;
    // _blendShader->setMat4("model", _armr->getModelMatrix());
    // _armr->draw();
    _arml->position = _camera->position;
    _blendShader->setMat4("model", _arml->getModelMatrix());
    _arml->draw();

    if ((((_bear0->position.x - _camera->position.x) * (_bear0->position.x - _camera->position.x) + (_bear0->position.z - _camera->position.z) * (_bear0->position.z - _camera->position.z)) < 16.0) && (((_bear0->position.x - _camera->position.x) * (_bear0->position.x - _camera->position.x) + (_bear0->position.z - _camera->position.z) * (_bear0->position.z - _camera->position.z)) >= 1.0))
      if ((_bear0->position.y - _camera->position.y) < 1.0 && (_bear0->position.y - _camera->position.y) > -1.0)
      {
        if (_bear0->position.x > _camera->position.x)
          _bear0->position.x -= 0.01 * (3.0 - (_bear0->position.x - _camera->position.x));
        if (_bear0->position.x < _camera->position.x)
          _bear0->position.x += 0.01 * (3.0 - (_bear0->position.x - _camera->position.x));
        if (_bear0->position.z > _camera->position.z)
          _bear0->position.z -= 0.01 * (3.0 - (_bear0->position.z - _camera->position.z));
        if (_bear0->position.z < _camera->position.z)
          _bear0->position.z += 0.01 * (3.0 - (_bear0->position.z - _camera->position.z));
      }
    if (((_bear0->position.x - _camera->position.x) * (_bear0->position.x - _camera->position.x) + (_bear0->position.z - _camera->position.z) * (_bear0->position.z - _camera->position.z)) <= 1.0)
    {
      _spotLight->position = _camera->position + glm::vec3(0.0f, 0.0f, 0.0f);
      _spotLight->rotation = glm::angleAxis(glm::radians(0.0f), -glm::vec3(1.0f, 1.0f, 1.0f));
      if (neng < 0.6)
      {
        neng += 0.002;
        _spotLight->angle = neng;
        loseWindow = true;
        gameOver = true;
      }
      _spotLight->color = {1.0f, 0.0f, 0.0f};
      _light->intensity = 0.0;
    }
    _blendShader->setMat4("model", _bear0->getModelMatrix());
    _bear0->draw();
    if (hint == 1)
    {
      _bear1->position.x = _camera->position.x;
      _bear1->position.y = -14.0f;
      _bear1->position.z = _camera->position.z;

      _blendShader->setMat4("model", _bear1->getModelMatrix());
      _bear1->draw();
      hint = 0;
    }

    if (knock == true)
    {
      _door->position = glm::vec3(10.0f, -14.4f, 22.6f);
      _door->computeBoundingBox();
    }
    else
    {
      _door->position = glm::vec3(10.0f, -13.4f, 22.6f);
      _door->computeBoundingBox();
    }
    _blendShader->setMat4("model", _door->getModelMatrix());
    _door->draw();
    _blendShader->setVec3("light.direction", _light->getFront() * XYD);
    _blendShader->setVec3("light.color", _light->color);
    _blendShader->setFloat("light.intensity", _light->intensity);
    _blendShader->setVec3("material.kds[0]", _blendMaterial->kds[0]);
    _blendShader->setVec3("material.kds[1]", _blendMaterial->kds[1]);
    _blendShader->setFloat("material.blend", _blendMaterial->blend);

    _blendShader->setVec3("spotLight.position", _spotLight->position);
    _blendShader->setVec3("spotLight.direction", _spotLight->getFront());
    _blendShader->setFloat("spotLight.intensity", _spotLight->intensity);
    _blendShader->setVec3("spotLight.color", _spotLight->color);
    _blendShader->setFloat("spotLight.angle", _spotLight->angle);
    _blendShader->setFloat("spotLight.kc", _spotLight->kc);
    _blendShader->setFloat("spotLight.kl", _spotLight->kl);
    _blendShader->setFloat("spotLight.kq", _spotLight->kq);

    _blendShader->setVec3("ambientLight.color", _ambientLight->color);
    _blendShader->setFloat("ambientLight.intensity", _ambientLight->intensity);
    glActiveTexture(GL_TEXTURE0);
    _blendMaterial->mapKds[0]->bind();
    glActiveTexture(GL_TEXTURE1);
    _blendMaterial->mapKds[1]->bind();
    // _blendShader->setInt("mapKds[1]", 1);
    _blendShader->setMat4("model", _armr->getModelMatrix());
    _armr->draw();
    break;
  case RenderMode::Show:
    player = 0;
    _blendShader->use();
    _blendShader->setMat4("projection", projection);
    _blendShader->setMat4("view", view);
    _blendShader->setMat4("model", _sphere->getModelMatrix());
    _sphere->draw();
    if (importFlag)
    {
      _bunny->scale = glm::vec3(y + 0.3, y + 0.3, y + 0.3);
      _blendShader->setMat4("model", _bunny->getModelMatrix());
      _bunny->draw();
    }
    _blendShader->setMat4("model", _cube->getModelMatrix());
    _cube->draw();
    _blendShader->setMat4("model", _cone->getModelMatrix());
    _cone->draw();
    _blendShader->setMat4("model", _cylinder->getModelMatrix());
    _cylinder->draw();
    _blendShader->setMat4("model", _roundtable->getModelMatrix());
    _roundtable->draw();

    _blendShader->setMat4("model", _maze->getModelMatrix());
    _maze->draw();
    _blendShader->setMat4("model", curNPC->getModelMatrix());
    curNPC->draw();
    if (knock == true)
    {
      _door->position = glm::vec3(10.2f, -14.4f, 22.6f);
      _door->computeBoundingBox();
    }
    else
    {
      _door->position = glm::vec3(10.2f, -13.4f, 22.6f);
      _door->computeBoundingBox();
    }
    _blendShader->setMat4("model", _door->getModelMatrix());
    _door->draw();
    _blendShader->setMat4("model", _newsphere->getModelMatrix());
    _newsphere->draw();

    _blendShader->setVec3("light.direction", _light->getFront() * XYD);
    _blendShader->setVec3("light.color", _light->color);
    _blendShader->setFloat("light.intensity", _light->intensity);
    _blendShader->setVec3("material.kds[0]", _blendMaterial->kds[0]);
    _blendShader->setVec3("material.kds[1]", _blendMaterial->kds[1]);
    _blendShader->setFloat("material.blend", _blendMaterial->blend);

    _blendShader->setVec3("spotLight.position", _spotLight->position);
    _blendShader->setVec3("spotLight.direction", _spotLight->getFront());
    _blendShader->setFloat("spotLight.intensity", _spotLight->intensity);
    _blendShader->setVec3("spotLight.color", _spotLight->color);
    _blendShader->setFloat("spotLight.angle", _spotLight->angle);
    _blendShader->setFloat("spotLight.kc", _spotLight->kc);
    _blendShader->setFloat("spotLight.kl", _spotLight->kl);
    _blendShader->setFloat("spotLight.kq", _spotLight->kq);

    _blendShader->setVec3("ambientLight.color", _ambientLight->color);
    _blendShader->setFloat("ambientLight.intensity", _ambientLight->intensity);

    glActiveTexture(GL_TEXTURE0);
    _blendMaterial->mapKds[0]->bind();
    glActiveTexture(GL_TEXTURE1);
    _blendMaterial->mapKds[1]->bind();
    _blendShader->setInt("mapKds[1]", 1);

    break;
  case RenderMode::Checker:
    _checkerShader->use();
    _checkerShader->setMat4("projection", projection);
    _checkerShader->setMat4("view", view);
    _checkerShader->setMat4("model", _sphere->getModelMatrix());
    _sphere->draw();
    if (importFlag)
    {
      _bunny->scale = glm::vec3(y + 0.3, y + 0.3, y + 0.3);
      _checkerShader->setMat4("model", _bunny->getModelMatrix());
      _bunny->draw();
    }
    _checkerShader->setMat4("model", _cube->getModelMatrix());
    _cube->draw();
    _checkerShader->setInt("material.repeat", _checkerMaterial->repeat);
    _checkerShader->setVec3("material.colors[0]", _checkerMaterial->colors[0]);
    _checkerShader->setVec3("material.colors[1]", _checkerMaterial->colors[1]);
    break;
  }

  _lineShader->use();
  _lineShader->setMat4("projection", projection);
  _lineShader->setMat4("view", view);
  _lineShader->setVec3("material.color", _lineMaterial->color);

  if (importFlag)
  {
    _lineShader->setMat4("model", _bunny->getModelMatrix());
    _bunny->drawBoundingBox();
  }
  _lineShader->setMat4("model", _roundtable->getModelMatrix());
  _roundtable->drawBoundingBox();
  _lineShader->setMat4("model", _newsphere->getModelMatrix());
  _newsphere->drawBoundingBox();
  _lineShader->setMat4("model", _cube->getModelMatrix());
  _cube->drawBoundingBox();
  _lineShader->setMat4("model", _maze->getModelMatrix());
  _maze->drawBoundingBox();
  _lineShader->setMat4("model", _door->getModelMatrix());
  _door->drawBoundingBox();
  glLineWidth(_lineMaterial->width);

  _skybox->draw(projection, view);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  const auto flags =
      ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;

  if (!ImGui::Begin("Control Panel", nullptr, flags))
  {
    ImGui::End();
  }
  else
  {
    ImGui::SetWindowPos(ImVec2(20, 5), ImGuiCond_Always);
    ImGui::Text("Render Mode");
    ImGui::Separator();
    ImGui::RadioButton("Game", (int *)&_renderMode,
                       (int)(RenderMode::Game));
    ImGui::NewLine();

    ImGui::RadioButton("Show", (int *)&_renderMode,
                       (int)(RenderMode::Show));
    ImGui::ColorEdit3("kd1", (float *)&_blendMaterial->kds[0]);
    ImGui::ColorEdit3("kd2", (float *)&_blendMaterial->kds[1]);
    ImGui::SliderFloat("blend", &_blendMaterial->blend, 0.0f, 1.0f);
    ImGui::NewLine();

    ImGui::RadioButton("Checker Shading", (int *)&_renderMode,
                       (int)(RenderMode::Checker));
    ImGui::SliderInt("repeat", &_checkerMaterial->repeat, 2, 20);
    ImGui::ColorEdit3("color1", (float *)&_checkerMaterial->colors[0]);
    ImGui::ColorEdit3("color2", (float *)&_checkerMaterial->colors[1]);
    ImGui::Checkbox("wireframe", &wireframe);
    ImGui::Checkbox("boundingbox", &boundingmode);
    ImGui::NewLine();

    ImGui::Text("Directional Light");
    ImGui::Separator();
    ImGui::SliderFloat("intensity", &_light->intensity, 0.0f, 2.0f);
    ImGui::SliderFloat("xd", &xd, -2.0f, 2.0f);
    ImGui::SliderFloat("yd", &yd, -2.0f, 2.0f);
    ImGui::ColorEdit3("color", (float *)&_light->color);
    ImGui::NewLine();

    ImGui::Text("Ambient light");
    ImGui::Separator();
    ImGui::SliderFloat("intensity##5", &_ambientLight->intensity, 0.0f, 10.0f);
    ImGui::ColorEdit3("color##1", (float *)&_ambientLight->color);
    ImGui::NewLine();

    ImGui::Text("spot light");
    ImGui::Separator();
    ImGui::SliderFloat("intensity##3", &_spotLight->intensity, 0.0f, 15.0f);
    ImGui::ColorEdit3("color##3", (float *)&_spotLight->color);
    ImGui::SliderFloat("angle##3", (float *)&_spotLight->angle, 0.0f, glm::radians(180.0f), "%f rad");
    ImGui::NewLine();

    // ImGui::Separator();
    // ImGui::RadioButton("Show bounding Box", (int *)&_renderMode,
    //                    (int)(RenderMode::Simple));
    // ImGui::NewLine();
    ImGui::Text("OBJ Export");
    if (ImGui::Button("Import"))
    {
      importFlag = 1;
      inputModel = new Model(modelPath1);
      _bunny.reset(inputModel);
      _bunny->scale = glm::vec3(1.0f, 1.0f, 1.0f);
      _bunny->position = glm::vec3(10.0f, 5.0f, 0.0f);
      _bunny->computeBoundingBox();
    }
    ImGui::SameLine();
    if (ImGui::Button("Export"))
    {
      bool flag = ExportObj(inputModel);
    }

    ImGui::End();
  }

  if (loseWindow)
  {
    ImGui::Begin("GameOver", &loseWindow); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::SetWindowPos(ImVec2(540, 320), ImGuiCond_Always);
    ImGui::Text("GameOver! You Lose!");
    if (ImGui::Button("Restart!"))
    {
      loseWindow = false;
      gameOver = false;
      _camera->position = glm::vec3(13.269848, -14.500000, 23.273075);
      _spotLight->color = {1.0f, 0.0f, 0.0f};
      _light->intensity = 1.0f;
      _spotLight->intensity = 0;
    }
    ImGui::End();
  }

  if (winWindow)
  {
    ImGui::Begin("GameOver", &winWindow); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::SetWindowPos(ImVec2(540, 320), ImGuiCond_Always);
    ImGui::Text("GameOver! You Win!");
    if (ImGui::Button("Restart!"))
    {
      winWindow = false;
      gameOver = false;
      _camera->position = glm::vec3(13.269848, -14.500000, 23.273075);
    }
    ImGui::End();
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool TextureMapping::checkBounding(const glm::vec3 &positon)
{
  if (_cube->checkBoundingBox(positon))
    return true;
  if (_roundtable->checkBoundingBox(positon))
    return true;
  if (_door->checkBoundingBox(positon))
    return true;
  if (_maze->checkInBoundingBox(positon))
    return true;
  if (_newsphere->checkBoundingBall(positon))
    return true;
  // if (NPC.changeModel()->checkBoundingBox(positon))
  //   return true;

  return false;
}
