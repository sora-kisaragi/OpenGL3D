/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "Shader.h"
#include <iostream>

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
};

/// 頂点データ
const Vertex vertices[] = {
	{ { -0.5f, -0.43f, 0.5f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ { 0.5f, -0.43f, 0.5f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ { 0.0f,  0.43f, 0.5f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
};


/// 頂点シェーダー.
static const char* vsCode =
"#version 410 \n"
"layout(location=0) in vec3 vPosition; \n"
"layout(location=1) in vec4 vColor; \n"
"layout(location=0) out vec4 outColor; \n"
"void main() { \n"
"  outColor = vColor; \n"
"  gl_Position = vec4(vPosition, 1.0); \n"
"}";



/// フラグメントシェーダー.
static const char* fsCode =
"#version 410 \n"
"layout(location=0) in vec4 inColor; \n"
"out vec4 fragColor; \n"
"void main() { \n"
"  fragColor = inColor; \n"
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
* Vertex Array Objectを作成する.
*
* @param vbo VAOに関連付けられるVBO.
*
* @return 作成したVAO.
*/
GLuint CreateVAO(GLuint vbo)
{
	GLuint vao = 0;
	
	//vaoを作成する
	glGenVertexArrays(1, &vao);

	//指定されたVAOをOpenGLの 現在の処理対象 に設定する関数
	glBindVertexArray(vao);

	//頂点アトリビュートを設定するには事前に対応するVBOを割り当てる必要がある
	//vboをOpenGLに割り当てる
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

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
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, color)));

	//0で割り当てを解除
	glBindVertexArray(0);

	//VBOを削除する　VAOに割り当てられている場合削除マークを付けて削除待機する
	glDeleteBuffers(1, &vbo);

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
	const GLuint vao = CreateVAO(vbo);
	const GLuint shaderProgram = Shader::Build(vsCode, fsCode);

	//失敗したら1を返してプログラムを終了
	if (!vbo || !vao || !shaderProgram) {
		return 1;
	}








	//メインループ
	while (!window.ShouldClose()) {


		//バックバッファを憑拠するときの色　RGBA
		glClearColor(.01f, 0.3f, 0.5f, 1.0f);
		
		//バックバッファを消去する関数 引数は消去するバッファの種類
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//描画に使用するプログラムを設定
		glUseProgram(shaderProgram);

		//指定されたVAOをOpenGLの現在の処理対処に設定する
		glBindVertexArray(vao);

		//指定されたオブジェクトやデータを使って図形を描写
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));

		//sizeof(配列名)/sizeof(配列名[0])の説明
		/*
		*	[補足] 「sizeof(配列名)/sizeof(配列名[0])」というのは
		*	C/C++で配列の大きさを取得する慣用的なプログラムです。
		*	ここでは直接書いていますが、一般的には
		*	#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
		*	のようなマクロを定義してそれを使います。
		*/



		//バッファの切替
		window.SwapBuffers();
	}

	//あとから作られたオブジェクトを先に削除
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