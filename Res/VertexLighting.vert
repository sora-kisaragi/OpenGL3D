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

//����
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


uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;

uniform mat4x4 matMVP;

/**
* ���_�V�F�[�_�[.
*/
void main()
{
// �����o�[�g���˂ɂ��g�U���ˌ��̌v�Z.
	float cosTheta = clamp(dot(vNormal, -directionalLight.direction), 0.0, 1.0);
	outColor.rgb = (vColor.rgb * directionalLight.color * cosTheta);
	outColor.a = vColor.a;

	// �����̌v�Z.
	outColor.rgb += ambientLight.color;
	outColor.a = vColor.a;


	outTexCoord = vTexCoord;
	gl_Position = matMVP * vec4(vPosition, 1.0);
 }

