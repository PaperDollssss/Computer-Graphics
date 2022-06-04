#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <glad/glad.h>

#include "vertex.h"
#include "object3d.h"
#include "bounding_box.h"
#include "otctree.h"

class Model : public Object3D
{
public:
  Model(const std::string &filepath);

  Model(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);

  Model(Model &&rhs) noexcept;

  virtual ~Model();

  GLuint getVao() const;

  GLuint getBoundingBoxVao() const;

  size_t getVertexCount() const;

  size_t getFaceCount() const;

  BoundingBox getBoundingBox() const;

  void computeBoundingBox();

  void computeInBoundingBox();

  bool checkBoundingBox(const glm::vec3 &point) const; // judge whether in the bounding box

  bool checkBoundingBall(const glm::vec3 &point) const; // judge whether in the bounding ball

  std::vector<Vertex> getVertices();

  std::vector<uint32_t> getIndices();
  bool checkInBoundingBox(const glm::vec3 &point);

  void changeBoundingBoxY(const int multiple);

  virtual void draw() const;

  virtual void drawBoundingBox() const;

protected:
  // vertices of the table represented in model's own coordinate
  std::vector<Vertex> _vertices;
  std::vector<uint32_t> _indices;

  // bounding box
  BoundingBox _boundingBox;

  // opengl objects
  GLuint _vao = 0;
  GLuint _vbo = 0;
  GLuint _ebo = 0;

  GLuint _boxVao = 0;
  GLuint _boxVbo = 0;
  GLuint _boxEbo = 0;

  void initGLResources();

  void initBoxGLResources();

  void cleanup();

  OctreeNode<double> *rootNode = NULL;

  int tmaxdepth = 0;
  double txm = 0;
  double tym = 0;
  double tzm = 0;

  template <class T>
  inline bool find(OctreeNode<T> *&p, double x, double y, double z);

  template <class T>
  inline void compute(OctreeNode<T> *&p, double x, double y, double z);
};

bool ExportObj(Model* inputModel);