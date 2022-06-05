//
// Created by 胡宇森 on 2022/5/21.
//
#include "obj_loader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::vector<float> ve, ne;
std::vector<float> te;

namespace obj
{
  typedef struct
  {
    int p_index;
    int t_index;
    int n_index;
  } vertex;

  bool exportFaceGroupToShape(shape_o &shape, const std::vector<std::vector<vertex>> &faces, const std::string &name, bool triangulate);

  bool LoadObj(attrib_o &_attrib, std::vector<shape_o> &shapes, std::string filePath, bool triangulate)
  {
    std::ifstream in(filePath, std::ios::in);
    if (!in.is_open())
      return false;
    bool eFlag = false;
    std::string name;
    std::string strLine;
    std::vector<float> v;
    std::vector<float> vn;
    std::vector<float> vt;
    std::vector<vertex> vertices;
    std::vector<std::vector<vertex>> faces;
    if (filePath == "../media/rock.obj")
      eFlag = true;
    while (getline(in, strLine))
    {
      std::istringstream ins(strLine);
      if (strLine.empty() || strLine[0] == '#')
        continue;
      if (strLine[0] == 'v')
      {
        if (strLine[1] == 'n')
        {
          std::string x, y, z, vv;
          ins >> vv >> x >> y >> z;
          vn.push_back(std::stof(x));
          vn.push_back(std::stof(y));
          vn.push_back(std::stof(z));
          if (eFlag)
          {
            ne.push_back(std::stof(x));
            ne.push_back(std::stof(y));
            ne.push_back(std::stof(z));
          }
          continue;
        }
        else if (strLine[1] == 't')
        {
          std::string x, y, vv;
          ins >> vv >> x >> y;
          vt.push_back(std::stof(x));
          vt.push_back(std::stof(y));
          if (eFlag)
          {
            te.push_back(std::stof(x));
            te.push_back(std::stof(y));
          }
          continue;
        }
        else
        {
          std::string x, y, z, vv;
          ins >> vv >> x >> y >> z;
          v.push_back(std::stof(x));
          v.push_back(std::stof(y));
          v.push_back(std::stof(z));
          if (eFlag)
          {
            ve.push_back(std::stof(x));
            ve.push_back(std::stof(y));
            ve.push_back(std::stof(z));
          }
          continue;
        }
      }
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
        else
        {
          for (int i = 0;; i++)
          {
            size_t pos1, pos2;
            vertex vert;
            std::string index_v, index_vt, index_vn, str, sub;
            if (i == 0)
              str = tmp1;
            else
            {
              if (ins >> str)
                ;
              else
                break;
            }

            pos1 = str.find_first_of('/');
            index_v = str.substr(0, pos1);
            sub = str.substr(pos1 + 1);
            pos2 = sub.find_first_of('/');
            index_vt = str.substr(pos1 + 1, pos2);
            index_vn = sub.substr(pos2 + 1);
            vert.p_index = std::stoi(index_v) - 1;
            vert.t_index = std::stoi(index_vt) - 1;
            vert.n_index = std::stoi(index_vn) - 1;
            face.push_back(vert);
          }
          faces.push_back(face);
          continue;
        }
      }
      else if (strLine[0] == 'g')
      {
        shape_o shape;
        bool flag = exportFaceGroupToShape(shape, faces, name, triangulate);
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
      else
      {
        continue;
      }
    }
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
      if (triangulate)
      {
        for (size_t k = 2; k < n; k++)
        {
          v1 = v2;
          v2 = face[k];

          index_o iv0, iv1, iv2;
          iv0.v_index = v0.p_index;
          iv0.n_index = v0.n_index;
          iv0.t_index = v0.t_index;
          iv1.v_index = v1.p_index;
          iv1.n_index = v1.n_index;
          iv1.t_index = v1.t_index;
          iv2.v_index = v2.p_index;
          iv2.n_index = v2.n_index;
          iv2.t_index = v2.t_index;

          shape.mesh.indices.push_back(iv0);
          shape.mesh.indices.push_back(iv1);
          shape.mesh.indices.push_back(iv2);

          shape.mesh.num_face_vertices.push_back(3);
        }
      }
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