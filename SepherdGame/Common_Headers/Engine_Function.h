#ifndef Engine_Function_h__
#define Engine_Function_h__

namespace Engine
{
	template <typename T>
	void Safe_Delete(T& Instance)
	{
		if(nullptr != Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}
	template <typename T>
	void Safe_Delete_Array(T& Instance)
	{
		if(nullptr != Instance)
		{
			delete [] Instance;
			Instance = nullptr;
		}
	}

	template <typename T>
	_ulong Safe_Release(T& Instance)
	{
		_ulong dwRefCnt = 0;

		if(nullptr != Instance)
		{
			dwRefCnt = Instance->Release();
			if(0 == dwRefCnt)
				Instance = nullptr;
		}
		return dwRefCnt;
	}
	static TCHAR* Create_DynamicTCHAR(const TCHAR* pInChar, _uint iSize)
	{
		TCHAR* pChar = new TCHAR[iSize];
		lstrcpy(pChar, pInChar);

		return pChar;
	}
	// Write
	template<typename T>
	void WriteBinary(std::ofstream& fOut, T& Value)
	{
		fOut.write(reinterpret_cast<const char*>(&Value), sizeof(T));
	}
	static void WriteBinaryChar(std::ofstream& fOut, char* pStr, int iLength)
	{
		fOut.write(pStr, sizeof(char) * iLength);
	}
	static void WriteBinaryTChar(std::ofstream& fOut, TCHAR* pStr, int iLength)
	{
		fOut.write(reinterpret_cast<const char*>(pStr), sizeof(TCHAR) * iLength);
	}
	// Read
	template<typename T>
	void ReadBinary(std::ifstream& fIn, T& Value)
	{
		fIn.read(reinterpret_cast<char*>(&Value), sizeof(T));
	}
	static void ReadBinaryChar(std::ifstream& fIn, char* pStr, int iLength)
	{
		fIn.read(pStr, sizeof(char) * iLength);
	}
	static void ReadBinaryTChar(std::ifstream& fIn, TCHAR* pStr, int iLength)
	{
		fIn.read(reinterpret_cast<char*>(pStr), sizeof(TCHAR) * iLength);
	}
}

#endif // Engine_Function_h__
