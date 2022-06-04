#ifndef __OCTRESSNODE__
#define __OCTRESSNODE__

#include <iostream>

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

  OctreeNode(T nodeValue = T(),
    T xminValue = T(), T xmaxValue = T(),
    T yminValue = T(), T ymaxValue = T(),
    T zminValue = T(), T zmaxValue = T(),
    OctreeNode<T>* top_left_front_Node = NULL,
    OctreeNode<T>* top_left_back_Node = NULL,
    OctreeNode<T>* top_right_front_Node = NULL,
    OctreeNode<T>* top_right_back_Node = NULL,
    OctreeNode<T>* bottom_left_front_Node = NULL,
    OctreeNode<T>* bottom_left_back_Node = NULL,
    OctreeNode<T>* bottom_right_front_Node = NULL,
    OctreeNode<T>* bottom_right_back_Node = NULL)
    : data(nodeValue),
    xmin(xminValue), xmax(xmaxValue),
    ymin(yminValue), ymax(ymaxValue),
    zmin(zminValue), zmax(zmaxValue),
    top_left_front(top_left_front_Node),
    top_left_back(top_left_back_Node),
    top_right_front(top_right_front_Node),
    top_right_back(top_right_back_Node),
    bottom_left_front(bottom_left_front_Node),
    bottom_left_back(bottom_left_back_Node),
    bottom_right_front(bottom_right_front_Node),
    bottom_right_back(bottom_right_back_Node) {}
};

inline int cal(int num)
{
  int result = 1;
  if (1 == num)
    result = 1;
  else
  {
    for (int i = 1; i < num; i++)
      result = 2 * result;
  }
  return result;
}

template <class T>
inline void createOctree(OctreeNode<T>*& root, int maxdepth, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
  maxdepth = maxdepth - 1;
  if (maxdepth >= 0)
  {
    root = new OctreeNode<T>();
    root->data = 0;
    root->xmin = xmin;
    root->xmax = xmax;
    root->ymin = ymin;
    root->ymax = ymax;
    root->zmin = zmin;
    root->zmax = zmax;
    double xm = (xmax - xmin) / 2;
    double ym = (ymax - ymin) / 2;
    double zm = (zmax - zmin) / 2;
    createOctree(root->top_left_front, maxdepth, xmin, xmax - xm, ymax - ym, ymax, zmax - zm, zmax);
    createOctree(root->top_left_back, maxdepth, xmin, xmax - xm, ymin, ymax - ym, zmax - zm, zmax);
    createOctree(root->top_right_front, maxdepth, xmax - xm, xmax, ymax - ym, ymax, zmax - zm, zmax);
    createOctree(root->top_right_back, maxdepth, xmax - xm, xmax, ymin, ymax - ym, zmax - zm, zmax);
    createOctree(root->bottom_left_front, maxdepth, xmin, xmax - xm, ymax - ym, ymax, zmin, zmax - zm);
    createOctree(root->bottom_left_back, maxdepth, xmin, xmax - xm, ymin, ymax - ym, zmin, zmax - zm);
    createOctree(root->bottom_right_front, maxdepth, xmax - xm, xmax, ymax - ym, ymax, zmin, zmax - zm);
    createOctree(root->bottom_right_back, maxdepth, xmax - xm, xmax, ymin, ymax - ym, zmin, zmax - zm);
  }
}
#endif
