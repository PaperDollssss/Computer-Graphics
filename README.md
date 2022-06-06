# Computer-Graphics Final Project

## Way to Compile

```bash
cmake -Bbuild .
cd build
cmake --build . --parallel 8
```

## code specification

采用visual studio c++代码规则

缩进：2空格

## To Do

**最后记得讲注释里的英文全部删除，清理warning！**

> bug汇总与解决：
>
> - 爬墙问题已解决并简化代码
>
> - MSVC绘制纹理向量越界问题：仍在debuging，如需操作纹理，推荐使用g++
>
> - ../和../../的问题：使用vs调试器和mac gcc都可直接运行。windows下直接打开exe仍需修改（不建议这么做）
>
> - windows.h的问题：已解决，现在的情况就是，windows下可以使用截屏和添加音乐两个函数，且已经截屏函数已经添加。mac请直接无视这部分，就当不能截屏和插入音乐。
>
>   截屏生成的图片保存在exe同目录（直接运行exe）/工程同目录（使用vs调试器）音乐函数已经实现了重复调用样例（覆盖），按N键实现（同时传送到起点）
>
>
> ```c++
> #if _WIN32
> SaveScreenShot(_windowWidth, _windowHeight);
> #endif
> 
> #if _WIN32
> void PlayMusic(music_path);
> #endif
> //请使用上面的方式而非直接调用该函数
> ```

### 0.1 总体要求
**40 total**

简单室内场景三维建模及真实感绘制

第一次验收（展示）时间：最后一次课，6月7日，**演示大程、代码模块、回答问题（对照源码介绍实现方法）**

第二次验收时间：6月18日或19日之前，**仅演示最后的大程，可放弃**

提交截止时间：6月20日，**提交：源代码、报告文档、可执行程序+相关数据资源**

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



## Introduction
### 1.1
### 1.2 Module introduction

## Module implementation

### 基本体素建模表达

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

### OBJ格式文件的读入与导出

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

### 连续帧绘制

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





### 碰撞检测
简单写一下包围盒与八叉树实现碰撞检测的部分原理
#### 包围盒
基本AABB矩形包围盒部分，在助教给出的model.boundingbox属性上进行添改，增加了包围盒顶点坐标变换（与模型一起进行空间坐标变换）
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
  cameraPos = cameraMoveSpeed * _camera->getFront();
  _camera->position += cameraPos;
  if (checkBounding(_camera->position + 10.0f * cameraPos))
    _camera->position -= cameraPos;
}
```

#### 八叉树
八叉树主要由一个数据结构和三个函数组成
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

## 玩法相关

### 快捷键
### 按键介绍

n：回到出生点
m：回到终点
