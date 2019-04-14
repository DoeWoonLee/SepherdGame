#ifndef Engine_Typedef_h__
#define Engine_Typedef_h__



typedef unsigned char	_ubyte;
typedef signed char		_byte;

typedef unsigned short	_ushort;
typedef signed short	_short;

typedef unsigned int	_uint;
typedef signed int		_int;

typedef unsigned long	_ulong;
typedef signed long		_long;

typedef bool			_bool;

typedef float			_float;
typedef double			_double;

//typedef XMFLOAT2		_vec2;
//typedef XMFLOAT3		_vec3;
//typedef XMFLOAT4		_vec4;
//typedef XMFLOAT4X4		_matrix;
//

static const XMVECTORF32 g_vFLTMAX = { FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX };
static const XMVECTORF32 g_vFLTMIN = { -FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX };
static const XMVECTORF32 g_vHalfVector = { 0.5f, 0.5f, 0.5f, 0.5f };
static const XMVECTORF32 g_vMultiplySetzwToZero = { 1.0f, 1.0f, 0.0f, 0.0f };
static const XMVECTORF32 g_vZero = { 0.0f, 0.0f, 0.0f, 0.0f };

namespace Engine
{

	static const int ANI_EVENT_SIZE = 20;
	static const int DYNAMIC_RESOURCE_KEY_LENGTH = 30;
	enum AABB_INDEX
	{
		AABB_TOP,
		AABB_BOTTOM,
		AABB_RIGHT,
		AABB_LEFT,
		AABB_FRONT,
		AABB_BACK,
		AABB_END
	};
};


#endif // Engine_Typedef_h__
