
attribute vec2 parametric;

uniform vec3 lightPosition;  // Object-space
uniform vec3 eyePosition;    // Object-space
uniform vec2 torusInfo;

varying vec2 normalMapTexCoord;

varying vec3 lightDirection;
varying vec3 halfAngle;
varying vec3 eyeDirection;
varying vec3 c0, c1, c2;

void main()
{
  const float pi2 = 6.28318530;  // 2 times Pi

  float u = parametric[0];
  float v = parametric[1];
  float sin_u = sin(u*pi2);
  float cos_u = cos(u*pi2);
  float x = cos_u;
  float y = v;
  float z = -sin_u;
  float dxdu = -sin_u;
  float dydu = 0.0;
  float dzdu = -cos_u;

  vec3 T = vec3(dxdu, dydu, dzdu);
  vec3 T_ = vec3(0.0, 1.0, 0.0);
  vec3 N = cross(T, T_);
  vec3 B = cross(T, N);
  mat3 M = mat3(T, B, N);

  gl_Position = gl_ModelViewProjectionMatrix * vec4(x, y, z, 1);

  normalMapTexCoord = vec2(3.0*u, 1.0-v);

  lightDirection = (lightPosition - vec3(x,y,z)) * M;

  eyeDirection = vec3(0);  // XXX fix me
  halfAngle = vec3(0);  // XXX fix me
  c0 = vec3(0);  // XXX fix me
  c1 = vec3(0);  // XXX fix me
  c2 = vec3(0);  // XXX fix me
}

