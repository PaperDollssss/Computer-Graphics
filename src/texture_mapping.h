#pragma once

#include <memory>
#include <string>
#include <windows.h>

#include "base/application.h"
#include "base/camera.h"
#include "base/glsl_program.h"
#include "base/light.h"
#include "base/model.h"
#include "base/skybox.h"
#include "base/texture.h"

#include "NPC.h"
#include "genBaseElements.h"
#include "screenshot.h"

enum class RenderMode
{
  Game,
  Show,
  Checker
};

struct SimpleMaterial
{
  std::shared_ptr<Texture2D> mapKd;
};

struct BlendMaterial
{
  glm::vec3 kds[2];
  std::shared_ptr<Texture2D> mapKds[2];
  float blend;
};

struct CheckerMaterial
{
  int repeat;
  glm::vec3 colors[2];
};

struct LineMaterial
{
  glm::vec3 color;
  float width;
};

class TextureMapping : public Application
{
public:
  TextureMapping(const Options &options);

  ~TextureMapping();

private:
  int cursorvisible = 0;
  bool YES = false;
  bool boundingmode;
  double timet = 0.0;
  float OrbitRadius = 10.0f;
  float OrbitX = 0, OrbitZ = OrbitRadius;

  std::unique_ptr<Model> _sphere;
  std::unique_ptr<Model> _bunny;
  std::unique_ptr<Model> _cube;
  std::unique_ptr<Model> _cone;
  std::unique_ptr<Model> _cylinder;
  std::unique_ptr<Model> _roundtable;
  std::unique_ptr<Model> _maze;
  std::unique_ptr<Model> _door;
  std::unique_ptr<Model> _newsphere;
  std::unique_ptr<Model> _arml;
  std::unique_ptr<Model> _armr;
  std::unique_ptr<Model> _bear;


  // npc NPC;

  std::unique_ptr<SimpleMaterial> _simpleMaterial;
  std::unique_ptr<BlendMaterial> _blendMaterial;
  std::unique_ptr<CheckerMaterial> _checkerMaterial;

  std::unique_ptr<PerspectiveCamera> _camera;
  std::unique_ptr<DirectionalLight> _light;
  std::unique_ptr<SpotLight> _spotLight;
  std::unique_ptr<AmbientLight> _ambientLight;



  std::unique_ptr<LineMaterial> _lineMaterial;
  std::unique_ptr<GLSLProgram> _lineShader;
  std::unique_ptr<GLSLProgram> _lineInstancedShader;

  std::unique_ptr<GLSLProgram> _instancedShader;
  std::unique_ptr<GLSLProgram> _shader;
  std::unique_ptr<GLSLProgram> _simpleShader;
  std::unique_ptr<GLSLProgram> _blendShader;
  std::unique_ptr<GLSLProgram> _checkerShader;

  std::unique_ptr<SkyBox> _skybox;

  enum RenderMode _renderMode = RenderMode::Game;

  void initInstancedShader();

  void initShader();

  void initSimpleShader();

  void initBlendShader();

  void initCheckerShader();

  void handleInput() override;

  void renderFrame() override;

  std::vector<glm::mat4> _modelMatrices;

  bool checkBounding(const glm::vec3 &position);
};