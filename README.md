# Computer-Graphics Final Project
## To Do

**最后记得讲注释里的英文全部删除，清理warning！**

**迷宫部分黄导加一下y轴限制吧，因为当下8层递归的情况下还是有可能穿过底座，但7层递归则会导致部分通道被空气墙堵塞，不刻意去按E键下潜的话玩迷宫没啥问题**

关于截图和音乐的Windows.h的问题，现在都被注释掉了，需要的采用如下方法开启

>

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
对于摄像机，每次判断的时候将摄像机加上11倍前进方向的距离作为摄像机的将来位置，模拟摄像机包围盒，如果检测碰撞，则回退摄像机位置（这部分之所以这么写是因为我当时想写模拟碰撞的屏幕震动效果）
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




## Way to Compile

```bash
cmake -Bbuild .
cd build
cmake --build . --parallel 8
```
## code specification
采用visual studio c++代码规则
缩进：2空格