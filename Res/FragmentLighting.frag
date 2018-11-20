/**
* @file FragmentLighting.frag
*/
#version 410

layout(location=0) in vec3 inPosition;
layout(location=1) in vec4 inColor;
layout(location=2) in vec2 inTexCoord;
layout(location=3) in vec3 inNormal;

out vec4 fragColor;

// ����.
struct AmbientLight
{
  vec3 color;
};

// �w�������C�g.
struct DirectionalLight
{
  vec3 direction;
  vec3 color;
};

// �|�C���g���C�g.
struct PointLight
{
  vec3 position[8];
  vec3 color[8];
};

// �X�|�b�g���C�g
struct SpotLight
{
  vec4 dirAndCutOff[4];
  vec4 posAndInnerCutOff[4];
  vec3 color[4];
};

uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform sampler2D texColor;

/**
* �t���O�����g�V�F�[�_�[.
*/
void main()
{
  vec3 normal = normalize(inNormal);

  // �w�������C�g�̖��邳���v�Z����.
  float cosTheta = clamp(dot(normal, -directionalLight.direction), 0.0, 1.0);
  vec3 lightColor = directionalLight.color * cosTheta;

  // �|�C���g���C�g�̖��邳���v�Z����.
  for (int i = 0; i < 8; ++i) {
    if (dot(pointLight.color[i], pointLight.color[i]) != 0) {
      // �t���O�����g���烉�C�g�֌������x�N�g�����v�Z.
      vec3 lightVector = pointLight.position[i] - inPosition;
      vec3 lightDir = normalize(lightVector);
      // �ʂ̌X���ɂ�閾�邳�̕ω��ʂ��v�Z.
      float cosTheta = clamp(dot(normal, lightDir), 0.0, 1.0);
      // �����ɂ�閾�邳�̕ω��ʂ��v�Z.
      float intensity = 1.0 / (1.0 + dot(lightVector, lightVector));
      // �ω��ʂ��������킹�Ė��邳�����߁A���v�ɉ��Z.
      lightColor += pointLight.color[i] * cosTheta * intensity;
    }
  }

  // �X�|�b�g���C�g�̖��邳���v�Z����.
  for (int i = 0; i < 4; ++i) {
    if (dot(spotLight.color[i], spotLight.color[i]) != 0) {
      // �t���O�����g���烉�C�g�֌������x�N�g�����v�Z.
      vec3 lightVector = spotLight.posAndInnerCutOff[i].xyz - inPosition;
      vec3 lightDir = normalize(lightVector);
      // �ʂ̌X���ɂ�閾�邳�̕ω��ʂ��v�Z.
      float cosTheta = clamp(dot(normal, lightDir), 0.0, 1.0);
      // �����ɂ�閾�邳�̕ω��ʂ��v�Z.
      float intensity = 1.0 / (1.0 + dot(lightVector, lightVector));
      // ���ˊp�ɂ�閾�邳�̕ω��ʂ��v�Z.
      float spotCosTheta = dot(lightDir, -spotLight.dirAndCutOff[i].xyz);
      float cutOff = smoothstep(spotLight.dirAndCutOff[i].w, spotLight.posAndInnerCutOff[i].w, spotCosTheta);
      // �ω��ʂ��������킹�Ė��邳�����߁A���v�ɉ��Z.
      lightColor += spotLight.color[i] * cosTheta * intensity * cutOff;
    }
  }

  fragColor = inColor * texture(texColor, inTexCoord);
  fragColor.rgb *= lightColor;
  fragColor.rgb += ambientLight.color;
}
