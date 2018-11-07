/*
* @file Shader.cpp
*/
#include "Shader.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdint.h>


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
	if (!string) {
		return 0;
	}


	
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


/**
* ファイルを読み込む
*
* @param path 読み込むファイル名
*
* @return 読み込んだデータ
*/
std::vector<GLchar> ReadFile(const char* path)
{
	
	std::basic_ifstream<GLchar> ifs;

	//
	ifs.open(path, std::ios_base::binary);
	
	if (!ifs.is_open()) {
		std::cerr << "ERROR: " << path << " を開けません.\n";
		return {};
		
	}

	
	//
	ifs.seekg(0, std::ios_base::end);
	
	//
	const size_t length = (size_t)ifs.tellg();
	
	ifs.seekg(0, std::ios_base::beg);

	std::vector<GLchar>buf(length);
	
	//
	ifs.read(buf.data(), length);
	
	//
	buf.push_back('\0');
	
	//
	return buf;
}

/**
* ファイルからプログラム・オブジェクトを作成する
*
* @param vsPath 頂点シェーダー・ファイル名
* @param fsPath フラグメントシェーダー・ファイル名
*
* @return 作成したプログラムオブジェクト
*
*/
GLuint BuildFromFile(const char* vsPath, const char* fsPath)
{
	const std::vector<GLchar> vsCode = ReadFile(vsPath);
	const std::vector<GLchar> fsCode = ReadFile(fsPath);
	
	//頂点シェーダーファイルとフラグメントシェーダーファイルを読み込む
	//Build関数にｎ読み込んだデータを渡してプログラムを作成
	return Build(vsCode.data(), fsCode.data());
}


}//Shader namespace