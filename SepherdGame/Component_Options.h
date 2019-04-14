#pragma once

#include "Engine_Define.h"

typedef struct tagComEnumStruct
{
	_uint uiBit;
	bool bRenderOption;
	bool bUpdateOption;

	tagComEnumStruct(void) : uiBit(0), bRenderOption(false), bUpdateOption(false) {}
	tagComEnumStruct(_uint _uiBit, bool _bUpdateOption, bool _bRenderOption) :
		uiBit(_uiBit), bRenderOption(_bRenderOption), bUpdateOption(_bUpdateOption) {}
	void Set(_uint _uiBit, bool _bUpdateOption, bool _bRenderOption)
	{
		uiBit = _uiBit;
		bRenderOption = _bRenderOption;
		bUpdateOption = _bUpdateOption;

	}
}COM_ENUM_STRUCT;


#define BIT_COM_TRANSFORM	(1)
#define BIT_COM_SPRITE		(1 << 1)
#define BIT_COM_RESOURCE	(1 << 2)
#define BIT_COM_COLLIDER	(1 << 3)
#define BIT_CONTROLLER		(1 << 4)
#define BIT_RENDERCONTROLLER (1 << 5)

enum COMPONENT_TYPE : _ushort
{
	COM_TRANSFORM,
	COM_SPRITE,
	COM_RESOURCE,
	COM_COLLIDER,
	COM_CONTROLLER,
	COM_RENDERCONTROLLER,
	COM_END
};