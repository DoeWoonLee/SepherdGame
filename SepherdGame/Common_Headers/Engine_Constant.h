#ifndef Engine_Constant_h__
#define Engine_Constant_h__

namespace Engine
{
	enum SC_UPDATE_RETURNS
	{
		SC_UPDATE_RETURNS_END
	};
	enum GOBJ_UPDATE_RETURNS
	{
		GOBJ_UPDATE_NO_RESOURCES,
		GOBJ_UPDATE_RETURNS_END // No Event
	};
	enum AXIS : unsigned char
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
		AXIS_NONE
	};
	enum XM_IDX : unsigned char
	{
		XM_IDX_X,
		XM_IDX_Y,
		XM_IDX_Z,
		XM_IDX_END
	};
}

#define WIN_CX 800
#define WIN_CY 600

#define FWIN_CX 800.f
#define FWIN_CY 600.f
#endif // Engine_Constant_h__
