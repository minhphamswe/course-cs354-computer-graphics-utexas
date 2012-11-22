
uniform vec4 LMa; // Light-Material ambient
uniform vec4 LMd; // Light-Material diffuse
uniform vec4 LMs; // Light-Material specular
uniform float shininess;

uniform sampler2D normalMap;
uniform sampler2D decal;
uniform sampler2D heightField;
uniform samplerCube envmap;

uniform mat3 objectToWorld;

varying vec2 normalMapTexCoord;
varying vec3 lightDirection;
varying vec3 eyeDirection;
varying vec3 halfAngle;
varying vec3 c0, c1, c2;

void main()
{
  // Get vectors from passed-in arguments
  vec3 Tu = c0;             // first surface tangent vector
  vec3 B = c1;              // surface binormal vector
  vec3 N = c2;              // surface normal vector

  // Reconstruct object to surface transformation
  mat3 M = mat3(Tu, B, N);

  // Extract perturbed normal vector
  vec3 n = vec3(texture2D(normalMap, normalMapTexCoord));

  // Expand perturbed normal vector to [-1, 1] from [0, 1]
  n = 2.0 * n - vec3(1.0);
  n.y = -n.y;               // invert the bump direction

  // Compute the reflection of eyeDirection off the surface
  vec3 r = reflect(-eyeDirection, n);

  // Convert the reflection vector to object and then world space
  r = M * r;
  r = objectToWorld * r;

  // Compute light direction and half-angle vectors
  vec3 l = normalize(lightDirection);
  vec3 h = normalize(halfAngle);

  // Lighting components
  vec4 specular = LMs * max(pow(dot(n, h), shininess), 0.0);
  vec4 diffuse  = LMd * max(dot(n, l), 0.0);
  vec4 ambient  = LMa;
  vec4 lighting = 0.5 * (specular + diffuse + ambient);

  // Final color
  gl_FragColor = lighting + 0.6 * textureCube(envmap, r);
}
