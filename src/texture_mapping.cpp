#define _USE_MATH_DEFINES
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

#include "genBaseElements.h"
#include "texture_mapping.h"
#include "media.h"
#include "shaders.h"
#include "roaming.h"

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

int _amount = 0;
float xd = -1.0, yd = 1.0;

TextureMapping::TextureMapping(const Options &options) : Application(options) {
  genCube(cubeVertices, cubeIndices);
  genCone(coneVertices, coneIndices);
  genCylinder(cylinderVertices, cylinderIndices);
  genRoundTable(roundtableVertices, roundtableIndices);
  genShpere(newsphereVertices, newsphereIndices);
  // init model

  _sphere.reset(new Model(modelPath));
  _sphere->scale = glm::vec3(3.0f, 3.0f, 3.0f);
  _sphere->position = glm::vec3(-10.0f, 5.0f, 0.0f);

  _bunny.reset(new Model(modelPath1));
  _bunny->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  _bunny->position = glm::vec3(10.0f, 5.0f, 0.0f);

  _maze.reset(new Model(modelPath2));
  _maze->scale = glm::vec3(0.05f, 0.05f, 0.05f);
  _maze->position = glm::vec3(-10.0f, -15.0f, 0.0f);

  _cube.reset(new Model(cubeVertices, cubeIndices));
  _cube->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  _cube->position = glm::vec3(10.0f, -5.0f, 0.0f);

  _cone.reset(new Model(coneVertices, coneIndices));
  _cone->scale = glm::vec3(2.0f, 2.0f, 2.0f);
  _cone->position = glm::vec3(-10.0f, -15.0f, 0.0f);

  _cylinder.reset(new Model(cylinderVertices, cylinderIndices));
  _cylinder->scale = glm::vec3(2.0f, 2.0f, 2.0f);
  _cylinder->position = glm::vec3(-10.0f, -5.0f, 0.0f);

  _roundtable.reset(new Model(roundtableVertices, roundtableIndices));
  _roundtable->scale = glm::vec3(2.0f, 2.0f, 2.0f);
  _roundtable->position = glm::vec3(20.0f, 5.0f, 0.0f);

  _newsphere.reset(new Model(newsphereVertices, newsphereIndices));
  _newsphere->scale = glm::vec3(2.0f, 2.0f, 2.0f);
  _newsphere->position = glm::vec3(40.0f, 5.0f, 0.0f);


  // init textures
  std::shared_ptr<Texture2D> earthTexture =
      std::make_shared<Texture2D>(earthTexturePath);
  std::shared_ptr<Texture2D> planetTexture =
      std::make_shared<Texture2D>(planetTexturePath);

  // init materials
  _simpleMaterial.reset(new SimpleMaterial);
  _simpleMaterial->mapKd = planetTexture;

  _blendMaterial.reset(new BlendMaterial);
  _blendMaterial->kds[0] = glm::vec3(1.0f, 1.0f, 1.0f);
  _blendMaterial->kds[1] = glm::vec3(1.0f, 1.0f, 1.0f);
  _blendMaterial->mapKds[0] = planetTexture;
  _blendMaterial->mapKds[1] = earthTexture;
  _blendMaterial->blend = 0.0f;

  _checkerMaterial.reset(new CheckerMaterial);
  _checkerMaterial->repeat = 10;
  _checkerMaterial->colors[0] = glm::vec3(1.0f, 1.0f, 1.0f);
  _checkerMaterial->colors[1] = glm::vec3(0.0f, 0.0f, 0.0f);

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

  _light.reset(new DirectionalLight());
  _light->rotation =
      glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

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
}

TextureMapping::~TextureMapping()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void TextureMapping::renderFrame() {
  
    glm::vec3 XYD{ xd, yd, 1.0f };
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

  // draw planet
  switch (_renderMode)
  {
  case RenderMode::Simple:
    // 1. use the shader
    _simpleShader->use();
    // 2. transfer mvp matrices to gpu
    _simpleShader->setMat4("projection", projection);
    _simpleShader->setMat4("view", view);
    _simpleShader->setMat4("model", _sphere->getModelMatrix());
    //    _sphere->draw();
    _bunny->scale = glm::vec3(y + 0.3, y + 0.3, y + 0.3);

    _shader->use();
    _shader->setMat4("projection", projection);
    _shader->setMat4("view", view);
    //_simpleShader->setMat4("model", _bunny->getModelMatrix());
    _shader->setMat4("model", _bunny->getModelMatrix());
    _bunny->draw();
    //_simpleShader->setMat4("model", _cube->getModelMatrix());
    _shader->setMat4("model", _cube->getModelMatrix());
    _cube->draw();
    _shader->setMat4("model", _cone->getModelMatrix());
    //    _cone->draw();
    _shader->setMat4("model", _cylinder->getModelMatrix());
    //    _cylinder->draw();
    _shader->setMat4("model", _roundtable->getModelMatrix());
    _roundtable->draw();
    _shader->setMat4("model", _newsphere->getModelMatrix());
    _newsphere->draw();
    _shader->setMat4("model", _maze->getModelMatrix());
    _maze->draw();

    // 3. enable textures and transform textures to gpu
    glActiveTexture(GL_TEXTURE0);
    _simpleMaterial->mapKd->bind();
    break;
  case RenderMode::Blend:

    // 1. use the shader
    _blendShader->use();
    // 2. transfer mvp matrices to gpu
    _blendShader->setMat4("projection", projection);
    _blendShader->setMat4("view", view);
    _blendShader->setMat4("model", _sphere->getModelMatrix());
    _sphere->draw();
    _bunny->scale = glm::vec3(y + 0.3, y + 0.3, y + 0.3);
    _blendShader->setMat4("model", _bunny->getModelMatrix());
    _bunny->draw();
    _blendShader->setMat4("model", _cube->getModelMatrix());
    _cube->draw();
    _blendShader->setMat4("maze", _cube->getModelMatrix());
    _maze->draw();
    _blendShader->setMat4("model", _newsphere->getModelMatrix());
    _newsphere->draw();
    // 3. transfer light attributes to gpu
    _blendShader->setVec3("light.direction", _light->getFront() * XYD);
    _blendShader->setVec3("light.color", _light->color);
    _blendShader->setFloat("light.intensity", _light->intensity);
    // 4. transfer materials to gpu
    // 4.1 transfer simple material attributes
    _blendShader->setVec3("material.kds[0]", _blendMaterial->kds[0]);
    _blendShader->setVec3("material.kds[1]", _blendMaterial->kds[1]);
    // 4.2 transfer blend cofficient to gpu
    _blendShader->setFloat("material.blend", _blendMaterial->blend);

    glActiveTexture(GL_TEXTURE0);
    _blendMaterial->mapKds[0]->bind();
    glActiveTexture(GL_TEXTURE1);
    _blendMaterial->mapKds[1]->bind();
    _blendShader->setInt("mapKds[1]", 1);
    break;
  case RenderMode::Checker:
    // 1. use the shader
    _checkerShader->use();
    // 2. transfer mvp matrices to gpu
    _checkerShader->setMat4("projection", projection);
    _checkerShader->setMat4("view", view);
    _checkerShader->setMat4("model", _sphere->getModelMatrix());
    _sphere->draw();
    _bunny->scale = glm::vec3(y + 0.3, y + 0.3, y + 0.3);
    _checkerShader->setMat4("model", _bunny->getModelMatrix());
    _bunny->draw();
    _checkerShader->setMat4("model", _cube->getModelMatrix());
    _cube->draw();
    // 3. transfer material attributes to gpu
    _checkerShader->setInt("material.repeat", _checkerMaterial->repeat);
    _checkerShader->setVec3("material.colors[0]", _checkerMaterial->colors[0]);
    _checkerShader->setVec3("material.colors[1]", _checkerMaterial->colors[1]);
    break;
  }

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
    ImGui::Text("Render Mode");
    ImGui::Separator();
    ImGui::RadioButton("Simple Texture Shading", (int *)&_renderMode,
                       (int)(RenderMode::Simple));
    ImGui::NewLine();

    ImGui::RadioButton("Blend Texture Shading", (int *)&_renderMode,
                       (int)(RenderMode::Blend));
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
    ImGui::NewLine();

    ImGui::Text("Directional light");
    ImGui::Separator();
    ImGui::SliderFloat("intensity", &_light->intensity, 0.0f, 2.0f);
    ImGui::SliderFloat("xd", &xd, -2.0f, 2.0f);
    ImGui::SliderFloat("yd", &yd, -2.0f, 2.0f); ImGui::ColorEdit3("color", (float *)&_light->color);
    ImGui::NewLine();

    ImGui::End();
  }
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
