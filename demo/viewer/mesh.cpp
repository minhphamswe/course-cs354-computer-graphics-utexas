#include <src/core/point.h>
#include <src/core/vector.h>
#include <src/core/transform.h>
#include <src/core/imaterial.h>
#include <src/shapes/trianglemesh.h>

#include <cstdio>
#include <iostream>
#include <vector>

#include "./mesh.h"

using namespace std;

Mesh::Mesh() {
  _cur_mtl = -1;
  o2w = ishi::Transform();
  w2o = ishi::Transform();
  mesh.push_back(ishi::TriangleMesh(&o2w, &w2o));
}

// This will be called by the obj parser
void Mesh::AddVertex(const ishi::Vector& v) {
  // TODO
  mesh[0].AddVertex(v[0], v[1], v[2]);

  // updates the bounding box
//   _bb(v);
}

// This will be called by the obj parser
void Mesh::AddTextureVertex(const ishi::Vector& v) {
  // TODO
//   printf("Texture Vertex: (%f, %f, %f)\n", v[0], v[1], v[2]);
  mesh[0].AddTextureVertex(v[0], v[1], v[2]);
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
  mesh[0].AddPolygon(p);
  mesh[0].AddPolygonTexture(pt);

  // updates the poly2mat map
  _polygon2material.push_back(_cur_mtl);
}

// Computes a normal for each vertex.
void Mesh::compute_normals() {
  // TODO don't forget to normalize your normals!
  mesh[0].ComputeNormal();

  for (int i = 0; i < _materials.size(); i++) {
    mesh[0].AddMaterial(ishi::Texture(_materials[i].ambient(),
                                   _materials[i].diffuse(),
                                   _materials[i].specular(),
                                   _materials[i].specular_coeff()));
//     printf("Material is: %s\n", _materials[i].name().c_str());
//     printf("Ambient is: %f %f %f\n", _materials[i].ambient().x, _materials[i].ambient().y, _materials[i].ambient().z);
//     printf("Diffusion is: %f %f %f\n", _materials[i].diffuse().x, _materials[i].diffuse().y, _materials[i].diffuse().z);
//     printf("Specular is: %f %f %f\n", _materials[i].specular().x, _materials[i].specular().y, _materials[i].specular().z);
  }

  mesh[0].LoadMaterialMapping(_polygon2material);
//   for (int i = 0; i < _polygon2material.size(); i++)
//     printf("Polygon to material is: %d\n", _polygon2material[i]);
}
