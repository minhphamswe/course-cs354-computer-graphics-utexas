#include "ray.h"
#include "material.h"
#include "light.h"

#include "../fileio/bitmap.h"
#include "../fileio/pngimage.h"

using namespace std;
extern bool debugMode;

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
Vec3d Material::shade(Scene *scene, const ray& r, const isect& i) const {
  // YOUR CODE HERE

  // For now, this method just returns the diffuse color of the object.
  // This gives a single matte color for every distinct surface in the
  // scene, and that's it.  Simple, but enough to get you started.
  // (It's also inconsistent with the phong model...)

  // Your mission is to fill in this method with the rest of the phong
  // shading model, including the contributions of all the light sources.
  // You will need to call both distanceAttenuation() and shadowAttenuation()
  // somewhere in your code in order to compute shadows and light falloff.
  if (debugMode)
    std::cout << "Debugging Phong code..." << std::endl;

  Vec3d I, H, V, N, L;
  Vec3d ambient, diffuse, specular, lighting;
  Vec3d sumLighting;

  ambient = ka(i) % scene->ambient();
  sumLighting = ke(i) + ambient;

  Vec3d isectPoint = r.at(i.t);
  for (vector<Light*>::const_iterator litr = scene->beginLights();
       litr != scene->endLights();
       ++litr) {
    Light* pLight = *litr;

    N = i.N;                                    // Normal vector
    I = pLight->getDirection(isectPoint);       // Incident vector
    V = -r.getDirection();                      // View vector
    H = I + V;                                  // Halfway vector
    H.normalize();

    // compute light color vector
    L = min(1.0, pLight->distanceAttenuation(isectPoint)) *
        (pLight->shadowAttenuation(isectPoint) %
        pLight->getColor(isectPoint));

    diffuse = max((N * I), 0.0) * (kd(i) % L);
    specular = pow(max((N * H), 0.0), shininess(i)) * (ks(i) % L);

    lighting = diffuse + specular;
    sumLighting += lighting;

    if (debugMode) {
//       std::cout << "N: " << N << "\t";
//       std::cout << "I: " << I << "\t";
//       std::cout << "H: " << H << "\t";
//       std::cout << "V: " << V << std::endl;
// 
//       std::cout << "Light: " << L << std::endl;
// 
//       std::cout << "kd: " << kd(i) << "\t";
//       std::cout << "(I * N): " << (I * N) << "\t";
//       std::cout << "(kd(i) % L): " << (kd(i) % L) << "\t";
//       std::cout << "diffuse: " << diffuse << std::endl;
// 
//       std::cout << "ks: " << ks(i) << "\t";
//       std::cout << "(N * H): " << (N * H) << "\t";
//       std::cout << "shininess: " << shininess(i) << "\t";

//       std::cout << "pow((N * H), shininess(i)): " << pow((N * H), shininess(i)) << "\t";
//       std::cout << "max(pow((N * H), shininess(i)), 0.0): " << max(pow((N * H), shininess(i)), 0.0) << std::endl;

//       std::cout << "(ks(i) % L): " << (ks(i) % L) << "\t";
//       std::cout << "specular: " << specular << std::endl;
// 
//       std::cout << "sumLighting: " << sumLighting << std::endl;
// 
//       std::cout << "ke(i): " << ke(i) << "\t";
//       std::cout << "kr(i): " << kr(i) << "\t";
//       std::cout << "kt(i): " << kt(i) << "\t";
//       std::cout << "index(i): " << index(i) << std::endl;
    }
  }

  sumLighting.clamp();

  if (debugMode) {
    std::cout << "ka: " << ka(i) << "\t";
    std::cout << "scene->ambient(): " << scene->ambient() << "\t";
    std::cout << "ambient: " << ambient << std::endl;

    std::cout << "sumLighting: " << sumLighting << std::endl;
  }
  return sumLighting;
}

TextureMap::TextureMap(string filename) {

  int start = filename.find_last_of('.');
  int end = filename.size() - 1;

  if (start >= 0 && start < end) {
    string ext = filename.substr(start, end);

    if (!ext.compare(".png")) {
      png_cleanup(1);

      if (!png_init(filename.c_str(), width, height)) {
        double gamma = 2.2;
        int channels, rowBytes;
        unsigned char* indata = png_get_image(gamma, channels, rowBytes);
        int bufsize = rowBytes * height;
        data = new unsigned char[bufsize];

        for (int j = 0; j < height; j++)
          for (int i = 0; i < rowBytes; i += channels)
            for (int k = 0; k < channels; k++)
              *(data + k + i + j * rowBytes) = *(indata + k + i + (height - j - 1) * rowBytes);

        png_cleanup(1);
      }
    } else
      if (!ext.compare(".bmp"))
        data = readBMP(filename.c_str(), width, height);
      else
        data = NULL;
  } else
    data = NULL;

  if (data == NULL) {
    width = 0;
    height = 0;
    string error("Unable to load texture map '");
    error.append(filename);
    error.append("'.");
    throw TextureMapException(error);
  }
}

Vec3d TextureMap::getMappedValue(const Vec2d& coord) const {
  // YOUR CODE HERE

  // In order to add texture mapping support to the
  // raytracer, you need to implement this function.
  // What this function should do is convert from
  // parametric space which is the unit square
  // [0, 1] x [0, 1] in 2-space to bitmap coordinates,
  // and use these to perform bilinear interpolation
  // of the values.



  return Vec3d(1.0, 1.0, 1.0);

}


Vec3d TextureMap::getPixelAt(int x, int y) const {
  // This keeps it from crashing if it can't load
  // the texture, but the person tries to render anyway.
  if (0 == data)
    return Vec3d(1.0, 1.0, 1.0);

  if (x >= width)
    x = width - 1;

  if (y >= height)
    y = height - 1;

  // Find the position in the big data array...
  int pos = (y * width + x) * 3;
  return Vec3d(double(data[pos]) / 255.0,
               double(data[pos + 1]) / 255.0,
               double(data[pos + 2]) / 255.0);
}

Vec3d MaterialParameter::value(const isect& is) const {
  if (0 != _textureMap)
    return _textureMap->getMappedValue(is.uvCoordinates);
  else
    return _value;
}

double MaterialParameter::intensityValue(const isect& is) const {
  if (0 != _textureMap) {
    Vec3d value(_textureMap->getMappedValue(is.uvCoordinates));
    return (0.299 * value[0]) + (0.587 * value[1]) + (0.114 * value[2]);
  } else
    return (0.299 * _value[0]) + (0.587 * _value[1]) + (0.114 * _value[2]);
}

