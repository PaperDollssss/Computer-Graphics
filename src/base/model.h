#pragma once

#include <string>
#include <vector>

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

    bool checkInBoundingBox(const glm::vec3 &point);

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
    inline bool find(OctreeNode<T> *&p, double x, double y, double z)
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
            return p->data;
        }
        else if (x < (p->xmax - xm) && y < (p->ymax - ym) && z < (p->zmax - zm))
        {
            return find(p->bottom_left_back, x, y, z);
        }
        else if (x < (p->xmax - xm) && y < (p->ymax - ym) && z > (p->zmax - zm))
        {
            return find(p->top_left_back, x, y, z);
        }
        else if (x > (p->xmax - xm) && y < (p->ymax - ym) && z < (p->zmax - zm))
        {
            return find(p->bottom_right_back, x, y, z);
        }
        else if (x > (p->xmax - xm) && y < (p->ymax - ym) && z > (p->zmax - zm))
        {
            return find(p->top_right_back, x, y, z);
        }
        else if (x < (p->xmax - xm) && y > (p->ymax - ym) && z < (p->zmax - zm))
        {
            return find(p->bottom_left_front, x, y, z);
        }
        else if (x < (p->xmax - xm) && y > (p->ymax - ym) && z > (p->zmax - zm))
        {
            return find(p->top_left_front, x, y, z);
        }
        else if (x > (p->xmax - xm) && y > (p->ymax - ym) && z < (p->zmax - zm))
        {
            return find(p->bottom_right_front, x, y, z);
        }
        else if (x > (p->xmax - xm) && y > (p->ymax - ym) && z > (p->zmax - zm))
        {
            return find(p->top_right_front, x, y, z);
        }
    }

    template <class T>
    inline void compute(OctreeNode<T> *&p, double x, double y, double z)
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
            p->data = 1;
        }
        else if (x < (p->xmax - xm) && y < (p->ymax - ym) && z < (p->zmax - zm))
        {
            compute(p->bottom_left_back, x, y, z);
        }
        else if (x < (p->xmax - xm) && y < (p->ymax - ym) && z > (p->zmax - zm))
        {
            compute(p->top_left_back, x, y, z);
        }
        else if (x > (p->xmax - xm) && y < (p->ymax - ym) && z < (p->zmax - zm))
        {
            compute(p->bottom_right_back, x, y, z);
        }
        else if (x > (p->xmax - xm) && y < (p->ymax - ym) && z > (p->zmax - zm))
        {
            compute(p->top_right_back, x, y, z);
        }
        else if (x < (p->xmax - xm) && y > (p->ymax - ym) && z < (p->zmax - zm))
        {
            compute(p->bottom_left_front, x, y, z);
        }
        else if (x < (p->xmax - xm) && y > (p->ymax - ym) && z > (p->zmax - zm))
        {
            compute(p->top_left_front, x, y, z);
        }
        else if (x > (p->xmax - xm) && y > (p->ymax - ym) && z < (p->zmax - zm))
        {
            compute(p->bottom_right_front, x, y, z);
        }
        else if (x > (p->xmax - xm) && y > (p->ymax - ym) && z > (p->zmax - zm))
        {
            compute(p->top_right_front, x, y, z);
        }
    }
};