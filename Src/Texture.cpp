/**
* @file Texture.cpp
*/
#include "Texture.h"
#include <iostream>

/// テクスチャ関連の関数やクラスを格納する名前空間
namespace Texture {


	/**
	* 2Dテクスチャを作成する.
	*
	* @param width   テクスチャの幅(ピクセル数).
	* @param height  テクスチャの高さ(ピクセル数).
	* @param data    テクスチャデータへのポインタ.
	*
	* @retval 0以外  作成したテクスチャ・オブジェクトのID.
	* @retval 0      テクスチャの作成に失敗.
	*/
	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data)
	{
		GLuint id;
		
		//テクスチャの作成
		//引数
		//作成する数
		//オブジェクトのIDが格納される変数へのポインタ
		glGenTextures(1, &id);

		//操作用のバインディングポイントに割り当てる
		//割当先のバインディングポイント
		//割り当てるオブジェクトのID 0の場合実質割当解除
		glBindTexture(GL_TEXTURE_2D, id);

		//GPUへテクスチャのパラメータと画像データを転送
		/**
		*	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* date);
		*	target	転送先になるバインディングポイント
		*	level	設定するミニマップレベル　ミニマップとはオブジェクトとカメラの距離に応じて大きさの違うテクスチャを使い分ける機能
		*	internalFormat	画像がどの様にGPUメモリに保存されるかを指定
		*	width	テクスチャの幅をピクセルで指定
		*	height	テクスチャの高さをピクセルで指定
		*	border	常に０を指定（OpenGL3.0以降は使用禁止）
		*	format	転送元の画像のデータ形式を指定する GL_RGBAなどがよくつかわれる
		*	type	転送元夫のがぞ図がどのように色を格納しているかを指定する
		*	data	転送元データへのポインタ nullptrで後から書き込んで使用する場合に使える（何が書かれているかわからない状態）
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		//テクスチャ作成の成功失敗を取得
		const GLenum result = glGetError();

		//もし失敗していたら
		if (result != GL_NO_ERROR) {
			//エラーを表示
			std::cerr << "ERROR: テクスチャの作成に失敗(0x" << std::hex << result << ").";
			//Bindを解除
			glBindTexture(GL_TEXTURE_2D, 0);
			//オブジェクトを削除 引数はglGettexturesと同じ
			glDeleteTextures(1, &id);

			return 0;

		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



		//Bindを解除
		glBindTexture(GL_TEXTURE_2D, 0);

		return id;
	}




}// namespace Texture