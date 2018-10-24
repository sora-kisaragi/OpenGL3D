/*
* @file Shader.cpp
*/
#include "Shader.h"
#include <vector>
#include <iostream>

/**
* シェーダーに関する機能を格納する名前空間
*/
namespace Shader {




/**
* シェーダー･プログラムをコンパイルする
*
* @param type	シェーダーの種類
* @param string シェーダー･プログラムへのポインタ
*	
* @retval 0より大きい	作成したシェーダー･オブジェクト
* @retval 0				シェーダー･オブジェクトの作成に失敗
*/
GLuint Compile(GLenum type, const GLchar* string)
{
	//シェーダーオブジェクトを作成
	GLuint shader = glCreateShader(type);

	//作成したシェーダーオブジェクトにシェーダープログラムを関連付ける
	glShaderSource(shader, 1, &string, nullptr);

	//関連付けたシェーダープログラムをコンパイル
	//シェーダーオブジェクトにセット
	glCompileShader(shader);

	// コンパイルに失敗した場合、原因をコンソールに出力して0を返す.
	GLint compiled = 0;

	//シェーダーオブジェクトの状態を取得する
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	//もしコンパイルに失敗したら
	if (!compiled) {

		//引数 0
		GLint infoLen = 0;

		//GL_INFO_LENGTHを指定すると、詳細情報のバイト数を取得。
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		
		if (infoLen) {
			//詳細情報を取得するためのバッファ
			std::vector<char> buf;

			//std::vectorのサイズを変更する関数 std::vector::resize
			buf.resize(infoLen);

			//サイズ変更に成功した場合
			if ((int)buf.size() >= infoLen) {

				//bufに詳細情報を取り込む
				glGetShaderInfoLog(shader, infoLen, nullptr, buf.data());
				//bufの内容をエラー表示
				std::cerr << "ERROR: シェーダーのコンパイルに失敗.\n" << buf.data() << std::endl;
			}

		}
		//シェーダーオブエクとを削除
		glDeleteShader(shader);

		//コンパイル失敗で０を返す
		return 0;

	}
	//コンパイル成功でシェーダーオブジェクトを返す
	return shader;
}


/**
* プログラムオブジェクトを作成する
*
* @param vsCode 頂点シェーダプログラムへのポインタ
* @param fsCode フラグメントシェーダプログラムへのポインタ
*
* @retval 0より大きい	作成したプログラムオブジェクト
* @retval 0				プログラムオブジェクトの作成に失敗
*/
GLuint Build(const GLchar* vsCode, const GLchar* fsCode)
{
	//シェーダープログラムからシェーダーオブジェクトを作成
	GLuint vs = Compile(GL_VERTEX_SHADER, vsCode);
	GLuint fs = Compile(GL_FRAGMENT_SHADER, fsCode);
	
	//失敗したら0を返す
	if (!vs || !fs) {
		return 0;
	}

	//プログラムオブジェクトを作成
	GLuint program = glCreateProgram();

	//シェーダーオブジェクトをプログラムオブジェクトに割り当てる
	glAttachShader(program, fs);

	//削除マークをつけて削除待機
	glDeleteShader(fs);

	//シェーダーオブジェクトをプログラムオブジェクトに割り当てる
	glAttachShader(program, vs);

	//削除マークをつけて削除待機
	glDeleteShader(vs);

	//割り当てたシェーダーオブジェクト同士をリンク
	glLinkProgram(program);

	//リンクに失敗した場合,原因をコンソールに出力して0を返す
	GLint linkStatus = GL_FALSE;

	//シェーダープログラムの状態を取得する
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

	//もしリンク出来ていない場合
	if (linkStatus != GL_TRUE) {
		//変数を0に
		GLint infoLen = 0;

		//詳細情報を取得する
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		
		if (infoLen) {

			//詳細情報を取得するバッファ
			std::vector<char> buf;

			//bufをリサイズ
			buf.resize(infoLen);

			//リサイズに成功したら
			if ((int)buf.size() >= infoLen) {
				
				//bufに詳細情報をいれる
				glGetProgramInfoLog(program, infoLen, nullptr, buf.data());
				
				//詳細情報をエラー出力
				std::cerr << "ERROR:シェーダーのリンクに失敗.\n" << buf.data() << std::endl;
			}
		}

		//シェーダーオブジェクトを削除
		glDeleteProgram(program);

		//失敗したら0を返す
		return 0;
	}
	//成功したらprogramを返す
	return program;
}



}//Shader namespace