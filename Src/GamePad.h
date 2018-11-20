/**
* @file GamePad.h
*/
#ifndef GAMEPAD_H_INCLUDED
#define GAMEPAD_H_INCLUDED
#include <stdint.h>


/**
* �Q�[���p�b�h���
* ���̓f�[�^�\����
*/
struct GamePad
{
	enum {
		DPAD_UP		= 0x0001,
		DPAD_DOWN	= 0x0002,
		DPAD_LEFT	= 0x0004,
		DPAD_RIGHT	= 0x0008,

		START	= 0x0010,
		
		A	= 0x0020,
		B	= 0x0040,
		X	= 0x0080,
		Y	= 0x0100,

		L	= 0x0200,
		R	= 0x0400,
		
		LT	= 0x0800,
		RT	= 0x1000,
		
		Back	= 0x2000,
		Mode	= 0x4000,

	};
	uint32_t buttons = 0;		//������Ă���ԃt���O������	PressOnly
	uint32_t buttonDown = 0;	//�����ꂽ�u�Ԃ����t���O������	PushOnly
};

#endif