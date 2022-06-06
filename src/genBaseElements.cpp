#define _USE_MATH_DEFINES
#include "texture_mapping.h"
glm::vec3 calNorm(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
  glm::vec3 norm = glm::cross((a - b), (a - c));
  return glm::normalize(norm);
}

void genCube(std::vector<Vertex> &cubeVertices,
             std::vector<uint32_t> &cubeIndices) {
  Vertex v[6];
  int faces = 0;
  const glm::vec3 p[8] = {
      glm::vec3(1.0f, 1.0f, -1.0f),   glm::vec3(1.0f, 1.0f, 1.0f),
      glm::vec3(-1.0f, 1.0f, -1.0f),  glm::vec3(-1.0f, 1.0f, 1.0f),
      glm::vec3(1.0f, -1.0f, -1.0f),  glm::vec3(1.0f, -1.0f, 1.0f),
      glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, -1.0f, 1.0f),
  };
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
  faces++;
  norm = glm::vec3(0.0f, 1.0f, 0.0f);
  v[0].position = p[0];
  v[1].position = p[1];
  v[2].position = p[2];
  v[3].position = p[1];
  v[4].position = p[2];
  v[5].position = p[3];
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
  faces++;
  norm = glm::vec3(1.0f, 0.0f, 0.0f);
  v[0].position = p[0];
  v[1].position = p[1];
  v[2].position = p[4];
  v[3].position = p[1];
  v[4].position = p[4];
  v[5].position = p[5];
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
  faces++;
  norm = glm::vec3(-1.0f, 0.0f, 0.0f);
  v[0].position = p[2];
  v[1].position = p[3];
  v[2].position = p[6];
  v[3].position = p[3];
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
  faces++;
  norm = glm::vec3(0.0f, 0.0f, -1.0f);
  v[0].position = p[6];
  v[1].position = p[2];
  v[2].position = p[4];
  v[3].position = p[2];
  v[4].position = p[4];
  v[5].position = p[0];
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
  faces++;
  norm = glm::vec3(0.0f, 0.0f, 1.0f);
  v[0].position = p[1];
  v[1].position = p[3];
  v[2].position = p[5];
  v[3].position = p[3];
  v[4].position = p[5];
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
}

void genCone(std::vector<Vertex> &coneVertices,
             std::vector<uint32_t> &coneIndices) {
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
  for (i = 0; i < num_stacks; i++, faces++) {
    tmp[1].position = tmp[2].position;
    tmp[2].position = glm::vec3(radius * cos((i + 2) * angle), 0,
                                radius * sin((i + 2) * angle));
    glm::vec3 norm =
        -calNorm(tmp[1].position, tmp[2].position, tmp[0].position);
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

void genCylinder(std::vector<Vertex> &cylinderVertices,
                 std::vector<uint32_t> &cylinderIndices) {
  int num_stacks = 400;
  double angle = 2 * M_PI / num_stacks;
  float radius = 3;
  float height = 5;
  int i = 0, faces = 0;
  Vertex tmp[3];
  tmp[0].position = glm::vec3(0.0f, 0.0f, 0.0f);
  tmp[1].position =
      glm::vec3(radius * cos(i * angle), 0, radius * sin(i * angle));
  tmp[2].position = glm::vec3(radius * cos((i + 1) * angle), 0,
                              radius * sin((i + 1) * angle));
  tmp[0].normal = glm::vec3(0.0f, -1.0f, 0.0f);
  tmp[1].normal = glm::vec3(0.0f, -1.0f, 0.0f);
  tmp[2].normal = glm::vec3(0.0f, -1.0f, 0.0f);
  for (i = 0; i < num_stacks; i++, faces++) {
    tmp[1].position = tmp[2].position;
    tmp[2].position = glm::vec3(radius * cos((i + 2) * angle), 0,
                                radius * sin((i + 2) * angle));
    cylinderVertices.push_back(tmp[0]);
    cylinderVertices.push_back(tmp[1]);
    cylinderVertices.push_back(tmp[2]);
    cylinderIndices.push_back(faces * 3 + 0);
    cylinderIndices.push_back(faces * 3 + 1);
    cylinderIndices.push_back(faces * 3 + 2);
  }
  tmp[0].position = glm::vec3(0.0f, height, 0.0f);
  tmp[1].position =
      glm::vec3(radius * cos(i * angle), height, radius * sin(i * angle));
  tmp[2].position = glm::vec3(radius * cos((i + 1) * angle), height,
                              radius * sin((i + 1) * angle));
  tmp[0].normal = glm::vec3(0.0f, 1.0f, 0.0f);
  tmp[1].normal = glm::vec3(0.0f, 1.0f, 0.0f);
  tmp[2].normal = glm::vec3(0.0f, 1.0f, 0.0f);
  for (i = 0; i < num_stacks; i++, faces++) {
    tmp[1].position = tmp[2].position;
    tmp[2].position = glm::vec3(radius * cos((i + 2) * angle), height,
                                radius * sin((i + 2) * angle));
    cylinderVertices.push_back(tmp[0]);
    cylinderVertices.push_back(tmp[1]);
    cylinderVertices.push_back(tmp[2]);
    cylinderIndices.push_back(faces * 3 + 0);
    cylinderIndices.push_back(faces * 3 + 1);
    cylinderIndices.push_back(faces * 3 + 2);
  }
  glm::vec3 norm;
  i = 0;
  tmp[0].position =
      glm::vec3(radius * cos(i * angle), 0, radius * sin(i * angle));
  tmp[1].position =
      glm::vec3(radius * cos(i * angle), height, radius * sin(i * angle));
  tmp[2].position = glm::vec3(radius * cos((i + 1) * angle), 0,
                              radius * sin((i + 1) * angle));
  for (i = 0; i < 2 * num_stacks; i++, faces++) {
    int index = i / 2;
    if (i % 2) {
      tmp[2].position = glm::vec3(radius * cos((index + 1) * angle), height,
                                  radius * sin((index + 1) * angle));
      norm = -calNorm(tmp[0].position, tmp[1].position, tmp[2].position);
    } else {
      tmp[2].position = glm::vec3(radius * cos((index + 2) * angle), 0,
                                  radius * sin((index + 2) * angle));
      norm = -calNorm(tmp[0].position, tmp[2].position, tmp[1].position);
    }
    tmp[0].normal = norm;
    tmp[1].normal = norm;
    tmp[2].normal = norm;
    cylinderVertices.push_back(tmp[0]);
    cylinderVertices.push_back(tmp[1]);
    cylinderVertices.push_back(tmp[2]);
    cylinderIndices.push_back(faces * 3 + 0);
    cylinderIndices.push_back(faces * 3 + 1);
    cylinderIndices.push_back(faces * 3 + 2);
    tmp[0].position = tmp[1].position;
    tmp[1].position = tmp[2].position;
  }
}

void genRoundTable(std::vector<Vertex> &roundtableVertices,
                   std::vector<uint32_t> &roundtableIndices) {
  int num_stacks = 400;
  double angle = 2 * M_PI / num_stacks;
  float inRadius = 3, outRadius = 5;
  float height = 5;
  int i = 0, faces = 0;
  Vertex tmp[3];
  tmp[0].position = glm::vec3(0.0f, 0.0f, 0.0f);
  tmp[1].position =
      glm::vec3(outRadius * cos(i * angle), 0, outRadius * sin(i * angle));
  tmp[2].position = glm::vec3(outRadius * cos((i + 1) * angle), 0,
                              outRadius * sin((i + 1) * angle));
  tmp[0].normal = glm::vec3(0.0f, -1.0f, 0.0f);
  tmp[1].normal = glm::vec3(0.0f, -1.0f, 0.0f);
  tmp[2].normal = glm::vec3(0.0f, -1.0f, 0.0f);
  for (i = 0; i < num_stacks; i++, faces++) {
    tmp[1].position = tmp[2].position;
    tmp[2].position = glm::vec3(outRadius * cos((i + 2) * angle), 0,
                                outRadius * sin((i + 2) * angle));
    roundtableVertices.push_back(tmp[0]);
    roundtableVertices.push_back(tmp[1]);
    roundtableVertices.push_back(tmp[2]);
    roundtableIndices.push_back(faces * 3 + 0);
    roundtableIndices.push_back(faces * 3 + 1);
    roundtableIndices.push_back(faces * 3 + 2);
  }
  tmp[0].position = glm::vec3(0.0f, height, 0.0f);
  tmp[1].position =
      glm::vec3(inRadius * cos(i * angle), height, inRadius * sin(i * angle));
  tmp[2].position = glm::vec3(inRadius * cos((i + 1) * angle), height,
                              inRadius * sin((i + 1) * angle));
  tmp[0].normal = glm::vec3(0.0f, 1.0f, 0.0f);
  tmp[1].normal = glm::vec3(0.0f, 1.0f, 0.0f);
  tmp[2].normal = glm::vec3(0.0f, 1.0f, 0.0f);
  for (i = 0; i < num_stacks; i++, faces++) {
    tmp[1].position = tmp[2].position;
    tmp[2].position = glm::vec3(inRadius * cos((i + 2) * angle), height,
                                inRadius * sin((i + 2) * angle));
    roundtableVertices.push_back(tmp[0]);
    roundtableVertices.push_back(tmp[1]);
    roundtableVertices.push_back(tmp[2]);
    roundtableIndices.push_back(faces * 3 + 0);
    roundtableIndices.push_back(faces * 3 + 1);
    roundtableIndices.push_back(faces * 3 + 2);
  }
  glm::vec3 norm;
  i = 0;
  tmp[0].position =
      glm::vec3(outRadius * cos(i * angle), 0, outRadius * sin(i * angle));
  tmp[1].position =
      glm::vec3(inRadius * cos(i * angle), height, inRadius * sin(i * angle));
  tmp[2].position = glm::vec3(outRadius * cos((i + 1) * angle), 0,
                              outRadius * sin((i + 1) * angle));
  for (i = 0; i < 2 * num_stacks; i++, faces++) {
    int index = i / 2;
    if (i % 2) {
      tmp[2].position = glm::vec3(inRadius * cos((index + 1) * angle), height,
                                  inRadius * sin((index + 1) * angle));
      norm = -calNorm(tmp[0].position, tmp[1].position, tmp[2].position);
    } else {
      tmp[2].position = glm::vec3(outRadius * cos((index + 2) * angle), 0,
                                  outRadius * sin((index + 2) * angle));
      norm = -calNorm(tmp[0].position, tmp[2].position, tmp[1].position);
    }
    tmp[0].normal = norm;
    tmp[1].normal = norm;
    tmp[2].normal = norm;
    roundtableVertices.push_back(tmp[0]);
    roundtableVertices.push_back(tmp[1]);
    roundtableVertices.push_back(tmp[2]);
    roundtableIndices.push_back(faces * 3 + 0);
    roundtableIndices.push_back(faces * 3 + 1);
    roundtableIndices.push_back(faces * 3 + 2);
    tmp[0].position = tmp[1].position;
    tmp[1].position = tmp[2].position;
  }
}

void genShpere(std::vector<Vertex> &sphereVertices,
               std::vector<uint32_t> &sphereIndices) {
  int outStack = 400;
  int inStack = 400;
  int sphereRadius = 5;
  double outangle = 0.5 * M_PI / outStack;
  double inangle = 2 * M_PI / inStack;
  Vertex tmp;
  for (int j = 0; j < outStack; j++) {
    float radius = cos(outangle * j) * sphereRadius;
    float off = radius / sphereRadius;
    for (int i = 0; i < inStack; i++) {
      tmp.position =
          glm::vec3(cos(inangle * i) * radius, -sin(inangle * i) * radius,
                    sin(outangle * j) * sphereRadius);
      tmp.normal = glm::vec3(cos(inangle * i) * off, -sin(inangle * i) * off,
                             sin(outangle * j));
      sphereVertices.push_back(tmp);
      if (i == 0) {
        sphereIndices.push_back(j * inStack);
        sphereIndices.push_back((j + 1) * inStack - 1);
        sphereIndices.push_back((j + 2) * inStack - 1);
        sphereIndices.push_back(j * inStack);
        sphereIndices.push_back((j + 1) * inStack);
        sphereIndices.push_back((j + 2) * inStack - 1);
      } else {
        sphereIndices.push_back(j * inStack + i);
        sphereIndices.push_back(j * inStack + i - 1);
        sphereIndices.push_back((j + 1) * inStack + i - 1);
        sphereIndices.push_back((j + 1) * inStack + i);
        sphereIndices.push_back((j + 1) * inStack + i - 1);
        sphereIndices.push_back(j * inStack + i);
      }
    }
  }
  for (int j = 0; j < outStack; j++) {
    float radius = cos(outangle * j) * sphereRadius;
    float off = radius / sphereRadius;
    for (int i = 0; i < inStack; i++) {
      tmp.position =
          glm::vec3(cos(inangle * i) * radius, -sin(inangle * i) * radius,
                    -sin(outangle * j) * sphereRadius);
      tmp.normal = glm::vec3(cos(inangle * i) * off, -sin(inangle * i) * off,
                             -sin(outangle * j));
      sphereVertices.push_back(tmp);
      if (i == 0) {
        sphereIndices.push_back((j + outStack) * inStack);
        sphereIndices.push_back((j + 1 + outStack) * inStack - 1);
        sphereIndices.push_back((j + 2 + outStack) * inStack - 1);
        sphereIndices.push_back((j + outStack) * inStack);
        sphereIndices.push_back((j + 1 + outStack) * inStack);
        sphereIndices.push_back((j + 2 + outStack) * inStack - 1);
      } else {
        sphereIndices.push_back((j + outStack) * inStack + i);
        sphereIndices.push_back((j + outStack) * inStack + i - 1);
        sphereIndices.push_back((j + 1 + outStack) * inStack + i - 1);
        sphereIndices.push_back((j + 1 + outStack) * inStack + i);
        sphereIndices.push_back((j + 1 + outStack) * inStack + i - 1);
        sphereIndices.push_back((j + outStack) * inStack + i);
      }
    }
  }
}

//
