#ifndef Engine_Define_h__
#define Engine_Define_h__

#pragma  warning (disable : 4251)
//#pragma  warning (disable : 4275)

#include <DirectXMath.h>

using namespace DirectX;
//#include <d3dx9math.h>
//#include <xnamath.h>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <tchar.h>


#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>

#include "Engine_Typedef.h"
#include "Engine_Constant.h"
#include "Engine_Function.h"
#include "Engine_Functor.h"
#include "Engine_Macro.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"

#include "Engine_Struct.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
#endif // Engine_Define_h__
