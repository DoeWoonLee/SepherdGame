#ifndef Engine_Macro_h__
#define Engine_Macro_h__




#define msg_box(_message)	MessageBox(nullptr, TEXT(_message), TEXT("System Message"), MB_OK)

#define BEGIN(_namespace) namespace _namespace {
#define END }

#define USING(_namespace) using namespace _namespace;

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#ifdef x32
#define NULL_CHECK( _ptr)	\
{if( _ptr == 0){__asm { int 3 };return;}}

#define NULL_CHECK_RETURN( _ptr, _return)	\
{if( _ptr == 0){__asm { int 3 };return _return;}}

#define NULL_CHECK_MSG( _ptr, _message )		\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);__asm { int 3 };}}

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);__asm { int 3 };return _return;}}


#define FAILED_CHECK(_hr)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(NULL, L"Failed", L"System Error",MB_OK); __asm { int 3 }; return E_FAIL;}

#define FAILED_CHECK_RETURN(_hr, _return)	if( ((HRESULT)(_hr)) < 0 )		\
{ MessageBox(NULL, L"Failed", L"System Error",MB_OK); __asm { int 3 }; return _return;}

#define FAILED_CHECK_MSG( _hr, _message)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(NULL, _message, L"System Message",MB_OK); __asm { int 3 };return E_FAIL;}

#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(NULL, _message, L"System Message",MB_OK); __asm { int 3 };return _return;}
#else
#define NULL_CHECK( _ptr)	\
{if( _ptr == 0){__debugbreak();  ;return;}}

#define NULL_CHECK_RETURN( _ptr, _return)	\
{if( _ptr == 0){__debugbreak();  return _return;}}

#define NULL_CHECK_MSG( _ptr, _message )		\
{if( _ptr == 0){MessageBox(nullptr, _message, L"System Message",MB_OK);__debugbreak();  }}

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
{if( _ptr == 0){MessageBox(nullptr, _message, L"System Message",MB_OK);__debugbreak();  return _return;}}


#define FAILED_CHECK(_hr)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(nullptr, L"Failed", L"System Error",MB_OK); __debugbreak();   return E_FAIL;}

#define FAILED_CHECK_RETURN(_hr, _return)	if( ((HRESULT)(_hr)) < 0 )		\
{ MessageBox(nullptr, L"Failed", L"System Error",MB_OK); __debugbreak();   return _return;}

#define FAILED_CHECK_MSG( _hr, _message)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(nullptr, _message, L"System Message",MB_OK); __debugbreak();  return E_FAIL;}

#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(nullptr, _message, L"System Message",MB_OK); __debugbreak();  return _return;}
//inline void FAILED_CHECK(HRESULT hResult) { if (hResult < 0) { MessageBox(NULL, L"Failed", L"System Error", MB_OK); } }

#endif 

#define NO_COPY(CLASSNAME)							\
	private:										\
	CLASSNAME(const CLASSNAME&);					\
	CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)				\
	NO_COPY(CLASSNAME)								\
	private:										\
	static CLASSNAME*	m_pInstance;				\
	public:											\
	static CLASSNAME*	GetInstance( void );		\
	static void DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)				\
	CLASSNAME*	CLASSNAME::m_pInstance = nullptr;		\
	CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
	if(nullptr == m_pInstance) {					\
	m_pInstance = new CLASSNAME;			\
	}											\
	return m_pInstance;							\
	}												\
	void CLASSNAME::DestroyInstance( void ) {		\
	if(nullptr != m_pInstance)	{					\
	delete m_pInstance;						\
	m_pInstance = nullptr;						\
	}											\
	}

#define DECLARE_CREATOR(CLASSNAME, ...) \
public:		\
static CLASSNAME* Create(__VA_ARGS__); \
HRESULT Initialize(__VA_ARGS__);	\
private: \

//#define IMPLEMENT_CREATOR(CLASSNAME, ...)\
//CLASSNAME* CLASSNAME::Create(__VA_ARGS__) 

#define SHADER_FILE(input) L"../bin/Asset/Shaders/"#input L".hlsl"
#define PATH_ASSETFILE(input) L"../bin/Asset/"#input

#define TS ToSIMD
#define LS LoadSIMD


// °øÂ÷
#define TOLERANCE 0.000000000000001f
// Density of air at Sea level, Slugs / ft^3
#define RHO 0.0023769f
// 9.8 * 4
#define GRAVITY 3.92f

#define MAXN(x,y) (((x)>(y)) ? (x) : (y))

// Math Define
#define XMDOT2(V1, V2) XMVector2Dot((V1), (V2)).m128_f32[0]
#define XMDOT3(V1, V2) XMVector2Dot((V1), (V2)).m128_f32[0]
#define XMDOT4(V1, V2) XMVector2Dot((V1), (V2)).m128_f32[0]


// ~ Release ~
#define SAFE_DELETE(p) if(p){delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p){delete [] p; p=nullptr;}
#define SAFE_RELEASE(p) if(p){ ULONG dwRef = p->Release();	p = nullptr; } 
//if(0 == dwRef){ p = nullptr; } }

// ~ WRite ~
#define WRITE_BINARY(fOut, Value, TYPE) fOut.write(reinterpret_cast<const char*>(&Value), sizeof(TYPE))
#define WRITE_BINARY_CHAR(fOut, pStr, iLength) fOut.write(pStr, sizeof(char) * iLength)
#define WRITE_BINARY_TCHAR(fOut, pStr, iLength) fOut.write(reinterpret_cast<const char*>(pStr), sizeof(TCHAR) * iLength)

#define READ_BINARY(fIn, Value, TYPE) fIn.read(reinterpret_cast<char*>(&Value), sizeof(TYPE))
#define READ_BINARY_CHAR(fIn, pStr, iLength) fIn.read(pStr, sizeof(char) * iLength)
#define READ_BINARY_TCHAR(fIn, pStr, iLength) fIn.read(reinterpret_cast<char*>(pStr), sizeof(TCHAR) * iLength)

// Iterator =========================================
#define ITERATOR_LOOP_START(CLASSTYPE, STL, IterValName)	\
	CLASSTYPE::iterator IterValName##_BIter = STL.begin();	\
	CLASSTYPE::iterator IterValName##_EIter = STL.end();	\
	for(;IterValName##_BIter != IterValName##_EIter; IterValName##_BIter++)

#define ITERATOR_PT_LOOP_START(CLASSTYPE, PSTL, ValName)	\
	CLASSTYPE::iterator IterValName##_BIter = PSTL->begin();	\
	CLASSTYPE::iterator IterValName##_EIter = PSTL->end();	\
	for(;IterValName##_BIter != IterValName##_EIter; IterValName##_BIter++)
// Getter Setter
#define DECLARE_GETTER_SETTER(DATATYPE, FUNCTOR)	\
public:										\
	void Set_##FUNCTOR(DATATYPE FUNCTOR);	\
	DATATYPE Get_##FUNCTOR(void);			\
private:									

#define IMPLEMENT_GETTER_SETTER(CLASSNAME,DATATYPE, FUNCTOR, MemberValue)\
	void CLASSNAME::Set_##FUNCTOR(DATATYPE FUNCTOR)			\
	{ MemberValue = FUNCTOR;	}							\
	DATATYPE CLASSNAME::Get_##FUNCTOR(void)					\
	{ return MemberValue; }

// ==================== Bit Operator ==================
#define BIT_OPERATE_CHECK(Operand, Bit) (Operand & Bit)
#define BIT_OPERATE_ADD(Operand, Bit)(Operand |= Bit)
#define BIT_OERPATE_SUB(Operand, Bit)( Operand &= ~(Bit) )

#define DECLARE_BITOPERATOR(FUNCTOR)					\
public:													\
	int Check_BitOption_##FUNCTOR (int iBit);			\
	void Add_BitOption_##FUNCTOR (int iBit);			\
	void Sub_BitOption_##FUNCTOR (int iBit);			\
private:												\
	unsigned int m_i##FUNCTOR;

#define IMPLEMENT_BITOPERATOR(CLASSNAME, FUNCTOR)			\
	int CLASSNAME::Check_BitOption_##FUNCTOR (int iBit)	\
	{ return BIT_OPERATE_CHECK( m_i##FUNCTOR, iBit);	}	\
	void CLASSNAME::Add_BitOption_##FUNCTOR (int iBit)		\
	{	BIT_OPERATE_ADD(m_i##FUNCTOR, iBit); }				\
	void CLASSNAME::Sub_BitOption_##FUNCTOR(int iBit)		\
	{	BIT_OERPATE_SUB(m_i##FUNCTOR, iBit);}
// ====================================================
#define SWAP_DATA(TYPE, DATA1, DATA2)\
	TYPE temp = DATA1; \
	DATA1 = DATA2; \
	DATA2 = temp;

#define SHADER_FILE(input) L"../bin/Asset/Shaders/"#input L".hlsl"
#define PATH_ASSETFILE(input) L"../bin/Asset/"#input

#define BIT16_SIZE 65536

#endif // Macro_h__
