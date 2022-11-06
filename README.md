# Computer-Graphics Final Project

**《the Nightmares of Toy-Bear》**

> 魏辰 3200100505 地理信息科学
> 
> 杨可轶 3200101042 地理信息科学
> 
> 胡宇森 3200100578 地理信息科学
> 
> 黄睿 3200101027 地理信息科学

## 0 Foreword

### 0.0 Way to Compile and Hints

```bash
cmake -Bbuild .
cd build
cmake --build . --parallel 8
```

- 程序适应跨平台开发，如果是Windows平台，则建议使用Visual Studio打开
- 在MSVC+Visual Studio debug 模式下打开该程序，会报出绘制纹理向量越界问题，切换 release 模式即可解决该问题。

- 在windows下如果直接打开exe需要修改模型相对路径：将所有 ../ 改为 ../../

- 截屏生成的图片保存在
  - exe同目录：直接运行exe
  - 工程同目录：使用 Visual Studio 调试

### 0.1 总体要求
**40 total**

简单室内场景三维建模及真实感绘制

### 0.2 基本要求
**35 total, 5 each**
- [x] 基本体素的建模表达能力
- [x] 基本三维网格(obj)导入导出
- [x] 基本材质、纹理的显示与编辑
- [x] 基本几何变换(旋转、平移与缩放)
- [x] 基本光照明模型，基本光源的编辑
- [x] 场景漫游如Zoom In/Out, Pan, Orbit, Zoom to Fit等
- [x] 多帧连续绘制，屏幕截取与保存
### 0.3 额外要求
**5 each,  according to the specific effect. Up to 40 in total**
- [ ] NURBS曲面建模能力
- [x] 空间碰撞检测
- [ ] 光照模型细化
- [ ] 其他平台实现
- [x] 完整三维游戏，注重核心玩法实现
- [ ] 增强现实应用结合
- [x] 一定的对象表达与交互能力，如门、窗、墙等
### 0.4 其他
- [x] 添加音乐
- [ ] 其他……

## 1 Introduction
### 1.1 总体介绍

在完成基本要求的基础上，实现了基于八叉树的碰撞检测算法并将其应用至一个迷宫游戏。迷宫游戏的建模通过blender完成，包含声音元素、灯光元素、轻度惊悚元素，同时也具备场景交互功能。

### 1.2 模型简介

立方体建模：直接利用每个点的坐标进行绘制。

相对复杂基本体：以圆锥为例，利用多个三角形网格绘制基本体素，当三角形数量够多就能逼近基本体素的形态。

能、迷宫、跳舞的女人：外部模型导入。

## 2 Module implementation

### 2.1 基本体素建模表达

立方体建模：直接利用每个点的坐标进行绘制。

```c++
void genCube(std::vector<Vertex> &cubeVertices,
             std::vector<uint32_t> &cubeIndices) {
  Vertex v[6];
  int faces = 0;
  // 顶点坐标
  const glm::vec3 p[8] = {
      glm::vec3(1.0f, 1.0f, -1.0f),   glm::vec3(1.0f, 1.0f, 1.0f),
      glm::vec3(-1.0f, 1.0f, -1.0f),  glm::vec3(-1.0f, 1.0f, 1.0f),
      glm::vec3(1.0f, -1.0f, -1.0f),  glm::vec3(1.0f, -1.0f, 1.0f),
      glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, -1.0f, 1.0f),
  };
  // 第一个面信息
  glm::vec3 norm;
  norm = glm::vec3(0.0f, -1.0f, 0.0f);
  v[0].position = p[4];
  v[1].position = p[5];
  v[2].position = p[6];
  v[3].position = p[5];
  v[4].position = p[6];
  v[5].position = p[7];
  v[0].normal = norm;
  v[1].normal = norm;
  v[2].normal = norm;
  v[3].normal = norm;
  v[4].normal = norm;
  v[5].normal = norm;
  v[0].texCoord = glm::vec2(0.0f, 1.0f);
  v[1].texCoord = glm::vec2(1.0f, 1.0f);
  v[2].texCoord = glm::vec2(0.0f, 0.0f);
  v[3].texCoord = glm::vec2(1.0f, 1.0f);
  v[4].texCoord = glm::vec2(0.0f, 0.0f);
  v[5].texCoord = glm::vec2(1.0f, 0.0f);
  for (int i = 0; i < 6; i++) {
    cubeVertices.push_back(v[i]);
    cubeIndices.push_back(6 * faces + i);
  }
  // 另外五个面相似
  // ...
}
```

相对复杂基本体：以圆锥为例，利用多个三角形网格绘制基本体素，当三角形数量够多就能逼近基本体素的形态。

```c++
void genCone(std::vector<Vertex> &coneVertices,
             std::vector<uint32_t> &coneIndices) {
  // 参数初始化
  int num_stacks = 100;
  double angle = 2 * M_PI / num_stacks;
  int faces = 0, i = 0;
  float radius = 3;
  float height = 5;
  Vertex tmp[3];
  glm::vec3 norm;
  tmp[0].position = glm::vec3(0.0f, 0.0f, 0.0f);
  tmp[1].position =
      glm::vec3(radius * cos(i * angle), 0, radius * sin(i * angle));
  tmp[2].position = glm::vec3(radius * cos((i + 1) * angle), 0,
                              radius * sin((i + 1) * angle));
  tmp[0].normal = glm::vec3(0.0f, -1.0f, 0.0f);
  tmp[1].normal = glm::vec3(0.0f, -1.0f, 0.0f);
  tmp[2].normal = glm::vec3(0.0f, -1.0f, 0.0f);
  // 移动底部圆周的点，求出底面三角形相关参数
  for (i = 0; i < num_stacks; i++, faces++) {
    tmp[1].position = tmp[2].position;
    tmp[2].position = glm::vec3(radius * cos((i + 2) * angle), 0,
                                radius * sin((i + 2) * angle));
    coneVertices.push_back(tmp[0]);
    coneVertices.push_back(tmp[1]);
    coneVertices.push_back(tmp[2]);
    coneIndices.push_back(faces * 3 + 0);
    coneIndices.push_back(faces * 3 + 1);
    coneIndices.push_back(faces * 3 + 2);
  }
  tmp[0].position = glm::vec3(0.0f, height, 0.0f);
  tmp[1].position =
      glm::vec3(radius * cos(i * angle), 0, radius * sin(i * angle));
  tmp[2].position = glm::vec3(radius * cos((i + 1) * angle), 0,
                              radius * sin((i + 1) * angle));
  tmp[0].normal = glm::vec3(0.0f, 1.0f, 0.0f);
  // 移动底部圆周的点，求出侧面三角形相关参数
  for (i = 0; i < num_stacks; i++, faces++) {
    tmp[1].position = tmp[2].position;
    tmp[2].position = glm::vec3(radius * cos((i + 2) * angle), 0, radius * sin((i + 2) * angle));
    glm::vec3 norm = -calNorm(tmp[1].position, tmp[2].position, tmp[0].position);
    tmp[0].normal = norm;
    tmp[1].normal = norm;
    tmp[2].normal = norm;
    coneVertices.push_back(tmp[0]);
    coneVertices.push_back(tmp[1]);
    coneVertices.push_back(tmp[2]);
    coneIndices.push_back(faces * 3 + 0);
    coneIndices.push_back(faces * 3 + 1);
    coneIndices.push_back(faces * 3 + 2);
  }
}
```

### 2.2 OBJ格式文件的读入与导出

OBJ文件读入：由于不要求解析mtl文件，因此只需要关注文件信息中的顶点数据，顶点索引以及网格信息。

```c++
// attrib_o用于记录顶点的数据
typedef struct
  {
    std::vector<float> vertices;
    std::vector<float> norms;
    std::vector<float> texts;
  } attrib_o;
```

```c++
// index_o用于记录顶点的索引信息
typedef struct
  {
    int v_index;
    int n_index;
    int t_index;
  } index_o;
```

```c++
// mesh_o用来记录网格信息
  typedef struct
  {
    std::vector<index_o> indices;
    std::vector<unsigned char> num_face_vertices;
  } mesh_o;
```

```c++
#include "obj_loader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace obj
{
  typedef struct
  {
    int p_index;
    int t_index;
    int n_index;
  } vertex;
  
  // 该函数将面转为网格
  bool exportFaceGroupToShape(shape_o &shape, const std::vector<std::vector<vertex>> &faces, const std::string &name, bool triangulate);

  bool LoadObj(attrib_o &_attrib, std::vector<shape_o> &shapes, std::string filePath, bool triangulate)
  {
    std::ifstream in(filePath, std::ios::in);
    if (!in.is_open())
      return false;
    bool eFlag = false;
    std::string name;
    std::string strLine;
    // 用于记录顶点数据
    std::vector<float> v;
    std::vector<float> vn;
    std::vector<float> vt;
    std::vector<vertex> vertices;
    std::vector<std::vector<vertex>> faces;
    // 读取数据
    while (getline(in, strLine))
    {
      std::istringstream ins(strLine);
      if (strLine.empty() || strLine[0] == '#')
        continue;
      if (strLine[0] == 'v')
      {
        // 读到vn说明是顶点法线数据
        if (strLine[1] == 'n')
        {
          // 记录相关数据 进入下次循环
          std::string x, y, z, vv;
          ins >> vv >> x >> y >> z;
          vn.push_back(std::stof(x));
          vn.push_back(std::stof(y));
          vn.push_back(std::stof(z));
          continue;
        }
        // 读到vn说明是顶点纹理数据
        else if (strLine[1] == 't')
        {
					// 记录相关数据
          // ...
        }
        else
        {
          // 记录相关数据
          // ...
        }
      }
      // 若读到f 要注意其格式 不同格式包含的数据种类不同
      else if (strLine[0] == 'f')
      {
        std::string ff;
        ins >> ff;
        std::vector<vertex> face;
        size_t pos1, pos2;
        std::string tmp1, tmp2;

        ins >> tmp1;
        pos1 = tmp1.find_first_of('/');
        tmp2 = tmp1.substr(pos1 + 1);
        pos2 = tmp2.find_first_of('/') + tmp1.length() - tmp2.length();
        // 双斜杠情况下不包含纹理信息
        if ((pos2 - pos1) == 1)
        {
          for (int i = 0;; i++)
          {
            size_t pos;
            vertex vert;
            std::string index_v, index_vn, str;
            if (i == 0)
              str = tmp1;
            else
            {
              if (ins >> str)
                ;
              else
                break;
            }
            pos = str.find_first_of('/');
            index_v = str.substr(0, pos);
            index_vn = str.substr(pos + 2);
            vert.p_index = std::stoi(index_v) - 1;
            vert.n_index = std::stoi(index_vn) - 1;
            face.push_back(vert);
          }
          faces.push_back(face);
          continue;
        }
        // 包含纹理信息
        else
        {
          // 数据读取
          // ...
        }
      }
      // 读到g将面转换为网格
      else if (strLine[0] == 'g')
      {
        shape_o shape;
        bool flag = exportFaceGroupToShape(shape, faces, name, triangulate);
        // 导出网格
        if (flag)
          shapes.push_back(shape);
        faces.clear();
        std::vector<std::string> names;
        names.reserve(2);
        std::string gg, name_str;
        ins >> gg >> name_str;
        name = name_str;
        continue;
      }
      // 其余情况不用处理
      else
      {
        continue;
      }
    }
    // 最后一次导出网格
    shape_o shape;
    bool flag = exportFaceGroupToShape(shape, faces, name, triangulate);
    if (flag)
      shapes.push_back(shape);
    faces.clear();
    _attrib.vertices.swap(v);
    _attrib.texts.swap(vt);
    _attrib.norms.swap(vn);
    return true;
  }

  bool exportFaceGroupToShape(shape_o &shape, const std::vector<std::vector<vertex>> &faces, const std::string &name, bool triangulate)
  {
    for (int i = 0; i < faces.size(); i++)
    {
      std::vector<vertex> face = faces[i];
      vertex v0 = face[0];
      vertex v1;
      vertex v2 = face[1];
      size_t n = face.size();
      // 三角面情况 只需记录三个点数据
      if (triangulate)
      {
        // 记录每点数据 导出网格
        // ...
      }
      // 多边形构成网格
      else
      {
        for (size_t k = 0; k < n; k++)
        {
          index_o iv;
          iv.v_index = face[k].p_index;
          iv.n_index = face[k].n_index;
          iv.t_index = face[k].t_index;
          shape.mesh.indices.push_back(iv);
        }
        shape.mesh.num_face_vertices.push_back(n);
      }
    }

    shape.name = name;
    return true;
  }
}
```

### 2.3 基本材质、纹理的显示和编辑能力

实现了基本材质、纹理的显示和编辑能力

仅节选部分代码

BlendShader

```c++
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

      "// spot light data structure declaration\n"
      "struct SpotLight {\n"
      "	vec3 position;\n"
      "	vec3 direction;\n"
      "	float intensity;\n"
      "	vec3 color;\n"
      "	float angle;\n"
      "	float kc;\n"
      "	float kl;\n"
      "	float kq;\n"
      "};\n"

      "struct AmbientLight {\n"
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
      "uniform AmbientLight ambientLight;\n"
      "uniform SpotLight spotLight;\n"

      "vec3 calcSpotLight(vec3 normal) {\n"
      "	vec3 lightDir = normalize(spotLight.position - fPosition);\n"
      "	float theta = acos(-dot(lightDir, normalize(spotLight.direction)));\n"
      "	if (theta > spotLight.angle) {\n"
      "		return vec3(0.0f, 0.0f, 0.0f);\n"
      "	}\n"
      "	vec3 diffuse = spotLight.color * max(dot(lightDir, normal), 0.0f) * (material.kds[0]+material.kds[1]);\n"
      "	float distance = length(spotLight.position - fPosition);\n"
      "	float attenuation = 1.0f / (spotLight.kc + spotLight.kl * distance + spotLight.kq * distance * distance);\n"
      "	return spotLight.intensity * attenuation * diffuse;\n"
      "}\n"

      "vec3 calcDirectionalLight(vec3 normal) {\n"
      "	vec3 lightDir = normalize(-light.direction);\n"
      "	vec3 diffuse = light.color * max(dot(lightDir, normal), 0.0f) * "
      "(material.kds[0]+material.kds[1]);\n"
      "	return light.intensity * diffuse ;\n"
      "}\n"

      "void main() {\n"
      "	vec3 normal = normalize(fNormal);\n"
      "	vec3 ambient = vec3(0.03f, 0.03f, 0.03f) * ambientLight.color * ambientLight.intensity;\n"
      "	vec3 spot = calcSpotLight(normal);\n"
      "	vec3 diffuse = calcDirectionalLight(normal);\n"
      //"	vec3 ambient = 0.08*light.color * light.intensity * "
      "(material.kds[0]+material.kds[1]);\n"
      "	color = mix(texture(mapKds[0], fTexCoord), texture(mapKds[1], "
      "fTexCoord), material.blend) * vec4(diffuse+ambient+spot, 1.0f);\n"
      "}\n";

  //----------------------------------------------------------------

  _blendShader.reset(new GLSLProgram);
  _blendShader->attachVertexShader(vsCode);
  _blendShader->attachFragmentShader(fsCode);
  _blendShader->link();
}
```

ui界面编辑材质和纹理

```c++
    ImGui::RadioButton("Show", (int*)&_renderMode,
      (int)(RenderMode::Show));
    ImGui::ColorEdit3("kd1", (float*)&_blendMaterial->kds[0]);
    ImGui::ColorEdit3("kd2", (float*)&_blendMaterial->kds[1]);
    ImGui::SliderFloat("blend", &_blendMaterial->blend, 0.0f, 1.0f);
    ImGui::NewLine();
```

### 2.4 基本几何变换功能

实现了模型的旋转平移缩放功能

按键R

```c++
  if (_keyboardInput.keyStates[GLFW_KEY_R] != GLFW_RELEASE)
  {
    _sphere->position += glm::vec3(0.0f, 0.03f, 0.0f);
  }
```

按键-

```c++
  if (_keyboardInput.keyStates[GLFW_KEY_MINUS] != GLFW_RELEASE)
  {
    _sphere->scale -= glm::vec3(0.03f, 0.03f, 0.03f);
    if (_sphere->scale.x < 0.03 || _sphere->scale.y < 0.03 ||
      _sphere->scale.z < 0.03)
      _sphere->scale = glm::vec3(0.03f, 0.03f, 0.03f);
  }
```


### 2.5 光照模型、基本光源编辑

directional light，ambient light，spot light
实现了光强、颜色、角度等编辑功能

仅节选部分代码

光源初始化

```c++
  // init light
  _light.reset(new DirectionalLight());
  _light->rotation =
    glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

  _spotLight.reset(new SpotLight());
  _spotLight->position = glm::vec3(0.0f, 0.0f, 5.0f);
  _spotLight->rotation = glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

  _ambientLight.reset(new AmbientLight);
```

ui界面编辑光源

```c++
    ImGui::Text("Directional Light");
    ImGui::Separator();
    ImGui::SliderFloat("intensity", &_light->intensity, 0.0f, 2.0f);
    ImGui::SliderFloat("xd", &xd, -2.0f, 2.0f);
    ImGui::SliderFloat("yd", &yd, -2.0f, 2.0f);
    ImGui::ColorEdit3("color", (float*)&_light->color);
    ImGui::NewLine();
```


### 2.6 摄像机漫游

实现了game模式的2.5维摄像机，show模式的三维摄像机，并实现了Zoom In/Out,Orbit,Zoom To Fit等功能

仅节选部分代码

按键A

```c++
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
```

鼠标移动

```c++
  if (cursorvisible % 2 == 0)
  {
    if (_mouseInput.move.xCurrent != _mouseInput.move.xOld)
    {
      double mouse_movement_in_x_direction =
        -(_mouseInput.move.xCurrent - _mouseInput.move.xOld);
      glm::vec3 right = glm::vec3(0.0f, 1.0f, 0.0f);
      double thetax = 0.003 * mouse_movement_in_x_direction;
      camera->rotation =
        glm::quat{ (float)cos(thetax / 2), (float)sin(thetax / 2) * right } *
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
        glm::quat{ (float)cos(thetay / 2), (float)sin(thetay / 2) * up } *
        camera->rotation;
      _mouseInput.move.yOld = _mouseInput.move.yCurrent;
    }
  }
```

鼠标滚轮

```c++
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
```

### 2.7 连续帧绘制

目的：将多个具有连续动作的obj文件连续绘制，实现动画效果。

原理：将多个obj文件预先导入某个容器，在每帧绘制时切换并循环绘制即可。

以下为连续帧绘制对象相关类

```c++
#ifndef FINAL_PROJECT_SRC_NPC_H_
#define FINAL_PROJECT_SRC_NPC_H_
#include "base/model.h"
#include <memory>
#include <string>
#include <vector>

// 使用智能指针存放每一个对象，用容器存储，调用函数即可实现连续帧绘制
class npc
{
public:
  npc();
  std::shared_ptr<Model> changeModel();
  ~npc() = default;

private:
  int count;
  int index;
  std::vector<std::shared_ptr<Model>> _npcVector;
};

#endif
```

```c++
npc::npc()
{
  index = 0;
  count = 0;
  for (int i = 0; i <= 100; i++)
  {
    std::string filePath = "../media/postures/pose";
    // count值不同时文件路径不同
    if (count < 10)
    {
      filePath += "00";
      filePath += std::to_string(count);
    }
    else if (count < 100)
    {
      filePath += "0";
      filePath += std::to_string(count);
    }
    else
    {
      filePath += std::to_string(count);
    }
    filePath += ".obj";
    // 利用智能指针存放每个npc单元，最终放入容器
    std::shared_ptr<Model> _npc;
    _npc.reset(new Model(filePath));
    _npc->scale = glm::vec3(0.01f, 0.01f, 0.01f);
    _npc->position = glm::vec3(-5, -5, -5);
    _npcVector.push_back(_npc);
    count++;
  }
}
```

每次渲染时调用changeModel函数即可实现连续帧绘制

```c++
std::shared_ptr<Model> npc::changeModel()
{
  std::shared_ptr<Model> curNPC = _npcVector[index];
  if (index < 100)
    index++;
  else
    index = 0;
  return curNPC;
}
```

### 2.8 空间碰撞检测

利用AABB包围盒和空间八叉树算法实现了空间碰撞检测。
#### 2.8.1 包围盒
基本AABB矩形包围盒部分，在model.boundingbox属性上进行添改，增加了包围盒顶点坐标变换（与模型一起进行空间坐标变换）
```c++
//在加载模型时使用计算函数进行包围盒计算
void Model::computeBoundingBox()
//在检测碰撞时，调用函数判断（摄像机的将来）位置是否在某模型的包围盒内
bool Model::checkBoundingBox(const glm::vec3& point) const
```
对于球，直接采用包围球，简单高效
```c++
bool Model::checkBoundingBall(const glm::vec3& point) const
```
对于摄像机，每次判断的时候将摄像机加上11倍前进方向的距离作为摄像机的将来位置，模拟摄像机包围盒
```c++
//以W键为例
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
```

#### 2.8.2 八叉树
八叉树主要由一个数据结构和三个函数组成。

注意，由于计算量较大，我们现在的程序中只对迷宫采取的八叉树划分，但其他任意模型都可以使用三个函数来简单引入八叉树碰撞模型（需要足够的顶点才能保证效果）。

分为三个步骤：

1. 首先给出一块空间长方体范围，对其进行八叉树空间划分
2. 将模型的所有顶点循环代入计算该点所在的最小八叉树叶节点，将该节点标记为会碰撞
3. 对于相机移动，将其移动的将来坐标带入整颗八叉树中，查找最小叶节点是否被标记碰撞，如果是，则返回会碰撞

```c++
//八叉树数据结构，xmin等六个数是当前八叉树的立方体包围盒，data储存了碰撞数据，1为发生碰撞，0为不碰撞(默认为0)
template <class T>
struct OctreeNode
{
  T data;
  T xmin, xmax;
  T ymin, ymax;
  T zmin, zmax;
  OctreeNode<T>* top_left_front, * top_left_back;
  OctreeNode<T>* top_right_front, * top_right_back;
  OctreeNode<T>* bottom_left_front, * bottom_left_back;
  OctreeNode<T>* bottom_right_front, * bottom_right_back;
}
//给出一个空间总包围盒，在其中生成八叉树
template <class T>
inline void createOctree(OctreeNode<T>*& root, int maxdepth, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
//给出一个点，计算其在包围盒中的位置，并将那个最小单位包围盒标记为发生碰撞(data=1)
template <class T>
  inline void compute(OctreeNode<T>*& p, double x, double y, double z);
//给出一个点，计算其是否会与整个八叉树中的点发生碰撞
template <class T>
  inline bool find(OctreeNode<T>*& p, double x, double y, double z);
```

### 2.9 完整三维游戏，具有可玩性

有碰撞检测的迷宫，第一人称逼真视角能看到自己的手，游戏遇到困难可以开挂，可以和模型互动，游戏失败有gameover弹窗提示

与熊互动

```c++
    if ((((_bear0->position.x - _camera->position.x) * (_bear0->position.x - _camera->position.x) + (_bear0->position.z - _camera->position.z) * (_bear0->position.z - _camera->position.z)) < 9.0)
        && (((_bear0->position.x - _camera->position.x) * (_bear0->position.x - _camera->position.x) + (_bear0->position.z - _camera->position.z) * (_bear0->position.z - _camera->position.z)) >= 1.0))
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
    if (((_bear0->position.x - _camera->position.x) * (_bear0->position.x - _camera->position.x) + (_bear0->position.z - _camera->position.z) * (_bear0->position.z - _camera->position.z)) <= 1.0) {
        _spotLight->position = _camera->position + glm::vec3(0.0f, 0.0f, 0.0f);
        _spotLight->rotation = glm::angleAxis(glm::radians(0.0f), -glm::vec3(1.0f, 1.0f, 1.0f));
        if (neng < 0.6) {
            neng += 0.001;
            _spotLight->angle = neng;
        }
        _spotLight->color = { 1.0f, 0.0f, 0.0f };
        _light->intensity = 0.0;

    }
    _blendShader->setMat4("model", _bear0->getModelMatrix());
    _bear0->draw();
```

开挂提示

```c++
if (hint == 1) {
  _bear1->position.x = _camera->position.x;
  _bear1->position.y = -14.0f;
  _bear1->position.z = _camera->position.z;

  _blendShader->setMat4("model", _bear1->getModelMatrix());
  _bear1->draw();
  hint = 0;
}
```

自己的手

```c++
_arml->rotation = _camera->rotation * glm::angleAxis(anglel, axis);
_armr->rotation = _camera->rotation * glm::angleAxis(angler, axis);
```

### 2.10 对象表达能力，能够表达门、墙等

关闭的门不可通行，可以按k键开门

```c++
if (_keyboardInput.keyStates[GLFW_KEY_K] != GLFW_RELEASE)
{
  knocky = true;
}
if (knocky == true && _keyboardInput.keyStates[GLFW_KEY_K] == GLFW_RELEASE)
{
  knock = !knock;
  knocky = false;
}
```

```c++
if (knock == true)
  _door->position = glm::vec3(2.0f, 2.0f, 2.0f);
else
  _door->position = glm::vec3(2.0f, 1.0f, 2.0f);
_blendShader->setMat4("model", _door->getModelMatrix());
_door->draw();
```

迷宫的墙始终不可通行:用碰撞检测实现

## 3 How to play

### 3.1 快捷键

- n：回到出生点
- m：回到终点
- r：球向上平移
- y：球向下平移
- f：球向左平移
- h：球向右平移
- t：球向上平移
- g：球向下平移
- -：球缩小
- =：球放大
- k：开/关门
- o：orbit
- b：摄像机焦距回到初始状态
- backspace：摄像机回到初始状态
- enter：显示/隐藏光标
- p：截图
- 鼠标滚轮：Zoom In/Out

### 3.2 游戏模式

- game模式：wasd控制第一人称2.5维相机，q：开挂，e不开挂

- show模式：wasdqe控制第一人称三维相机

### 3.3 音乐机制

- 背景音乐：受游戏模式控制，一直存在
- 游戏模式的兽吼心跳：受与熊的距离控制音量，远到一定程度就不发出声音

## 4 Code specification

- 采用visual studio c++代码规则

- 缩进：2空格
