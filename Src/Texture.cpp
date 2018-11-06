/**
* @file Texture.cpp
*/
#include "Texture.h"
#include <stdint.h>
#include <vector>
#include <fstream>
#include <iostream>

/// テクスチャ関連の関数やクラスを格納する名前空間
namespace Texture {


	/**
	* 2Dテクスチャを作成する.
	*
	* @param width   テクスチャの幅(ピクセル数).
	* @param height  テクスチャの高さ(ピクセル数).
	* @param data    テクスチャデータへのポインタ.
	* @param format  転送元画像のデータ形式.
	* @param type    転送元画像のデータ格納形式.
	*
	* @retval 0以外  作成したテクスチャ・オブジェクトのID.
	* @retval 0      テクスチャの作成に失敗.
	*/
	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data, GLenum format, GLenum type)
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

		//GPUメモリに画像データを転送	GL_UNPACK_ALIGNMENTを指定するとGPUメモリへデータを転送するときのアライメントを指定できる
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, format, type, data);



		//初期値に戻す（初期値は４）
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);



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

		//テクスチャのパラメータを設定する
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// 1要素の画像データの場合、(R,R,R,1)として読み取られるように設定する.
			if (format == GL_RED) {
			const GLint swizzle[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
			glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);

		}



		//Bindを解除
		glBindTexture(GL_TEXTURE_2D, 0);

		return id;
	}

	/**
	* ファイルから2Dテクスチャを読み込む
	*
	* @param path 2D テクスチャとして読み込むファイル名
	*
	* @retval	0 以外	作成したテクスチャオブジェクトのID
	*			0		テクスチャの作成に失敗
	*/
	GLuint LoadImage2D(const char* path)
	{
		//TAG ヘッダを読み込む
		std::basic_ifstream<uint8_t> ifs;
		ifs.open(path, std::ios_base::binary);
		uint8_t tgaHeader[18];
		ifs.read(tgaHeader, 18);

		//イメージIDを飛ばす
		//読み飛ばすときは ignore（イグノア）メンバ関数を使う
		ifs.ignore(tgaHeader[0]);


		//カラーマップを飛ばす
		if (tgaHeader[1]) {
			const int colorMapLength = tgaHeader[5] + tgaHeader[6] * 0x100;
			const int colorMapEntrySize = tgaHeader[7];
			const int colorMapSize = colorMapLength * colorMapEntrySize / 8;
			ifs.ignore(colorMapSize);
		}


		//画像データを読み込む
		const int width = tgaHeader[12] + tgaHeader[13] * 0x100;
		const int height = tgaHeader[14] + tgaHeader[15] * 0x100;
		const int pixelDepth = tgaHeader[16];
		const int imageSize = width * height * pixelDepth / 8;
		std::vector<uint8_t> buf(imageSize);
		ifs.read(buf.data(), imageSize);

		//画像データが「上から舌」で格納されている場合、上下を入れ替える
		if(tgaHeader[17] & 0x20) {
			const int lineSize = width * pixelDepth / 8;
			std::vector<uint8_t>tmp(imageSize);
			std::vector<uint8_t>::iterator source = buf.begin();
			std::vector<uint8_t>::iterator destination = tmp.end();
			for (int i = 0; i < height; i++) {
				destination -= lineSize;
				std::copy(source, source + lineSize, destination);
				source += lineSize;
			}
		
			buf.swap(tmp);
		}


		// 読み込んだ画像データからテクスチャを作成する.
		GLenum type = GL_UNSIGNED_BYTE;
		GLenum format = GL_BGRA;
		if (tgaHeader[2] == 3) {
			format = GL_RED;			
		}

		if (tgaHeader[16] == 24) {
			format = GL_BGR;
		}
		else if (tgaHeader[16] == 16){
			type = GL_UNSIGNED_SHORT_1_5_5_5_REV;
			
		}

		return CreateImage2D(width, height, buf.data(), format, type);

	}





}// namespace Texture