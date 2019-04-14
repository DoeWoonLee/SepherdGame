#ifndef ResourceInclude_h__
#define ResourceInclude_h__

#include "TextureMgr.h"

namespace CLIENT
{

	void PreLoadTextoures(void)
	{
		#define LOAD_TEXTURE(KEY, PATH) CTextureMgr::GetInstance()->Ready_Texture(KEY, PATH)
		LOAD_TEXTURE("Player", _T("../Resources/Test.bmp"));
		LOAD_TEXTURE("WoodPillar", _T("../Resources/WoodPillar.bmp"));
	}

}

#endif // !ResourceInclude_h__
