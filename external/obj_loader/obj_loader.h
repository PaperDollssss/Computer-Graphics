//
// Created by 胡宇森 on 2022/5/21.
//

#ifndef CG_PROJECTS_EXTERNAL_OBJ_LOADER_OBJ_LOADER_H_
#define CG_PROJECTS_EXTERNAL_OBJ_LOADER_OBJ_LOADER_H_

#include <map>
#include <string>
#include <vector>

namespace obj {
typedef struct {
  std::vector<float> vertices;
  std::vector<float> norms;
  std::vector<float> texts;
} attrib_o;

typedef struct {
  int v_index;
  int n_index;
  int t_index;
} index_o;

typedef struct {
  std::vector<index_o> indices;
  std::vector<unsigned char> num_face_vertices;
} mesh_o;

typedef struct {
  std::string name;
  mesh_o mesh;
} shape_o;

bool LoadObj(attrib_o &_attrib, std::vector<shape_o> &shapes,
             std::string filePath, bool triangulate = true);
} // namespace obj
#endif // CG_PROJECTS_EXTERNAL_OBJ_LOADER_OBJ_LOADER_H_
