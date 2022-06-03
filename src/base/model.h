#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <glad/glad.h>

#include "vertex.h"
#include "object3d.h"
#include "bounding_box.h"

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

    bool checkBoundingBox(const glm::vec3 &point) const; // judge whether in the bounding box

    bool checkBoundingBall(const glm::vec3 &point) const; // judge whether in the bounding ball

    std::vector<Vertex> getVertices();

    std::vector<uint32_t> getIndices();

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
};

bool ExportObj(Model *inputModel);