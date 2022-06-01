//
// Created by 胡宇森 on 2022/5/30.
//
#ifndef FINAL_PROJECT_SRC_GENBASEELEMENTS_H_
#define FINAL_PROJECT_SRC_GENBASEELEMENTS_H_
#include <memory>
#include <string>

#include "base/application.h"
#include "base/camera.h"
#include "base/glsl_program.h"
#include "base/light.h"
#include "base/model.h"
#include "base/skybox.h"
#include "base/texture.h"

void genCube(std::vector<Vertex> &cubeVertices,
             std::vector<uint32_t> &cubeIndices);
void genCone(std::vector<Vertex> &coneVertices,
             std::vector<uint32_t> &coneIndices);
void genCylinder(std::vector<Vertex> &cylinderVertices,
                 std::vector<uint32_t> &cylinderIndices);
void genRoundTable(std::vector<Vertex> &roundtableVertices,
                   std::vector<uint32_t> &roundtableIndices);
void genCone(std::vector<Vertex> &coneVertices,
             std::vector<uint32_t> &coneIndices);
void genShpere(std::vector<Vertex> &sphereVertices,
               std::vector<uint32_t> &sphereIndices);
glm::vec3 calNorm(glm::vec3 a, glm::vec3 b, glm::vec3 c);

#endif // FINAL_PROJECT_SRC_GENBASEELEMENTS_H_
