#include <src/core/common.h>
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
  this->w2o = Transform();
  this->loc = Transform();

  /* Geometric information */
  this->offset = Vector();
  this->endpoint = Point();   // in world coordinate
  this->basepoint = Point();  // in world coordinate

  /* Motion information */
  this->numChannels = 0;
}

void Segment::Update() {
  cout << "Updating " << name << " ID: " << id << endl;

  // Recompute world-to-object transformation
  if (par) {
    this->w2o = Translate(this->offset) * par->w2o;
  }

//   cout << "Basepoint" << basepoint.x << basepoint.y << basepoint.z << endl;

  // Get local transformation from the frame
  vector<float> frame = frameData[frameIndex];

  Vector trans = Vector(0, 0, 0);   // Translation vector
  Vector rot = Vector(0, 0, 0);     // Rotation data holder

  for (unsigned int i = 0; i < numChannels; i++) {
    // get channel to update by order
    float f = frame[i];         // data
    int c = channelOrder[i];    // which channel it maps to

    if (c == BVH_XPOS_IDX && (channelFlags & BVH_XPOS)) {
      cout << "Move to point X equals " << f << endl;
      trans.x = f;

    } else if (c == BVH_YPOS_IDX && (channelFlags & BVH_YPOS)) {
      cout << "Move to point X equals " << f << endl;
      trans.y = f;

    } else if (c == BVH_ZPOS_IDX && (channelFlags & BVH_ZPOS)) {
      cout << "Move to point X equals " << f << endl;
      trans.z = f;

    } else if (c == BVH_XROT_IDX) {
      cout << "Rotate around X by " << f << endl;
      rot.x = Radian(-f);

    } else if (c == BVH_YROT_IDX) {
      cout << "Rotate around Y by " << f << endl;
      rot.y = Radian(-f);

    } else if (c == BVH_ZROT_IDX) {
      cout << "Rotate around Z by " << f << endl;
      rot.z = Radian(-f);
    }
  }

  if (trans != Vector(0, 0, 0))
    this->w2o = Translate(trans) * this->w2o * Translate(Point() - basepoint);

  if (rot != Vector(0, 0, 0))
    this->loc = RotateX(rot.x) * RotateX(rot.y) * RotateZ(rot.z);

  // Recompute basepoint, offset
  this->basepoint = this->w2o(Point());
  this->offset = this->loc(this->offset);
//   this->offset = Length(this->offset) * Normalize(rot);
  this->endpoint = Translate(this->offset)(this->basepoint);

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
    glVertex3f(this->basepoint.x * scale, this->basepoint.y * scale, this->basepoint.z * scale);
  glEnd();

//   glBegin(GL_LINES);
//     glVertex3f(basepoint.x * scale, basepoint.y * scale, basepoint.z * scale);
//     glVertex3f(endpoint.x * scale, endpoint.y * scale, endpoint.z * scale);
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
}

void SceneGraph::SetOffset(uint32_t id, float * offset) {
  cout << "setOffset:id=" << id << " offset=(" << offset[0] << ","
  << offset[1] << "," << offset[2] << ")" << endl;

  nodes[id]->offset = Vector(offset[0], offset[1], offset[2]);
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

uint32_t SceneGraph::GetNumFrames() {
  return numFrames;
}


uint32_t SceneGraph::GetCurrentFrame() {
  return currentFrame;
}
