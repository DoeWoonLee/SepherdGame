#ifndef Bitmap_h__
#define Bitmap_h__

#include "Component.h"

class CTexture : public CComponent
{
private:
	explicit CTexture(void);
	virtual ~CTexture(void);
private:
	HRESULT Init_Texture(const TCHAR* pStrPath);
public:
	static CTexture* LoadTexture(const TCHAR* pStrPath);

	long Get_Width(void);
	long Get_Height(void);
	
	HBITMAP Get_Bitmap(void);

	virtual _ulong Release(void)override;
private:
	HBITMAP m_hBitmap;
	long m_lWidth;
	long m_lHeight;
};

#endif // !Bitmap_h__
