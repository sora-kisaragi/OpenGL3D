/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


/// 2dベクトル型
struct Vector2
{
	float x, y;
};


/// 3Dベクトル型
struct Vector3
{
	float x, y, z;
};

/// RGBAカラー型
struct Color
{
	float r, g, b, a;
};

/// 頂点データ型 [Vertex = 頂点]
struct Vertex
{
	Vector3 position;///< 座標
	Color color;///< 色
	Vector2 texCoord;///< テクスチャ座標　Texture Coordinatesの略
};



/// 頂点データ
const Vertex vertices[] = {
	//木
	{ { 0.00f, 5.0f, 0.00f},{ 0.5f, 0.8f, 0.3f, 1.0f }, {0.0f,0.4f}},
	{ { 0.00f, 1.5f,-1.10f},{ 0.1f, 0.3f, 0.0f, 1.0f }, {0.0f,1.0f}},
	{ {-0.75f, 1.5f, 0.40f},{ 0.1f, 0.3f, 0.0f, 1.0f }, {-0.5f,0.0f}},
	{ { 0.75f, 1.5f, 0.40f},{ 0.1f, 0.3f, 0.0f, 1.0f }, {0.0f,0.0f}},
	{ { 0.00f, 4.0f, 0.00f},{ 0.2f, 0.1f, 0.0f, 1.0f }, {0.5f,0.1f}},
	{ { 0.00f, 0.0f,-0.37f},{ 0.5f, 0.3f, 0.2f, 1.0f }, {-0.5f,0.1f}},
	{ {-0.25f, 0.0f, 0.13f},{ 0.5f, 0.3f, 0.2f, 1.0f }, {-0.25f,0.0f}},
	{ { 0.25f, 0.0f, 0.13f},{ 0.5f, 0.3f, 0.2f, 1.0f }, {0.25f,0.0f}},

	//家

	{ { 2.8f, 0.0f, 3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 1.000f, 1.00f } },
	{ { 3.0f, 4.0f, 3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 1.000f, 0.31f } },
	{ { 0.0f, 6.0f, 3.0f},{ 0.5f, 0.4f, 0.2f, 1.0f },{ 0.875f, 0.00f } },
	{ {-3.0f, 4.0f, 3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.750f, 0.31f } },
	{ {-2.8f, 0.0f, 3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.750f, 1.00f } },
	
	{ {-2.8f, 0.0f,-3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.500f, 1.00f } },
	{ {-3.0f, 4.0f,-3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.500f, 0.31f } },
	{ { 0.0f, 6.0f,-3.0f},{ 0.5f, 0.4f, 0.2f, 1.0f },{ 0.375f, 0.00f } },
	{ { 3.0f, 4.0f,-3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.250f, 0.31f } },
	{ { 2.8f, 0.0f,-3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.250f, 1.00f } },
	
	{ { 2.8f, 0.0f, 3.0f},{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.000f, 1.00f } },
	{ { 3.0f, 4.0f, 3.0f},{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.000f, 0.31f } },
	{ { 0.0f, 6.0f, 3.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.750f, 0.00f } },
	{ { 0.0f, 6.0f,-3.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.500f, 0.00f } },
	{ { 0.0f, 6.0f,-3.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.250f, 0.00f } },
	{ { 0.0f, 6.0f, 3.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.000f, 0.00f } },

	//岩
	//底面
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//側面(前)
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//側面(右)
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//側面(左)
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//側面(後)
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	//上面
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },
	{ { 5.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f,1.0f } },


	//四角形
	{ { -0.5f, -0.3f, 0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ { 0.3f, -0.3f, 0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ { 0.3f,  0.5f, 0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
	{ { -0.5f,  0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },

	{ {-0.3f,  0.3f, 0.1f},{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ {-0.3f, -0.5f, 0.1f},{ 0.0f, 1.0f, 1.0f, 1.0f } },
	{ { 0.5f, -0.5f, 0.1f},{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ { 0.5f, -0.5f, 0.1f},{ 1.0f, 0.0f, 0.0f, 1.0f } },
	{ { 0.5f,  0.3f, 0.1f},{ 1.0f, 1.0f, 0.0f, 1.0f } },
	{ {-0.3f,  0.3f, 0.1f},{ 1.0f, 0.0f, 0.0f, 1.0f } },




	{ { -0.5f, -0.43f, 0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ { 0.5f, -0.43f, 0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ { 0.0f,  0.43f, 0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
};

// インデックスデータ
const GLushort indices[] = {
	//木
	0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 2, 3,
	4, 5, 6, 4, 6, 7, 4, 7, 5,

	//家
	0, 1, 3, 3, 4, 0, 1, 2, 3,
	5, 6, 8, 8, 9, 5, 6, 7, 8,
	9, 8, 11, 11, 10, 9,
	4, 3, 6, 6, 5, 4,
	3, 12, 13, 13, 6, 3,
	8, 14, 15, 15, 11, 8,


	//岩	



	0,1,2,2,3,0,
	4,5,6,7,8,9,
};

/*
*描画データ
*/
struct Mesh
{
	GLenum mode;			///< プリミティブの種類
	GLsizei count;			///< 描画するインデックス数
	const GLvoid* indices;	///< 描画開始インデックスのバイトオフセット
	GLint baseVertex;		///< インデックス0番とみなされる頂点配列内の位置
};

/*
*描画データリスト
*/
const Mesh meshList[] = {
	{GL_TRIANGLES, 21,(const GLvoid*)0,0 }, //木
	{GL_TRIANGLES,42,(const GLvoid*)(21 * sizeof(GLshort)),8},//家
};



/// 頂点シェーダー.
static const char* vsCode =
"#version 410 \n"
"layout(location=0) in vec3 vPosition; \n"
"layout(location=1) in vec4 vColor; \n"
"layout(location=2) in vec2 vTexCoord; \n"
"layout(location=0) out vec4 outColor;"
"layout(location=1) out vec2 outTexCoord; \n"
"uniform mat4x4 matMVP; \n"
"void main() { \n"
"  outColor = vColor; \n"
"  outTexCoord = vTexCoord; \n"
"  gl_Position = matMVP * vec4(vPosition, 1.0); \n"
"}";



/// フラグメントシェーダー.
static const char* fsCode =
"#version 410 \n"
"layout(location=0) in vec4 inColor; \n"
"layout(location=1) in vec2 inTexCoord; \n"
"uniform sampler2D texColor; \n"
"out vec4 fragColor; \n"
"void main() { \n"
"  fragColor = inColor * texture(texColor, inTexCoord); \n"
"}";







/**
* Vertex Buffer Objectを作成する.
*
* @param size 頂点データのサイズ.
* @param data 頂点データへのポインタ.
*
* GLsizeiptr = int
* GLvoid = void
*
* @return 作成したVBO.
*/
GLuint CreateVBO(GLsizeiptr size, const GLvoid* data)
{
	//unsigined int = GLuint
	GLuint vbo = 0;

	//メモリ領域を管理するオブジェクトを作成する関数
	//引数はバッファオブジェクトの個数と変数へのポインタ
	glGenBuffers(1, &vbo);

	//バッファオブジェクトを特定の用途に割り当てる
	//GL_ARRAY_BUFFER　は　頂点データを示す定数
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	/**バッファオブジェぅとにデータを転送する関数
	*   引数は
	* 1 転送先のバッファ用途
	* 2 転送バイト数
	* 3 転送するデータへのポインタ
	* 4 転送先のバッファにどのようにアクセスするかに関するヒントを渡す
	*
	*	GL_STATIC_DRAW	= アプリケーションから更新され、描画処理のソースとして使われる。
	*					  バッファは一度だけ転送され、何度も利用されます。
	*/
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	//0で割り当てを解除
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vboを返す
	return vbo;
}


/**
* Index Buffer Objectを作成する
*
* @param size インデックスデータのサイズ
* @param data インデックスデータへのポインタ
*
* GL_ELEMENT_ARRAY_BUFFERはインデックスデータを操作するためのマクロ
*
* @return 作成したIBO
*/
GLuint CreateIBO(GLsizeiptr size, const GLvoid* data)
{
	GLuint ibo = 0;

	//メモリ領域を管理するオブジェクトを作成する
	glGenBuffers(1, &ibo);

	//バッファオブジェクトを特定の用途に割り当てる
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	//バッファオブジェぅとにデータを転送する関数
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	//0で割り当てを解除
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//iboを返す
	return ibo;
}





/**
* Vertex Array Objectを作成する.
*
* @param vbo VAOに関連付けられるVBO.
* @param ibo VAOに関連付けられるIBO.
*
* @return 作成したVAO.
*/
GLuint CreateVAO(GLuint vbo, GLuint ibo)
{
	GLuint vao = 0;

	//vaoを作成する
	glGenVertexArrays(1, &vao);

	//指定されたVAOをOpenGLの 現在の処理対象 に設定する関数
	glBindVertexArray(vao);

	//頂点アトリビュートを設定するには事前に対応するVBOを割り当てる必要がある
	//vboをOpenGLに割り当てる
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//iboをOpenGLに割り当てる
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	//指定したバインディングポイントを有効にする
	//glDisableVertexAttribArrayで無効化にするまでは有効
	glEnableVertexAttribArray(0);

	/*
	*頂点アトリビュートをバインディングポインタに割り当てる関数
	*座標と色データ分のアトリビュートを作成し、それぞれを0,1番とする
	*引数は
	* 1 バインディングポイントのインデックス(0～15) | 2 情報の要素数 sizeofはクラスや構造体のバイト数を求めるC/C++の演算子
	* 3 情報の型 座標は3つのfloatなのでGL_FLOAT		| 4 情報を正規化するかどうか GL_FALSEならしない
	* 5 頂点データのバイト数 sizeofを使う			| 6 情報が頂点データの先頭から何バイト目にあるか を設定します C++の機能 offsetofマクロが重要 詳細はDocの2回
	*/
	glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, position)));
	
	//指定したバインディングポイントを割り当てる
	glEnableVertexAttribArray(1);

	//頂点アトリビュートをバインディングポインタへ割り当てる
	glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, color)));

	//指定したバインディングポイントを有効にする
	glEnableVertexAttribArray(2);

	//頂点アトリビュートをバインディングポインタへ割り当てる
	glVertexAttribPointer(2, sizeof(Vertex::texCoord) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, texCoord)));



	//0で割り当てを解除
	glBindVertexArray(0);

	//VBOを削除する　VAOに割り当てられている場合削除マークを付けて削除待機する
	glDeleteBuffers(1, &vbo);

	//IBOを削除する　IBOに割り当てられている場合削除マークを付けて削除待機する
	glDeleteBuffers(1, &ibo);

	return vao;

}








/**
* エントリーポート
*/
int main()
{
	//GLFW GLEWの初期化とウィンドウの作成
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	if (!window.Init(800, 600, "OpenGL3D")) {
		return 1;
	}

	//Shader.h
	//実装した関数を呼び出し、作成したオブジェクトを変数に格納
	const GLuint vbo = CreateVBO(sizeof(vertices), vertices);
	const GLuint ibo = CreateIBO(sizeof(indices), indices);
	const GLuint vao = CreateVAO(vbo, ibo);
	const GLuint shaderProgram = Shader::Build(vsCode, fsCode);

	//失敗したら1を返してプログラムを終了
	if (!vbo || !ibo || !vao || !shaderProgram) {
		return 1;
	}

	//uniform変数の位置を取得する
	const GLint matMVPLoc = glGetUniformLocation(shaderProgram, "matMVP");
	//見つからなかった場合
	if (matMVPLoc < 0) {
		//エラーを出す
		std::cerr << "ERROR: uniform変数'matMVP'が見つかりません.\n";
		//1を返す
		return 1;
	}

	glUseProgram(shaderProgram);
	const GLint texColorLoc = glGetUniformLocation(shaderProgram, "texColor");
	if (texColorLoc >= 0) {
		//1つのint型の値をuniform変数に設定する関数
		glUniform1i(texColorLoc, 0);
	}
	glUseProgram(0);


	//テクスチャを作成する
	const int tw = 8; //画像の幅
	const int th = 8; //画像の高さ
	const uint32_t B = 0xff'00'00'00; //黒
	const uint32_t W = 0xff'ff'ff'ff; //白
	const uint32_t imageData[tw * th] = {
		W, W, B, W, W, W, W, W,
		W, W, B, W, W, W, W, W,
		W, W, B, W, W, W, W, W,
		B, B, B, B, B, B, B, B,
		W, W, W, W, W, W, B, W,
		W, W, W, W, W, W, B, W,
		W, W, W, W, W, W, B, W,
		B, B, B, B, B, B, B, B,
	};
	//テクスチャを作成 それぞれに引数を設定するだけ
	GLuint texId = Texture::CreateImage2D(tw, th, imageData, GL_RGBA, GL_UNSIGNED_BYTE);
	GLuint texHouse = Texture::LoadImage2D("Res/House.tga");
	
	//作成に失敗した場合は1を返して終了
	if (!texId) {
		return 1;
	}








	//メインループ
	while (!window.ShouldClose()) {

		//glEnableは機能を有効にする関数
		//GL_DEPTH_TESTは　深度バッファによる奥行きの比較を示す
		glEnable(GL_DEPTH_TEST);


		//==========================課題2================================
		//カリングをオンにする
		glEnable(GL_CULL_FACE);

		//バックバッファを憑拠するときの色　RGBA
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);

		//バックバッファを消去する関数 引数は消去するバッファの種類
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	


		//視点を回転移動させる
		static float degree = 0.0f;
		//毎フレーム+0.0１°
		degree += 0.01f;
		//もし360°を越えたら360引くことで同じ角度にする
		if (degree >= 360.0f) { degree -= 360.0f; }
		//カメラのポジションを決める
		const glm::vec3 viewPos = glm::rotate(
			glm::mat4(1), glm::radians(degree), glm::vec3(0, 1, 0)) * glm::vec4(20, 20, 30, 1);


		

		//描画に使用するプログラムを設定
		glUseProgram(shaderProgram);


		//座標変換行列を作成してシェーダーに転送する
		//glm::perspective
		//透視投影を行う座標変換行列
		//近くにあるものほど大きく、遠くにあるものほど小さい事を表現
		const glm::mat4x4 matProj =
			glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
		
		//glm::lookAt
		//ワールド座標からビュー座標への変換行列
		//引数の順番
		//視点座標 注視点座標 視点の上方向のベクトル
		const glm::mat4x4 matView =
			glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));



		//ローカル座標からワールド座標への行列変換
		//mat4x4(1)で単位行列
		//translateは平行移動行列を作成する関数
		//最初の引数が合成先の行列 次が平行移動させる距離
		
		//3つの行列をかけ合わせて行列を合成
		/*
		*行列どうしの積を求める理由
		*行列の性質に
		*「行列の積を座標に掛けた結果は、積のもとになった２つの行列を順番に座標に掛けた場合と等しい」
		*他に 合成した行列なら行列と座標の席の計算は一回で済むために毎度計算するより早く軽い
		*/
		
		//シェーダーに変換行列を転送
		//引数
		//転送先のuniform変数の位置	転送するデータの数
		//行列をどう転置するかを指定	転送するデータへのポインタ
		//&vp[0][0]で行列の最初の要素へのポインタを渡している
		//現在設定されているプログラムオブジェクトに対して転送するため、glUseProgramの後に書く。

		//指定されたVAOをOpenGLの現在の処理対処に設定する

		////指定されたオブジェクトやデータを使って図形を描写

		//glDrawElements関数の兄弟のようなもの
		//追加の引数としてインデックスの０番とみなす頂点データの位置を設定することができる
		//頂点データが増減したときにここを変えるだけで良い



		


		//指定されたVAOをOpenGLの現在の処理対処に設定する
		glBindVertexArray(vao);

		//指定したテクスチャImageユニットをテクスチャ関数の処理対象として設定
		glActiveTexture(GL_TEXTURE0);

		//指定したテクスチャが選択されたテクスチャイメージユニットに割り当てられる
		glBindTexture(GL_TEXTURE_2D, texId);

		const float treeCount = 10;//木の本数
		const float radius = 8;		//木を植える円の半径

		//木の本数分作る
		for (float i = 0; i < treeCount; ++i) {
			//x座標
			const float x = std::cos(3.14f * 2 / treeCount * i) * radius;
			//y座標
			const float z = std::sin(3.14f * 2 / treeCount * i) * radius;
			//ローカル座標からワールド座標への行列変換
			const glm::mat4x4 matModel = glm::translate(glm::mat4(1), glm::vec3(x, 0, z));
			//3つの行列をかけ合わせて行列を合成
			const glm::mat4x4 matMVP = matProj * matView * matModel;
			//シェーダーに変換行列を転送
			glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
			//インデックスの0番とみなす頂点データの位置を設定
			glDrawElementsBaseVertex(meshList[0].mode, meshList[0].count,
				GL_UNSIGNED_SHORT, meshList[0].indices, meshList[0].baseVertex);
		}

		//家を作る

		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texHouse);

			//ローカル座標からワールド座標への行列変換
			const glm::mat4x4 matModel = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
			//3つの行列をかけ合わせて行列を合成
			const glm::mat4x4 matMVP = matProj * matView * matModel;
			//シェーダーに変換行列を転送
			glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
			//インデックスの0番とみなす頂点データの位置を設定
			glDrawElementsBaseVertex(meshList[1].mode, meshList[1].count,
				GL_UNSIGNED_SHORT, meshList[1].indices, meshList[1].baseVertex);
		}






		//glDrawElements 引数
		/**
		* 1 プリミティブの種類	|| 2 描画するインデックス数
		* 3 インデックスの型	|| 4 インデックスデータの描画オフセットを、インデックスデータの先頭データからのバイト数で指定
		*/


		//sizeof(配列名)/sizeof(配列名[0])の説明
		/*
		*	[補足] 「sizeof(配列名)/sizeof(配列名[0])」というのは
		*	C/C++で配列の大きさを取得する慣用的なプログラムです。
		*	ここでは直接書いていますが、一般的には
		*	#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
		*	のようなマクロを定義してそれを使います
		*/

		//割り当てを解除（デフォルトを割り当てる）
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);


		//バッファの切替
		window.SwapBuffers();
	}

	//あとから作られたオブジェクトを先に削除
	glDeleteTextures(1, &texHouse);
	glDeleteTextures(1, &texId);
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vao);

	//削除順番の補足
	/*
	*「作成したときとは逆の順番でオブジェクトを削除する」ことは、
	* プログラムを作成する上で一般的なルールです。
	* 依存関係の有無にかかわらず、このルールに従うことをお薦めします。
	*/

	return 0;
}