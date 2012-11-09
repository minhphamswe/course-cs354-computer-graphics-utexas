#include <src/core/point.h>
#include <src/core/vector.h>
#include <src/core/transform.h>
#include <src/shapes/trianglemesh.h>

#include <cstdio>
#include <iostream>
#include <vector>

#include "./mesh.h"

using namespace std;

Mesh::Mesh() {
  mesh = ishi::TriangleMesh();
  _cur_mtl = -1;
}

// This will be called by the obj parser
void Mesh::AddVertex(const ishi::Vector& v) {
  // TODO
  mesh.AddVertex(v[0], v[1], v[2]);

  // updates the bounding box
//   _bb(v);
}

// This will be called by the obj parser
void Mesh::AddTextureVertex(const ishi::Vector& v) {
  // TODO
//   printf("Texture Vertex: (%f, %f, %f)\n", v[0], v[1], v[2]);
}

// p is the list of indices of vertices for this polygon.  For example,
// if p = {0, 1, 2} then the polygon is a triangle with the zeroth, first and
// second vertices added using AddVertex.
//
// pt is the list of texture indices for this polygon, similar to the
// actual vertices described above.
void Mesh::AddPolygon(const std::vector<int>& p, const std::vector<int>& pt) {
  // TODO
//   printf("Texture Polygon Indices: (%d, %d, %d)\n", pt[0], pt[1], pt[2]);;
  mesh.AddPolygon(p);

  // updates the poly2mat map
  _polygon2material.push_back(_cur_mtl);
}

// Computes a normal for each vertex.
void Mesh::compute_normals() {
  // TODO don't forget to normalize your normals!
  mesh.ComputeNormal();
}
