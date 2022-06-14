#include <iostream>
#include <limits>
#include <unordered_map>

#include "obj_loader.h"

#include "model.h"

extern std::vector<float> ve, ne;
extern std::vector<float> te;
std::vector<glm::vec3> f_indices;
Model::Model(const std::string &filepath)
{
  obj::attrib_o attrib;
  std::vector<obj::shape_o> shapes;

  std::string err;

  std::string::size_type index = filepath.find_last_of("/");
  std::string mtlBaseDir = filepath.substr(0, index + 1);

  if (!obj::LoadObj(attrib, shapes, filepath.c_str()))
  {
    throw std::runtime_error("load " + filepath + " failure: " + err);
  }

  if (!err.empty())
  {
    std::cerr << err << std::endl;
  }

  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
  std::unordered_map<Vertex, uint32_t> uniqueVertices;

  for (const auto &shape : shapes)
  {
    for (const auto &index : shape.mesh.indices)
    {
      Vertex vertex{};

      vertex.position.x = attrib.vertices[3 * index.v_index + 0];
      vertex.position.y = attrib.vertices[3 * index.v_index + 1];
      vertex.position.z = attrib.vertices[3 * index.v_index + 2];

      // there is still a warning with visual studio windows 11 sdk called vector overflow
      if (index.t_index >= 0)
      {
        vertex.texCoord.x = attrib.vertices[2 * index.t_index + 0];
        vertex.texCoord.y = attrib.vertices[2 * index.t_index + 1];
      }

      if (index.n_index >= 0)
      {
        vertex.normal.x = attrib.norms[3 * index.n_index + 0];
        vertex.normal.y = attrib.norms[3 * index.n_index + 1];
        vertex.normal.z = attrib.norms[3 * index.n_index + 2];
      }

      // check if the vertex appeared before to reduce redundant data
      if (uniqueVertices.count(vertex) == 0)
      {
        uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
        vertices.push_back(vertex);
      }
      if (filepath == "../media/rock.obj")
      {
        f_indices.push_back(glm::vec3(index.v_index + 1, index.t_index + 1, index.n_index + 1));
      }
      indices.push_back(uniqueVertices[vertex]);
    }
    // f_indices.push_back(glm::vec3(-1, -1, -1));
  }

  _vertices = vertices;
  _indices = indices;

  computeBoundingBox();

  initGLResources();

  initBoxGLResources();

  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    cleanup();
    throw std::runtime_error("OpenGL Error: " + std::to_string(error));
  }
}

Model::Model(const std::vector<Vertex> &vertices,
             const std::vector<uint32_t> &indices)
    : _vertices(vertices), _indices(indices)
{

  computeBoundingBox();

  initGLResources();

  initBoxGLResources();

  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    cleanup();
    throw std::runtime_error("OpenGL Error: " + std::to_string(error));
  }
}

Model::Model(Model &&rhs) noexcept
    : _vertices(std::move(rhs._vertices)), _indices(std::move(rhs._indices)),
      _boundingBox(std::move(rhs._boundingBox)), _vao(rhs._vao), _vbo(rhs._vbo),
      _ebo(rhs._ebo), _boxVao(rhs._boxVao), _boxVbo(rhs._boxVbo),
      _boxEbo(rhs._boxEbo)
{
  _vao = 0;
  _vbo = 0;
  _ebo = 0;
  _boxVao = 0;
  _boxVbo = 0;
  _boxEbo = 0;
}

Model::~Model() { cleanup(); }

BoundingBox Model::getBoundingBox() const { return _boundingBox; }

void Model::draw() const
{
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indices.size()),
                 GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Model::drawBoundingBox() const
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBindVertexArray(_boxVao);
  glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

GLuint Model::getVao() const { return _vao; }

GLuint Model::getBoundingBoxVao() const { return _boxVao; }

size_t Model::getVertexCount() const { return _vertices.size(); }

size_t Model::getFaceCount() const { return _indices.size() / 3; }

void Model::initGLResources()
{
  // create a vertex array object
  glGenVertexArrays(1, &_vao);
  // create a vertex buffer object
  glGenBuffers(1, &_vbo);
  // create a element array buffer
  glGenBuffers(1, &_ebo);

  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(),
               _vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(uint32_t),
               _indices.data(), GL_STATIC_DRAW);

  // specify layout, size of a vertex, data type, normalize, sizeof vertex
  // array, offset of the attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, texCoord));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
}

void Model::computeBoundingBox()
{
  float minX = std::numeric_limits<float>::max();
  float minY = std::numeric_limits<float>::max();
  float minZ = std::numeric_limits<float>::max();
  float maxX = -std::numeric_limits<float>::max();
  float maxY = -std::numeric_limits<float>::max();
  float maxZ = -std::numeric_limits<float>::max();

  for (const auto &v : _vertices)
  {
    minX = std::min(v.position.x, minX);
    minY = std::min(v.position.y, minY);
    minZ = std::min(v.position.z, minZ);
    maxX = std::max(v.position.x, maxX);
    maxY = std::max(v.position.y, maxY);
    maxZ = std::max(v.position.z, maxZ);
  }

  _boundingBox.min = glm::vec3(minX, minY, minZ);
  _boundingBox.max = glm::vec3(maxX, maxY, maxZ);

  _boundingBox.min = glm::vec3((getModelMatrix() * glm::vec4(_boundingBox.min, 1.0f)).x, (getModelMatrix() * glm::vec4(_boundingBox.min, 1.0f)).y, (getModelMatrix() * glm::vec4(_boundingBox.min, 1.0f)).z);
  _boundingBox.max = glm::vec3((getModelMatrix() * glm::vec4(_boundingBox.max, 1.0f)).x, (getModelMatrix() * glm::vec4(_boundingBox.max, 1.0f)).y, (getModelMatrix() * glm::vec4(_boundingBox.max, 1.0f)).z);
}

void Model::initBoxGLResources()
{
  std::vector<glm::vec3> boxVertices = {
      glm::vec3(_boundingBox.min.x, _boundingBox.min.y, _boundingBox.min.z),
      glm::vec3(_boundingBox.max.x, _boundingBox.min.y, _boundingBox.min.z),
      glm::vec3(_boundingBox.min.x, _boundingBox.max.y, _boundingBox.min.z),
      glm::vec3(_boundingBox.max.x, _boundingBox.max.y, _boundingBox.min.z),
      glm::vec3(_boundingBox.min.x, _boundingBox.min.y, _boundingBox.max.z),
      glm::vec3(_boundingBox.max.x, _boundingBox.min.y, _boundingBox.max.z),
      glm::vec3(_boundingBox.min.x, _boundingBox.max.y, _boundingBox.max.z),
      glm::vec3(_boundingBox.max.x, _boundingBox.max.y, _boundingBox.max.z),
  };

  std::vector<uint32_t> boxIndices = {0, 1, 0, 2, 0, 4, 3, 1, 3, 2, 3, 7,
                                      5, 4, 5, 1, 5, 7, 6, 4, 6, 7, 6, 2};

  glGenVertexArrays(1, &_boxVao);
  glGenBuffers(1, &_boxVbo);
  glGenBuffers(1, &_boxEbo);

  glBindVertexArray(_boxVao);
  glBindBuffer(GL_ARRAY_BUFFER, _boxVbo);
  glBufferData(GL_ARRAY_BUFFER, boxVertices.size() * sizeof(glm::vec3),
               boxVertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _boxEbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxIndices.size() * sizeof(uint32_t),
               boxIndices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

void Model::cleanup()
{
  if (_boxEbo)
  {
    glDeleteBuffers(1, &_boxEbo);
    _boxEbo = 0;
  }

  if (_boxVbo)
  {
    glDeleteBuffers(1, &_boxVbo);
    _boxVbo = 0;
  }

  if (_boxVao)
  {
    glDeleteVertexArrays(1, &_boxVao);
    _boxVao = 0;
  }

  if (_ebo != 0)
  {
    glDeleteBuffers(1, &_ebo);
    _ebo = 0;
  }

  if (_vbo != 0)
  {
    glDeleteBuffers(1, &_vbo);
    _vbo = 0;
  }

  if (_vao != 0)
  {
    glDeleteVertexArrays(1, &_vao);
    _vao = 0;
  }
}

bool Model::checkBoundingBox(const glm::vec3 &point) const
{
  if (point.x < _boundingBox.min.x)
    return false;
  if (point.y < _boundingBox.min.y)
    return false;
  if (point.z < _boundingBox.min.z)
    return false;
  if (point.x > _boundingBox.max.x)
    return false;
  if (point.y > _boundingBox.max.y)
    return false;
  if (point.z > _boundingBox.max.z)
    return false;
  return true;
}

bool Model::checkBoundingBall(const glm::vec3 &point) const
{
  // sphereRadius = 5 * 2
  if (sqrt(pow((point.x - position.x), 2) + pow((point.y - position.y), 2) + pow((point.z - position.z), 2)) > 5)
    return false;
  else
    return true;
}

std::vector<Vertex> Model::getVertices()
{
  return _vertices;
}

std::vector<uint32_t> Model::getIndices()
{
  return _indices;
}

bool ExportObj(Model *inputModel)
{
  // std::vector<glm::vec3> position, normal;
  // std::vector<glm::vec2> textCoords;
  auto position = ve;
  auto normal = ne;
  auto textCoords = te;
  // for (auto vertex : inputModel->getVertices())
  // {
  //   position.push_back(vertex.position);
  //   normal.push_back(vertex.normal);
  //   textCoords.push_back(vertex.texCoord);
  // }
  std::ofstream fout("rock.obj");
  int count = 0;
  for (auto i : position)
  {
    if (count == 0)
    {
      fout << "v ";
    }
    fout << i;
    if (count == 2)
    {
      fout << std::endl;
      count = 0;
    }
    else
    {
      fout << " ";
      count++;
    }
  }
  count = 0;
  for (auto i : textCoords)
  {
    if (count == 0)
    {
      fout << "vt ";
    }
    fout << i;
    if (count == 1)
    {
      fout << std::endl;
      count = 0;
    }
    else
    {
      fout << " ";
      count++;
    }
  }
  count = 0;
  for (auto i : normal)
  {
    if (count == 0)
    {
      fout << "vn ";
    }
    fout << i;
    if (count == 2)
    {
      fout << std::endl;
      count = 0;
    }
    else
    {
      fout << " ";
      count++;
    }
  }

  // for (auto p : position)
  // {
  //   fout << "v ";
  //   fout << p.x << " " << p.y << " " << p.z << std::endl;
  // }
  // for (auto t : textCoords)
  // {
  //   fout << "vt ";
  //   fout << t.x << " " << t.y << std::endl;
  // }
  // for (auto n : normal)
  // {
  //   fout << "vn ";
  //   fout << n.x << " " << n.y << " " << n.z << std::endl;
  // }
  count = 0;
  int faces = 0;
  for (auto i : f_indices)
  {
    // if (i.x == -1)
    //   fout << "g _" + faces << std::endl;
    if (count == 0)
      fout << "f ";
    fout << i.x << "/" << i.y << "/" << i.z;
    if (count == 2)
    {
      fout << std::endl;
      count = 0;
      continue;
    }
    else
      fout << " ";
    count++;
  }
  return true;
}
void Model::computeInBoundingBox()
{
  tmaxdepth = cal(8);
  txm = (_boundingBox.max.x - _boundingBox.min.x) / tmaxdepth;
  tym = (_boundingBox.max.y - _boundingBox.min.y) / tmaxdepth;
  tzm = (_boundingBox.max.z - _boundingBox.min.z) / tmaxdepth;
  createOctree(rootNode, 8, _boundingBox.min.x, _boundingBox.max.x, _boundingBox.min.y, _boundingBox.max.y, _boundingBox.min.z, _boundingBox.max.z);
  for (const auto &v : _vertices)
  {
    glm::vec3 w = glm::vec3((getModelMatrix() * glm::vec4(v.position, 1.0f)).x, (getModelMatrix() * glm::vec4(v.position, 1.0f)).y, (getModelMatrix() * glm::vec4(v.position, 1.0f)).z);
    // std::cout << w.y << std::endl;
    compute(rootNode, w.x, w.y, w.z);
  }
}
bool Model::checkInBoundingBox(const glm::vec3 &point)
{
  if (find(rootNode, point.x, point.y, point.z))
    return true;
  return false;
}

void Model::changeBoundingBoxY(const int multiple)
{
  _boundingBox.max.y = _boundingBox.min.y + multiple * (_boundingBox.max.y - _boundingBox.min.y);
}

template <class T>
inline bool Model::find(OctreeNode<T> *&p, double x, double y, double z)
{
  double xm = (p->xmax - p->xmin) / 2;
  double ym = (p->ymax - p->ymin) / 2;
  double zm = (p->zmax - p->zmin) / 2;

  if (x > _boundingBox.max.x || x < _boundingBox.min.x || y > _boundingBox.max.y || y < _boundingBox.min.y || z > _boundingBox.max.z || z < _boundingBox.min.z)
  {
    return 0;
  }
  if (x <= p->xmin + txm && x >= p->xmax - txm && y <= p->ymin + tym && y >= p->ymax - tym && z <= p->zmin + tzm && z >= p->zmax - tzm)
  {
    // std::cout << "point " << x << " " << y << " " << z << std::endl;
    // std::cout << p->data << std::endl;
    return p->data;
  }
  else if (x <= (p->xmax - xm) && y <= (p->ymax - ym) && z <= (p->zmax - zm))
  {
    return find(p->bottom_left_back, x, y, z);
  }
  else if (x <= (p->xmax - xm) && y <= (p->ymax - ym) && z >= (p->zmax - zm))
  {
    return find(p->top_left_back, x, y, z);
  }
  else if (x >= (p->xmax - xm) && y <= (p->ymax - ym) && z <= (p->zmax - zm))
  {
    return find(p->bottom_right_back, x, y, z);
  }
  else if (x >= (p->xmax - xm) && y <= (p->ymax - ym) && z >= (p->zmax - zm))
  {
    return find(p->top_right_back, x, y, z);
  }
  else if (x <= (p->xmax - xm) && y >= (p->ymax - ym) && z <= (p->zmax - zm))
  {
    return find(p->bottom_left_front, x, y, z);
  }
  else if (x <= (p->xmax - xm) && y >= (p->ymax - ym) && z >= (p->zmax - zm))
  {
    return find(p->top_left_front, x, y, z);
  }
  else if (x >= (p->xmax - xm) && y >= (p->ymax - ym) && z <= (p->zmax - zm))
  {
    return find(p->bottom_right_front, x, y, z);
  }
  else if (x >= (p->xmax - xm) && y >= (p->ymax - ym) && z >= (p->zmax - zm))
  {
    return find(p->top_right_front, x, y, z);
  }
  else
    return 0;
}

template <class T>
inline void Model::compute(OctreeNode<T> *&p, double x, double y, double z)
{
  double xm = (p->xmax - p->xmin) / 2;
  double ym = (p->ymax - p->ymin) / 2;
  double zm = (p->zmax - p->zmin) / 2;

  if (x > _boundingBox.max.x || x < _boundingBox.min.x || y > _boundingBox.max.y || y < _boundingBox.min.y || z > _boundingBox.max.z || z < _boundingBox.min.z)
  {
    return;
  }
  if (x <= p->xmin + txm && x >= p->xmax - txm && y <= p->ymin + tym && y >= p->ymax - tym && z <= p->zmin + tzm && z >= p->zmax - tzm)
  {
    // std::cout << "create point " << x << " " << y << " " << z << std::endl;
    p->data = 1;
  }
  else if (x <= (p->xmax - xm) && y <= (p->ymax - ym) && z <= (p->zmax - zm))
  {
    compute(p->bottom_left_back, x, y, z);
  }
  else if (x <= (p->xmax - xm) && y <= (p->ymax - ym) && z >= (p->zmax - zm))
  {
    compute(p->top_left_back, x, y, z);
  }
  else if (x >= (p->xmax - xm) && y <= (p->ymax - ym) && z <= (p->zmax - zm))
  {
    compute(p->bottom_right_back, x, y, z);
  }
  else if (x >= (p->xmax - xm) && y <= (p->ymax - ym) && z >= (p->zmax - zm))
  {
    compute(p->top_right_back, x, y, z);
  }
  else if (x <= (p->xmax - xm) && y >= (p->ymax - ym) && z <= (p->zmax - zm))
  {
    compute(p->bottom_left_front, x, y, z);
  }
  else if (x <= (p->xmax - xm) && y >= (p->ymax - ym) && z >= (p->zmax - zm))
  {
    compute(p->top_left_front, x, y, z);
  }
  else if (x >= (p->xmax - xm) && y >= (p->ymax - ym) && z <= (p->zmax - zm))
  {
    compute(p->bottom_right_front, x, y, z);
  }
  else if (x >= (p->xmax - xm) && y >= (p->ymax - ym) && z >= (p->zmax - zm))
  {
    compute(p->top_right_front, x, y, z);
  }
}
