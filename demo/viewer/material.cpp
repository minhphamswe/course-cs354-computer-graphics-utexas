#include "./material.h"

#include <src/core/vector.h>
#include <string>
#include "./texture.h"

Material::Material()
    : _ambient(ishi::Vector(.1, .1, .1)),
      _diffuse(ishi::Vector(.3, .3, .3)),
      _specular(ishi::Vector(.1, .1, .1)), _specular_coeff(10),
      _texture_id(-1) {
}

Material::Material(const std::string& name)
    : _name(name),
      _ambient(ishi::Vector(.1, .1, .1)),
      _diffuse(ishi::Vector(.3, .3, .3)),
      _specular(ishi::Vector(.1, .1, .1)), _specular_coeff(10),
      _texture_id(-1) {
}

void Material::set_ambient(const ishi::Vector& ambient) {
  _ambient = ambient;
}
void Material::set_diffuse(const ishi::Vector& diffuse) {
  _diffuse = diffuse;
}
void Material::set_specular(const ishi::Vector& specular) {
  _specular = specular;
}
void Material::set_specular_coeff(const float& coeff) {
  _specular_coeff = coeff;
}
void Material::set_texture(const std::string& texture) {
  _texture = texture;
}

void Material::LoadTexture(int texture_id) {
  ::LoadTexture(texture(), texture_id);
  _texture_id = texture_id;
}
