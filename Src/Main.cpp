/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "Shader.h"
#include "Texture.h"
#include "Geometry.h"
#include "MeshList.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

/// 頂点シェーダ.
static const char* vsCode =
"#version 410 \n"
"layout(location=0) in vec3 vPosition; \n"
"layout(location=1) in vec4 vColor; \n"
"layout(location=2) in vec2 vTexCoord; \n"
"layout(location=0) out vec4 outColor; \n"
"layout(location=1) out vec2 outTexCoord; \n"
"uniform mat4x4 matMVP; \n"
"void main() { \n"
"  outColor = vColor; \n"
"  outTexCoord = vTexCoord; \n"
"  gl_Position = matMVP * vec4(vPosition, 1.0); \n"
"} \n";

/// フラグメントシェーダ.
static const char* fsCode =
"#version 410 \n"
"layout(location=0) in vec4 inColor; \n"
"layout(location=1) in vec2 inTexCoord; \n"
"out vec4 fragColor; \n"
"uniform sampler2D texColor; \n"
"void main() { \n"
"  fragColor = inColor * texture(texColor, inTexCoord); \n"
"} \n";

/// エントリーポイント.
int main()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	if (!window.Init(800, 600, "OpenGL Tutorial")) {
		return 1;
	}

	MeshList meshList;
	if (!meshList.Allocate()) {
		return 1;
	}

	const GLuint shaderProgram = Shader::BuildFromFile("Res/Simple.vert", "Res/Simple.frag");
	const GLuint fragmentLightingId = Shader::BuildFromFile("Res/FragmentLighting.vert", "Res/FragmentLighting.frag");
	if (!shaderProgram || !fragmentLightingId) {
		return 1;
	}
	Shader::Program progSimple(shaderProgram);
	Shader::Program progFragmentLighting(fragmentLightingId);

	// テクスチャを作成する.
	const int imageWidth = 8; // 画像の幅.
	const int imageHeight = 8; // 画像の高さ.
	const GLuint B = 0xff'40'40'40; // 黒.
	const GLuint W = 0xff'ff'ff'ff; // 白.
	const GLuint imageData[imageWidth * imageHeight] = {
		W, W, B, W, W, W, W, W,
		W, W, B, W, W, W, W, W,
		W, W, B, W, W, W, W, W,
		B, B, B, B, B, B, B, B,
		W, W, W, W, W, W, B, W,
		W, W, W, W, W, W, B, W,
		W, W, W, W, W, W, B, W,
		B, B, B, B, B, B, B, B,
	};
	const GLuint G2 = 0xff'10'80'20;
	const GLuint G1 = 0xff'20'C0'40;
	const GLuint G0 = 0xff'40'E0'80;
	const GLuint R0 = 0xff'20'60'A0;
	const GLuint R1 = 0xff'10'20'60;
	const GLuint imageTree[imageWidth * imageHeight] = {
		R0,R1,R0,R1,R0,R1,R0,R1,
		R0,R0,R0,R0,R0,R0,R0,R0,
		G2,G1,G2,G1,G2,G1,G2,G1,
		G1,G2,G1,G2,G1,G2,G1,G2,
		G1,G1,G2,G1,G1,G1,G2,G1,
		G0,G1,G0,G1,G0,G1,G0,G1,
		G1,G0,G1,G0,G1,G0,G1,G0,
		G0,G0,G0,G0,G0,G0,G0,G0,
	};
	GLuint texId = Texture::CreateImage2D(imageWidth, imageHeight, imageData, GL_RGBA, GL_UNSIGNED_BYTE);
	GLuint texTree = Texture::CreateImage2D(imageWidth, imageHeight, imageTree, GL_RGBA, GL_UNSIGNED_BYTE);
	GLuint texHouse = Texture::LoadImage2D("Res/House.tga");
	GLuint texRock = Texture::LoadImage2D("Res/Rock.tga");

	// ライトの設定.
	Shader::LightList lights;
	lights.ambient.color = glm::vec3(0.05f, 0.1f, 0.1f);
	lights.directional.direction = glm::normalize(glm::vec3(5, -2, -2));
	lights.directional.color = glm::vec3(1, 1, 1);
	lights.point.position[0] = glm::vec3(5, 4, 0);
	lights.point.color[0] = glm::vec3(1.0f, 0.8f, 0.4f) * 100.0f;
	lights.spot.posAndInnerCutOff[0] = glm::vec4(-6, 6, 8, std::cos(glm::radians(15.0f)));
	lights.spot.dirAndCutOff[0] = glm::vec4(glm::normalize(glm::vec3(-1, -2, -2)), std::cos(glm::radians(20.0f)));
	lights.spot.color[0] = glm::vec3(0.4f, 0.8f, 1.0f) * 200.0f;

	// メインループ.
	window.InitTimer();
	while (!window.ShouldClose()) {
		window.UpdateTimer();
		const float deltaTime = (float)window.DeltaTime();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 視点を設定する.
		const glm::vec3 viewPos(20, 30, 30);

		progFragmentLighting.Use();

		// 座標変換行列を作成する.
		const glm::mat4x4 matProj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
		const glm::mat4x4 matView = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		progFragmentLighting.SetViewProjectionMatrix(matProj * matView);

		// 光源を設定する.
		progFragmentLighting.SetLightList(lights);

		meshList.BindVertexArray();

		progFragmentLighting.BindTexture(0, texTree);

		const float treeCount = 10; // 木を植える本数.
		const float radius = 8; //　半径.
		for (float i = 0; i < treeCount; ++i) {
			const float theta = 3.14f * 2 / treeCount * i;
			const float x = std::cos(theta) * radius;
			const float z = std::sin(theta) * radius;
			progFragmentLighting.Draw(meshList[0], glm::vec3(x, 0, z), glm::vec3(0, theta * 5, 0), glm::vec3(1));
		}

		progFragmentLighting.BindTexture(0, texId);
		progFragmentLighting.Draw(meshList[3], glm::vec3(0), glm::vec3(0), glm::vec3(1));

		progFragmentLighting.BindTexture(0, texHouse);
		progFragmentLighting.Draw(meshList[1], glm::vec3(0), glm::vec3(0), glm::vec3(1));
		progFragmentLighting.Draw(meshList[1], glm::vec3(0, 0, 15), glm::vec3(0), glm::vec3(1));
		progFragmentLighting.Draw(meshList[1], glm::vec3(0, 0, -15), glm::vec3(0), glm::vec3(1));

		progFragmentLighting.BindTexture(0, texRock);
		progFragmentLighting.Draw(meshList[2], glm::vec3(4, 0, 0), glm::vec3(0), glm::vec3(1));

		progSimple.Use();
		progSimple.SetViewProjectionMatrix(matProj * matView);

		// ポイント・ライトの位置が分かるように適当なモデルを表示.
		{
			// 0番のポイント・ライトを移動する.
			const float speed = 10.0f * deltaTime;
			if (window.IsKeyPressed(GLFW_KEY_A)) {
				lights.point.position[0].x -= speed;
			}
			else if (window.IsKeyPressed(GLFW_KEY_D)) {
				lights.point.position[0].x += speed;
			}
			if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
				if (window.IsKeyPressed(GLFW_KEY_W)) {
					lights.point.position[0].y += speed;
				}
				else if (window.IsKeyPressed(GLFW_KEY_S)) {
					lights.point.position[0].y -= speed;
				}
			}
			else {
				if (window.IsKeyPressed(GLFW_KEY_W)) {
					lights.point.position[0].z -= speed;
				}
				else if (window.IsKeyPressed(GLFW_KEY_S)) {
					lights.point.position[0].z += speed;
				}
			}

			// モデルのY軸回転角を更新.
			static float pointLightAngle = 0;
			pointLightAngle += glm::radians(1.0f);
			if (pointLightAngle > glm::radians(360.0f)) {
				pointLightAngle -= glm::radians(360.0f);
			}

			// ポイント・ライトの位置が分かるように適当なモデルを表示.
			progSimple.BindTexture(0, texId);
			for (int i = 0; i < 8; ++i) {
				progSimple.Draw(meshList[0], lights.point.position[i], glm::vec3(0, pointLightAngle, 0), glm::vec3(1.0f, -0.25f, 1.0f));
			}
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		window.SwapBuffers();
	}

	glDeleteTextures(1, &texRock);
	glDeleteTextures(1, &texHouse);
	glDeleteTextures(1, &texTree);
	glDeleteTextures(1, &texId);

	return 0;
}
