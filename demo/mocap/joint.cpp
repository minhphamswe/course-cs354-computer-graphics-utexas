#include <src/core/vector.h>
#include <src/core/transform.h>

#include <GL/gl.h>

#include <stdint.h>
#include <iostream>
#include <vector>

#include "./bvh_defs.h"
#include "./joint.h"

using namespace std;
using namespace ishi;

/* Segment methods */

Segment::Segment(const char* name, uint32_t id) {
  /* Identification information */
  this->id = id;
  this->name = name;

  /* Hierarchy information */
  this->par = NULL;
  this->locTrans = Transform();
  this->accTrans = Transform();

  /* Geometric information */
  this->offset = Vector();
  this->endpoint = Point();
  this->basepoint = Point();

  /* Motion information */
  this->numChannels = 0;
}

void Segment::Update() {
  cout << "Updating " << name << " ID: " << id << endl;
//   cout << "Offset" << offset.x << offset.y << offset.z << endl;

  // Get accumulated transformation from the parent
  if (par) {
    accTrans = par->accTrans;
  }

  // Get local transformation from the frame
  vector<float> frame = frameData[frameIndex];

//   cout << "Frame for " << name << " is: " << "(";
//   for (unsigned int i = 0; i < frame.size(); i++)
//     cout << frame[i] << ", ";
//   cout << ")" << endl;

  for (unsigned int i = 0; i < numChannels; i++) {
    // get channel to update by order
    float f = frame[i];         // data
    int c = channelOrder[i];    // which channel it maps to
//     cout << "Channel Order: " << c << endl;

    locTrans = Transform();
    if (c == BVH_XPOS_IDX) {
      cout << "Translate along X by " << f << endl;
//       locTrans = Translate(Vector(f, 0, 0)) * locTrans;
      locTrans *= Translate(Vector(f, 0, 0));
//       this->basepoint = Translate(Vector(f, 0, 0))(this->basepoint);  // This is the base
//       this->basepoint = locTrans(this->basepoint);

    } else if (c == BVH_YPOS_IDX) {
      cout << "Translate along Y by " << f << endl;
      locTrans = Translate(Vector(0, f, 0)) * locTrans;

    } else if (c == BVH_ZPOS_IDX) {
      cout << "Translate along Z by " << f << endl;
      locTrans = Translate(Vector(0, 0, f)) * locTrans;

    } else if (c == BVH_XROT_IDX) {
//       cout << "Rotate around X by " << f << endl;
//       locTrans = RotateX(-f) * locTrans;
    } else if (c == BVH_YROT_IDX) {
//       cout << "Rotate around Y by " << f << endl;
//       locTrans = RotateY(-f) * locTrans;
    } else if (c == BVH_ZROT_IDX) {
//       cout << "Rotate around Z by " << f << endl;
//       locTrans = RotateZ(-f) * locTrans;
    }
  }

  // Update accumulated transformation
  accTrans = locTrans * accTrans;

  // Recompute base point
  if (par)
    this->basepoint = par->endpoint;
  else
    this->basepoint = locTrans(this->basepoint);  // This is the base
  cout << "Basepoint" << basepoint.x << basepoint.y << basepoint  .z << endl;

  // Recompute offset
  this->offset = locTrans(this->offset);

//   cout << "Offset" << offset.x << offset.y << offset.z << endl;

  // Recompute end point
//   if (par)
//     this->endpoint = par->endpoint + this->offset;
//   else
//     this->endpoint = Point(0, 0, 0) + this->offset;
  this->endpoint = this->basepoint + this->offset;
  
  // Apply transformation to geometric details
  //extent = locTrans(extent);
//   extent = accTrans(extent);   wrong
//   p = accTrans(p);
//   if (par) {
//     extent = p - par->p;
//   }
//   p = locTrans(Point());  wrong

  // Do the same for all children (order doesn't matter)
  for (unsigned int i = 0; i < chd.size(); i++) {
    chd[i]->frameIndex = frameIndex;
    chd[i]->Update();
  }
}

void Segment::DistributeFrame(float* data) {
  // Distribute to self first
  vector<float> frame;
  for (unsigned int i = 0; i < numChannels; i++) {
    frame.push_back(*data);
    data++;
  }
  frameData.push_back(frame);

  // Then distribute to the children (in order)
  for (unsigned int i = 0; i < chd.size(); i++) {
    chd[i]->DistributeFrame(data);
  }
}

void Segment::Render() {
  // Render self
//   cout << "Rendering " << name << endl;
//   Point pp = p + extent;
//   cout << "Drawing line from (" << p.x << "," << p.y << "," << p.z << ") to"
//   << "(" << pp.x << "," << pp.y << "," << pp.z << ")" << endl;
//   cout << "Extent is :" << "(" << extent.x << "," << extent.y << "," << extent.z << ")" << endl;

  float scale = 5.f;

  glColor3f(1.f, 0.f, 0.f);

//   cout << "This endpoint: " << this->endpoint.x << this->endpoint.y << this->endpoint.z << endl;

  glPointSize(10);
  glBegin(GL_POINTS);
    glVertex3f(this->endpoint.x * scale, this->endpoint.y * scale, this->endpoint.z * scale);
  glEnd();

//   glBegin(GL_LINES);

//     glVertex3f(endpoint.x * scale, endpoint.y * scale, endpoint.z * scale);
// //     if (par)
// //       glVertex3f(par->p.x * scale, par->p.y * scale, par->p.z * scale);
//     if (chd.size() > 0)
//       glVertex3f(chd[0]->endpoint.x * scale, chd[0]->endpoint.y * scale, chd[0]->endpoint.z * scale);
//     else
//       glVertex3f(endpoint.x * scale, endpoint.y * scale, endpoint.z * scale);
// //     glVertex3f(pp.x * scale, pp.y * scale, pp.z * scale);
//   glEnd();

  // Then render all children
  for (unsigned int i = 0; i < chd.size(); i++) {
    chd[i]->Render();
  }
}


/* SceneGraph Methods */
void SceneGraph::CreateRoot(const char * name, uint32_t id) {
//   cout << "createRoot:name=" << name << " id=" << id << endl;
  // Allocate new scene node
  nodes.insert(nodes.begin() + id, new Segment(name, id));
  roots.push_back(nodes[id]);
}

void SceneGraph::CreateJoint(const char * name, uint32_t id) {
//   cout << "createJoint:name=" << name << " id=" << id << endl;
  // Allocate new scene node
  nodes.insert(nodes.begin() + id, new Segment(name, id));
}

void SceneGraph::CreateEndSite(const char * name, uint32_t id) {
//   cout << "createEndSite:name=" << name << " id=" << id;
  // Allocate new scene node
  nodes.insert(nodes.begin() + id, new Segment(name, id));
}

void SceneGraph::SetChild(uint32_t parent, uint32_t child) {
  cout << "setChild:parent=" << parent << " child=" << child << endl;
  nodes[child]->par = nodes[parent];
  nodes[parent]->chd.push_back(nodes[child]);
//   nodes[parent]->extent = nodes[child]->p - nodes[parent]->p;
}

void SceneGraph::SetOffset(uint32_t id, float * offset) {
  cout << "setOffset:id=" << id << " offset=(" << offset[0] << ","
  << offset[1] << "," << offset[2] << ")" << endl;

//   if (nodes[id]->par)
//     nodes[id]->p = nodes[id]->par->p;
  nodes[id]->offset = Vector(offset[0], offset[1], offset[2]);
//   nodes[id]->locTrans = Translate(nodes[id]->offset);
}

void SceneGraph::SetNumChannels(uint32_t id, uint16_t num) {
//   cout << "setNumChannels:id=" << id << " num=" << num << endl;
  nodes[id]->numChannels = num;
}

void SceneGraph::SetChannelFlags(uint32_t id, uint16_t flags) {
//   cout << "setChannelFlags:id=" << id << " flags=" << flags << endl;
  nodes[id]->channelFlags = flags;
}

void SceneGraph::SetChannelOrder(uint32_t id, int * order) {
//   cout  << "setChannelOrder:id=" << id << " order: "
//   << order[0] << order[1] << order[2] << endl;
  for (unsigned int i = 0; i < nodes[id]->numChannels; i++) {
    nodes[id]->channelOrder.push_back(*order);
    order++;
  }
//   cout << "Node channel order: "
//   << nodes[id]->channelOrder[0] << nodes[id]->channelOrder[1] << nodes[id]->channelOrder[2] << endl;
}

void SceneGraph::SetFrameIndex(uint32_t id, uint32_t index) {
//   cout << "setFrameIndex:id=" << id << " index=" << index << endl;
  nodes[id]->frameIndex = index;
}

void SceneGraph::SetFrameTime(float delta) {
//   cout << "setFrameTime:delta=" << delta << endl;
  frameTime = delta;
}

void SceneGraph::SetNumFrames(uint32_t num) {
//   cout << "setNumFrames:num=" << num << endl;
  numFrames = num;
}

void SceneGraph::SetFrameSize(uint32_t size) {
//   cout << "setFrameSize:size=" << size << endl;
  frameSize = size;
}

void SceneGraph::AddFrame(float * data) {
//   cout << "addFrame" << endl;
  // Distribute frame data to all nodes, starting at the root
  for (unsigned int i = 0; i < roots.size(); i++) {
    roots[i]->DistributeFrame(data);
  }
}

void SceneGraph::SetCurrentFrame(uint32_t frameNumber) {
  cout << "setCurrentFrame:frameNumber=" << frameNumber << endl;
  this->currentFrame = frameNumber;
  // Increment frame number for all children and request update
  for (unsigned int i = 0; i < roots.size(); i++) {
    roots[i]->frameIndex = frameNumber;
    roots[i]->Update();
  }
}

float SceneGraph::GetFrameTime() {
  return frameTime;
}


uint32_t SceneGraph::GetCurrentFrame() {
  return currentFrame;
}
