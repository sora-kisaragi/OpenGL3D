/**
* @file VertexLighting.vert
*/
#version 410

layout(location=0) in vec3 vPosition;
layout(location=1) in vec4 vColor;
layout(location=2) in vec2 vTexCoord;
layout(location=3) in vec3 vNormal;

layout(location=0) out vec4 outColor;
layout(location=1) out vec2 outTexCoord;

// 環境光.
struct AmbientLight
{
  vec3 color;
};

// 指向性ライト.
struct DirectionalLight
{
  vec3 direction;
  vec3 color;
};

// ポイントライト.
struct PointLight
{
  vec3 position[8];
  vec3 color[8];
};

uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform mat4x4 matMVP;

/**
* 頂点シェーダー.
*/
void main()
{
  float cosTheta = clamp(dot(vNormal, -directionalLight.direction), 0, 1);
  vec3 lightColor = directionalLight.color * cosTheta;

  for (int i = 0; i < 8; ++i) {
    if (dot(pointLight.color[i], pointLight.color[i]) != 0) {
      vec3 lightVector = (pointLight.position[i] - vPosition);
      float power = 1 / dot(lightVector, lightVector);
      cosTheta = clamp(dot(vNormal, normalize(lightVector)), 0, 1);
      lightColor += pointLight.color[i] * cosTheta * power;
	}
  }

  outColor.rgb = (vColor.rgb * lightColor);
  outColor.rgb += ambientLight.color;
  outColor.a = vColor.a;
  outTexCoord = vTexCoord;
  gl_Position = matMVP * vec4(vPosition, 1.0);
}
