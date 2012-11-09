#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <string>
#include <vector>
#include "src/core/vector.h"

class Material {
 public:
  Material();
  explicit Material(const std::string& name);

  void set_ambient(const ishi::Vector& ambient);
  void set_diffuse(const ishi::Vector& diffuse);
  void set_specular(const ishi::Vector& specular);
  void set_specular_coeff(const float& coeff);
  void set_texture(const std::string& texture);
  void LoadTexture(int texture_id);

  const std::string& name() const { return _name; }
  const ishi::Vector& ambient() const { return _ambient; }
  const ishi::Vector& diffuse() const { return _diffuse; }
  const ishi::Vector& specular() const { return _specular; }
  const float& specular_coeff() const { return _specular_coeff; }
  const std::string& texture() const { return _texture; }
  int texture_id() const { return _texture_id; }

 private:
  std::string _name;
  ishi::Vector _ambient;
  ishi::Vector _diffuse;
  ishi::Vector _specular;
  float _specular_coeff;
  std::string _texture;
  int _texture_id;
};

#endif
