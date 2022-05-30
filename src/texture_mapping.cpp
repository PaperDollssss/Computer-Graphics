#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

#include "texture_mapping.h"

const std::string modelPath = "../../media/sphere.obj";
const std::string modelPath1 = "../../media/nanosuit.obj";

const std::string earthTexturePath = "../../media/earthmap.jpg";
const std::string planetTexturePath = "../../media/planet_Quom1200.png";
int cursorvisible = 0;
bool YES = false;

std::vector<Vertex> v;
std::vector<uint32_t> i;
double timet = 0.0;
float OrbitRadius = 10.0f;
float OrbitX = 0, OrbitZ = OrbitRadius;

const std::vector<std::string> skyboxTexturePaths = {
    "../../media/starfield/Right_Tex.jpg",
    "../../media/starfield/Left_Tex.jpg",
    "../../media/starfield/Down_Tex.jpg",
    "../../media/starfield/Up_Tex.jpg",
    "../../media/starfield/Front_Tex.jpg",
    "../../media/starfield/Back_Tex.jpg"};

TextureMapping::TextureMapping(const Options &options) : Application(options) {

  Vertex CubeVertex[36] = {
      {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),
       glm::vec2(0.0f, 0.0f)},
      {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),
       glm::vec2(0.0f, 1.0f)},
      {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),
       glm::vec2(0.0f, 0.0f)}

      ,
      {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
       glm::vec2(0.0f, 0.0f)},
      {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
       glm::vec2(0.0f, 1.0f)},
      {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
       glm::vec2(0.0f, 0.0f)}

      ,
      {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),
       glm::vec2(0.0f, 1.0f)},
      {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),
       glm::vec2(0.0f, 1.0f)},
      {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),
       glm::vec2(0.0f, 0.0f)},
      {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),
       glm::vec2(1.0f, 0.0f)}

      ,
      {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
       glm::vec2(0.0f, 1.0f)},
      {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
       glm::vec2(0.0f, 1.0f)},
      {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
       glm::vec2(0.0f, 0.0f)},
      {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
       glm::vec2(1.0f, 0.0f)}

      ,
      {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f),
       glm::vec2(0.0f, 1.0f)},
      {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f),
       glm::vec2(0.0f, 0.0f)},
      {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f),
       glm::vec2(0.0f, 1.0f)}

      ,
      {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
       glm::vec2(0.0f, 1.0f)},
      {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
       glm::vec2(1.0f, 1.0f)},
      {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
       glm::vec2(1.0f, 0.0f)},
      {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
       glm::vec2(0.0f, 0.0f)},
      {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
       glm::vec2(0.0f, 1.0f)}};

  for (int x = 0; x < 36; x++) {
    v.push_back(Vertex(CubeVertex[x]));
    i.push_back(uint32_t(x));
  }
  int num_stacks = 100;
  double angle = 2 * M_PI / num_stacks;

  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  float radius = 3;
  float height = 5;

  Vertex tmp;
  tmp.position = glm::vec3(0, 0, 0);
  tmp.normal = glm::vec3(0, 0, 0);
  tmp.texCoord = glm::vec2(0, 0);
  vertices.push_back(tmp);
  for (int i = 0; i < num_stacks; ++i) {
    tmp.position =
        glm::vec3(cos(angle * i) * radius, -sin(angle * i) * radius, 0);
    tmp.normal = glm::vec3(0, 0, 0);
    tmp.texCoord = glm::vec2(0, 0);
    vertices.push_back(tmp);
    if (i > 0) {
      indices.push_back(0);
      indices.push_back(i);
      indices.push_back(i + 1);
      indices.push_back(i);
      indices.push_back(i + 1);
      indices.push_back(num_stacks + 1);
    } else if (i == 0) {
      indices.push_back(0);
      indices.push_back(num_stacks);
      indices.push_back(1);
      indices.push_back(1);
      indices.push_back(num_stacks + 1);
      indices.push_back(num_stacks);
    }
  }
  tmp.position = glm::vec3(0, 0, height);
  tmp.normal = glm::vec3(0, 0, 0);
  tmp.texCoord = glm::vec2(0, 0);
  vertices.push_back(tmp);
  // init model

  _sphere.reset(new Model(modelPath));
  _sphere->scale = glm::vec3(3.0f, 3.0f, 3.0f);
  _sphere->position = glm::vec3(-10.0f, 5.0f, 0.0f);

  _bunny.reset(new Model(modelPath1));
  _bunny->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  _bunny->position = glm::vec3(10.0f, 5.0f, 0.0f);

  _cube.reset(new Model(v, i));
  _cube->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  _cube->position = glm::vec3(10.0f, -5.0f, 0.0f);

  _cone.reset(new Model(vertices, indices));
  _cone->scale = glm::vec3(2.0f, 2.0f, 2.0f);
  _cone->position = glm::vec3(-10.0f, -5.0f, 0.0f);

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

  // init light
  _light.reset(new DirectionalLight());
  _light->rotation =
      glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

  // init shaders
  initSimpleShader();
  initBlendShader();
  initCheckerShader();
  initShader();

  // init imgui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(_window, true);
  ImGui_ImplOpenGL3_Init();
}

TextureMapping::~TextureMapping() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void TextureMapping::initShader() {
  const char *vsCode =
      "#version 330 core\n"
      "layout(location = 0) in vec3 aPosition;\n"
      "layout(location = 1) in vec3 aNormal;\n"
      "out vec3 worldPosition;\n"
      "out vec3 normal;\n"
      "uniform mat4 model;\n"
      "uniform mat4 view;\n"
      "uniform mat4 projection;\n"
      "void main() {\n"
      "	normal = mat3(transpose(inverse(model))) * aNormal;\n"
      "	worldPosition = vec3(model * vec4(aPosition, 1.0f));\n"
      "	gl_Position = projection * view * vec4(worldPosition, 1.0f);\n"
      "}\n";

  const char *fsCode =
      "#version 330 core\n"
      "in vec3 worldPosition;\n"
      "in vec3 normal;\n"
      "out vec4 fragColor;\n"
      "void main() {\n"
      "vec3 lightPosition = vec3(100.0f, 100.0f, 100.0f);\n"
      "// ambient color\n"
      "float ka = 0.1f;\n"
      "vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);\n"
      "vec3 ambient = ka * objectColor;\n"
      "// diffuse color\n"
      "float kd = 0.8f;\n"
      "vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);\n"
      "vec3 lightDirection = normalize(lightPosition - worldPosition);\n"
      "vec3 diffuse = kd * lightColor * max(dot(normalize(normal), "
      "lightDirection), 0.0f);\n"
      "fragColor = vec4(ambient + diffuse, 1.0f);\n"
      "}\n";

  _shader.reset(new GLSLProgram);
  _shader->attachVertexShader(vsCode);
  _shader->attachFragmentShader(fsCode);
  _shader->link();
}

void TextureMapping::initSimpleShader() {
  const char *vsCode =
      "#version 330 core\n"
      "layout(location = 0) in vec3 aPosition;\n"
      "layout(location = 1) in vec3 aNormal;\n"
      "layout(location = 2) in vec2 aTexCoord;\n"
      "out vec2 fTexCoord;\n"
      "uniform mat4 projection;\n"
      "uniform mat4 view;\n"
      "uniform mat4 model;\n"

      "void main() {\n"
      "	fTexCoord = aTexCoord;\n"
      "	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
      "}\n";

  const char *fsCode = "#version 330 core\n"
                       "in vec2 fTexCoord;\n"
                       "out vec4 color;\n"
                       "uniform sampler2D mapKd;\n"
                       "void main() {\n"
                       "	color = texture(mapKd, fTexCoord);\n"
                       "}\n";

  _simpleShader.reset(new GLSLProgram);
  _simpleShader->attachVertexShader(vsCode);
  _simpleShader->attachFragmentShader(fsCode);
  _simpleShader->link();
}

void TextureMapping::initBlendShader() {
  const char *vsCode =
      "#version 330 core\n"
      "layout(location = 0) in vec3 aPosition;\n"
      "layout(location = 1) in vec3 aNormal;\n"
      "layout(location = 2) in vec2 aTexCoord;\n"
      "out vec3 fPosition;\n"
      "out vec3 fNormal;\n"
      "out vec2 fTexCoord;\n"
      "uniform mat4 projection;\n"
      "uniform mat4 view;\n"
      "uniform mat4 model;\n"

      "void main() {\n"
      "	fPosition = vec3(model * vec4(aPosition, 1.0f));\n"
      "	fNormal = mat3(transpose(inverse(model))) * aNormal;\n"
      "	fTexCoord = aTexCoord;\n"
      "	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
      "}\n";

  // TODO: change the fragment shader code to achieve the following goals
  // + blend of the two textures
  // + lambert shading, i.e the color is affected by the light
  // -----------------------------------------------------------------
  const char *fsCode =
      "#version 330 core\n"
      "in vec3 fPosition;\n"
      "in vec3 fNormal;\n"
      "in vec2 fTexCoord;\n"
      "out vec4 color;\n"

      "struct DirectionalLight {\n"
      "	vec3 direction;\n"
      "	vec3 color;\n"
      "	float intensity;\n"
      "};\n"

      "struct Material {\n"
      "	vec3 kds[2];\n"
      "	float blend;\n"
      "};\n"

      "uniform Material material;\n"
      "uniform DirectionalLight light;\n"
      "uniform sampler2D mapKds[2];\n"

      "vec3 calcDirectionalLight(vec3 normal) {\n"
      "	vec3 lightDir = normalize(-light.direction);\n"
      "	vec3 diffuse = light.color * max(dot(lightDir, normal), 0.0f) * "
      "(material.kds[0]+material.kds[1]);\n"
      "	return light.intensity * diffuse ;\n"
      "}\n"

      "void main() {\n"
      "	vec3 normal = normalize(fNormal);\n"
      "	vec3 diffuse = calcDirectionalLight(normal);\n"
      "	vec3 ambient = 0.08*light.color * light.intensity * "
      "(material.kds[0]+material.kds[1]);\n"
      "	color = mix(texture(mapKds[0], fTexCoord), texture(mapKds[1], "
      "fTexCoord), material.blend) * vec4(diffuse+ambient, 1.0f);\n"
      "}\n";

  //----------------------------------------------------------------

  _blendShader.reset(new GLSLProgram);
  _blendShader->attachVertexShader(vsCode);
  _blendShader->attachFragmentShader(fsCode);
  _blendShader->link();
}

void TextureMapping::initCheckerShader() {
  const char *vsCode =
      "#version 330 core\n"
      "layout(location = 0) in vec3 aPosition;\n"
      "layout(location = 1) in vec3 aNormal;\n"
      "layout(location = 2) in vec2 aTexCoord;\n"
      "out vec2 fTexCoord;\n"
      "uniform mat4 projection;\n"
      "uniform mat4 view;\n"
      "uniform mat4 model;\n"
      "void main() {\n"
      "	fTexCoord = aTexCoord;\n"
      "	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
      "}\n";

  // TODO: change the following code to achieve procedural checker texture
  // hint: use the TexCoord to determine the color
  // modify your code here
  // --------------------------------------------------------------
  const char *fsCode = "#version 330 core\n"
                       "in vec2 fTexCoord;\n"
                       "out vec4 color;\n"

                       "struct Material {\n"
                       "	vec3 colors[2];\n"
                       "	int repeat;\n"
                       "};\n"

                       "uniform Material material;\n"

                       "void main() {\n"
                       "   vec3 colorChoose = (int(fTexCoord.x * "
                       "material.repeat) + int(fTexCoord.y * material.repeat)) "
                       "% 2 == 0 ? material.colors[0] : material.colors[1];\n"
                       "	color = vec4(colorChoose, 1.0f);\n"
                       "}\n";
  //----------------------------------------------------------------

  _checkerShader.reset(new GLSLProgram);
  _checkerShader->attachVertexShader(vsCode);
  _checkerShader->attachFragmentShader(fsCode);
  _checkerShader->link();
}

void TextureMapping::handleInput() {
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

  if (_keyboardInput.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
    glfwSetWindowShouldClose(_window, true);
    return;
  }

  if (_keyboardInput.keyStates[GLFW_KEY_EQUAL] != GLFW_RELEASE) {
    _sphere->scale += glm::vec3(0.03f, 0.03f, 0.03f);
  }
  if (_keyboardInput.keyStates[GLFW_KEY_MINUS] != GLFW_RELEASE) {
    _sphere->scale -= glm::vec3(0.03f, 0.03f, 0.03f);
    if (_sphere->scale.x < 0.03 || _sphere->scale.y < 0.03 ||
        _sphere->scale.z < 0.03)
      _sphere->scale = glm::vec3(0.03f, 0.03f, 0.03f);
  }
  if (_keyboardInput.keyStates[GLFW_KEY_R] != GLFW_RELEASE) {
    _sphere->position += glm::vec3(0.0f, 0.03f, 0.0f);
  }
  if (_keyboardInput.keyStates[GLFW_KEY_Y] != GLFW_RELEASE) {
    _sphere->position += glm::vec3(0.0f, -0.03f, 0.0f);
  }
  if (_keyboardInput.keyStates[GLFW_KEY_F] != GLFW_RELEASE) {
    _sphere->position += glm::vec3(-0.03f, 0.0f, 0.0f);
  }
  if (_keyboardInput.keyStates[GLFW_KEY_H] != GLFW_RELEASE) {
    _sphere->position += glm::vec3(0.03f, 0.0f, 0.0f);
  }
  if (_keyboardInput.keyStates[GLFW_KEY_T] != GLFW_RELEASE) {
    _sphere->position += glm::vec3(0.0f, 0.0f, -0.03f);
  }
  if (_keyboardInput.keyStates[GLFW_KEY_G] != GLFW_RELEASE) {
    _sphere->position += glm::vec3(0.0f, 0.0f, 0.03f);
  }

  /*if (_keyboardInput.keyStates[GLFW_KEY_SPACE] == GLFW_PRESS) {
          std::cout << "switch camera" << std::endl;
          _keyboardInput.keyStates[GLFW_KEY_SPACE] = GLFW_RELEASE;
          return;
  }*/

  if (_keyboardInput.keyStates[GLFW_KEY_SPACE] == GLFW_PRESS) {
    _camera.reset(new PerspectiveCamera(glm::radians(50.0f),
                                        1.0f * _windowWidth / _windowHeight,
                                        0.1f, 10000.0f));
    _camera->position.z = 10.0f;
    _camera->rotation =
        glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0),
                    glm::vec3(0.0, 1.0, 0.0));
  }
  if (_keyboardInput.keyStates[GLFW_KEY_B] == GLFW_PRESS) {
    _camera->fovy = 0.872664;
  }
  Camera *camera = _camera.get();
  if (_keyboardInput.keyStates[GLFW_KEY_O] != GLFW_RELEASE) {
    // cameraPos = cameraMoveSpeed * cameraFront;
    timet += 0.01;
    OrbitX = sin(timet) * OrbitRadius;
    OrbitZ = cos(timet) * OrbitRadius;
    // cameraPos = cameraMoveSpeed * _camera->getFront();
    //_camera->position += cameraPos;
    _camera->position = glm::vec3(OrbitX, _camera->position.y, OrbitZ);
  }

  if (_keyboardInput.keyStates[GLFW_KEY_W] != GLFW_RELEASE) {
    // cameraPos = cameraMoveSpeed * cameraFront;
    cameraPos = cameraMoveSpeed * _camera->getFront();
    _camera->position += cameraPos;
  }
  if (_keyboardInput.keyStates[GLFW_KEY_D] != GLFW_RELEASE) {
    // cameraPos = glm::normalize(glm::cross(cameraFront, cameraUp)) *
    // cameraMoveSpeed;
    cameraPos = _camera->getRight() * cameraMoveSpeed;
    _camera->position += cameraPos;
  }
  if (_keyboardInput.keyStates[GLFW_KEY_S] != GLFW_RELEASE) {
    // cameraPos = cameraMoveSpeed * cameraFront;
    cameraPos = cameraMoveSpeed * _camera->getFront();
    _camera->position -= cameraPos;
  }
  if (_keyboardInput.keyStates[GLFW_KEY_A] != GLFW_RELEASE) {
    // cameraPos = glm::normalize(glm::cross(cameraFront, cameraUp)) *
    // cameraMoveSpeed;
    cameraPos = _camera->getRight() * cameraMoveSpeed;
    _camera->position -= cameraPos;
  }
  if (_keyboardInput.keyStates[GLFW_KEY_E] != GLFW_RELEASE) {
    cameraPos = cameraMoveSpeed * cameraUp;
    _camera->position -= cameraPos;
  }
  if (_keyboardInput.keyStates[GLFW_KEY_Q] != GLFW_RELEASE) {
    cameraPos = cameraMoveSpeed * cameraUp;
    _camera->position += cameraPos;
  }

  if (_keyboardInput.keyStates[GLFW_KEY_ENTER] != GLFW_RELEASE) {
    YES = true;
  }
  if (YES == true && _keyboardInput.keyStates[GLFW_KEY_ENTER] == GLFW_RELEASE) {
    if (cursorvisible % 2 == 0) {
      glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      _mouseInput.move.xOld = _mouseInput.move.xCurrent = 0.5 * _windowWidth;
      _mouseInput.move.yOld = _mouseInput.move.yCurrent = 0.5 * _windowHeight;
      glfwSetCursorPos(_window, _mouseInput.move.xCurrent,
                       _mouseInput.move.yCurrent);
      cursorvisible++;
    } else {
      glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      _mouseInput.move.xOld = _mouseInput.move.xCurrent = 0.5 * _windowWidth;
      _mouseInput.move.yOld = _mouseInput.move.yCurrent = 0.5 * _windowHeight;
      glfwSetCursorPos(_window, _mouseInput.move.xCurrent,
                       _mouseInput.move.yCurrent);
      cursorvisible++;
    }
    YES = false;
  }

  if (cursorvisible % 2 == 0) {
    if (_mouseInput.move.xCurrent != _mouseInput.move.xOld) {
      // if (firstMouse)
      //{
      //	_mouseInput.move.xOld = _mouseInput.move.xCurrent;
      //	_mouseInput.move.yOld = _mouseInput.move.yCurrent;
      //	firstMouse = false;
      // }
      double mouse_movement_in_x_direction =
          -(_mouseInput.move.xCurrent - _mouseInput.move.xOld);
      glm::vec3 right = glm::vec3(0.0f, 1.0f, 0.0f);
      double thetax = 0.003 * mouse_movement_in_x_direction;
      camera->rotation =
          glm::quat{(float)cos(thetax / 2), (float)sin(thetax / 2) * right} *
          camera->rotation;
      _mouseInput.move.xOld = _mouseInput.move.xCurrent;
    }

    if (_mouseInput.move.yCurrent != _mouseInput.move.yOld) {
      // if (firstMouse)
      //{
      //	_mouseInput.move.xOld = _mouseInput.move.xCurrent;
      //	_mouseInput.move.yOld = _mouseInput.move.yCurrent;
      //	firstMouse = false;
      // }
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

  if (_mouseInput.scroll.y != 0) {
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

void TextureMapping::renderFrame() {
  // some options related to imGUI
  static bool wireframe = false;

  // trivial things
  showFpsInWindowTitle();

  glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  if (wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
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
  switch (_renderMode) {
  case RenderMode::Simple:
    // 1. use the shader
    _simpleShader->use();
    // 2. transfer mvp matrices to gpu
    _simpleShader->setMat4("projection", projection);
    _simpleShader->setMat4("view", view);
    _simpleShader->setMat4("model", _sphere->getModelMatrix());
    _sphere->draw();
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
    _cone->draw();

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
    // 3. transfer light attributes to gpu
    _blendShader->setVec3("light.direction", _light->getFront());
    _blendShader->setVec3("light.color", _light->color);
    _blendShader->setFloat("light.intensity", _light->intensity);
    // 4. transfer materials to gpu
    // 4.1 transfer simple material attributes
    _blendShader->setVec3("material.kds[0]", _blendMaterial->kds[0]);
    _blendShader->setVec3("material.kds[1]", _blendMaterial->kds[1]);
    // 4.2 transfer blend cofficient to gpu
    _blendShader->setFloat("material.blend", _blendMaterial->blend);
    // 4.3 TODO: enable textures and transform textures to gpu
    // write your code here
    //----------------------------------------------------------------
    // ...
    //----------------------------------------------------------------
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

  //_bunny->draw();
  //_sphere->draw();

  // draw skybox
  _skybox->draw(projection, view);

  // draw ui elements
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  const auto flags =
      ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;

  if (!ImGui::Begin("Control Panel", nullptr, flags)) {
    ImGui::End();
  } else {
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
    ImGui::ColorEdit3("color", (float *)&_light->color);
    ImGui::NewLine();

    ImGui::End();
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
