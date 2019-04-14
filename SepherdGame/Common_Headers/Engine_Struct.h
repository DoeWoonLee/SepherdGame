#ifndef Engine_Struct_h__
#define Engine_Struct_h__


namespace Engine
{
	struct Triangle
	{
		XMVECTOR pt[3];
		BOOL culled;
	};
	// =============================================
	typedef struct tagFloat2Point
	{
		_float fX;
		_float fY;
	}F2POINT;
}
#endif // Engine_Struct_h__
