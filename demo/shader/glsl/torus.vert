
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

  float major_radius = torusInfo.x;
  float minor_radius = torusInfo.y;

  // Extract parametric coordinates
  float u = parametric[0];
  float v = parametric[1];
  float sin_u = sin(u*pi2);
  float cos_u = cos(u*pi2);
  float sin_v = sin(v*pi2);
  float cos_v = cos(v*pi2);

  // Compute torus vertex world coordinates from pametric coordinates
  float x = (major_radius + minor_radius * cos_v) * cos_u;
  float y = (major_radius + minor_radius * cos_v) * sin_u;
  float z = minor_radius * sin_v;

  // Compute gradient components in the u direction
  float dxdu = sin_u * (-(minor_radius * cos_v + major_radius));
  float dydu = cos_u * (minor_radius * cos_v + major_radius);
  float dzdu = 0.0;

  // Compute gradient components in the v direction
  float dxdv = -minor_radius * cos_u * sin_v;
  float dydv = -minor_radius * sin_u * sin_v;
  float dzdv = minor_radius * cos_v;

  // Compute object to surface transformation
  vec3 Tu = vec3(dxdu, dydu, dzdu);      // surface tangent vector
  vec3 Tv = vec3(dxdv, dydv, dzdv);     // another surface tangent vector
  vec3 N = cross(Tu, Tv);                // surface normal vector
  vec3 B = cross(Tu, N);                 // surface binormal vector
  mat3 M = mat3(Tu, B, N);               // object to surface transformation

  // Set vertex positions
  gl_Position = gl_ModelViewProjectionMatrix * vec4(x, y, z, 1);

  // Set texture mapping coordinates
  normalMapTexCoord = vec2(6.0*u, 2.0*v);

  // Compute light direction
  lightDirection = (lightPosition - vec3(x,y,z)) * M;

  eyeDirection = vec3(0);  // XXX fix me
  halfAngle = vec3(0);  // XXX fix me
  c0 = Tu;
  c1 = B;
  c2 = N;
}

