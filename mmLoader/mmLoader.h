/********************************************************************
	created:	2014/03/11
	created:	11:3:2014   14:03
	file base:	mmLoader
	file ext:	h
	author:		tishion
	
	purpose:	
*********************************************************************/
#ifndef __MMLOADER_H_INCLUDED_
#define __MMLOADER_H_INCLUDED_

//////////////////////////////////////////////////////////////////////////
// ϵͳ��صĺ���ָ���
typedef struct __NTFUNCPTRS
{
	LPVOID pfnCreateFileW;			//CreateFileW
	LPVOID pfnGetFileSize;			//GetFileSize
	LPVOID pfnCreateFileMappingW;	//CreateFileMappingW
	LPVOID pfnMapViewOfFile;			//MapViewOfFile
	LPVOID pfnUnmapViewOfFile;		//UnmapViewOfFile
	LPVOID pfnCloseHandle;			//CloseHandle
	LPVOID pfnGetModuleHandleA;		//GetModuleHandleA
	LPVOID pfnLoadLibraryA;			//LoadLibraryA
	LPVOID pfnGetProcAddress;		//GetProcAddress
	LPVOID pfnVirtualAlloc;			//VirtualAlloc
	LPVOID pfnVirtualFree;			//VirtualFree
	LPVOID pfnReversed_0;
	LPVOID pfnReversed_1;
	LPVOID pfnReversed_2;
	LPVOID pfnReversed_3;
	LPVOID pfnReversed_4;
}NTFUNCPTRSTABLE, *PNTFUNCPTRSTABLE;

//////////////////////////////////////////////////////////////////////////
// MemModuleObject
typedef struct __MEMMODULE
{
	union							// MemModule base
	{
		DWORD	dwBase;
		HMODULE	hModule;
		LPVOID	lpBase;
		PIMAGE_DOS_HEADER pImageDosHeader;
	};
	DWORD dwSizeOfImage;			// MemModule size
	DWORD dwCrc;					// MemModule crc32

	BOOL	bLoadOk;				// MemModule is load ok?

	PNTFUNCPTRSTABLE pNtFuncptrsTable;	// Pointer to NT function pointers table 

	struct							// Raw file resource data
	{
		HANDLE	h;
		HANDLE	hMapping;
		LPVOID	pBuffer;
	}RawFile;

	TCHAR tszModuleName[MAX_PATH];	// MemModule Name (or full file path name)
}MEM_MODULE, *PMEM_MODULE;



//////////////////////////////////////////////////////////////////////////
// public
// 

/*
 * ���ڿ���MemModuleHelper����Ϊ
 */ 
typedef enum _MMHELPER_METHOD
{
	MHM_BOOL_LOAD,
	MHM_VOID_FREE,
	MHM_FARPROC_GETPROC,
}MMHELPER_METHOD;


/************************************************************************\
 * 
 * ����������
 *		��mmLoader��ShellCode��֮���mmLoader��ʹ�ö�Ҫͨ�����������ʵ��
 * ������
 *		pMmeModule��
 *			
 *		method��
 *			��Ҫ���õĹ��ܵ�����
 *		
 *		lpModuleName��
 *			��Ҫ���ص�ģ����(ֻ�е�methodΪMHM_BOOL_LOADʱ����Ч)
 *		lpProcName��
 *			��Ҫ��ȡ��ַ�ĵ�Proc������(ֻ�е�methodΪMHM_FARPROC_GETPROCʱ����Ч)
 *		
 *		bCallEntry��
 *			�Ƿ���Ҫ����ģ�����ڵ㺯��(ֻ�е�methodΪMHM_BOOL_LOADʱ����Ч)
 *		
 *	����ֵ��
 *		��methodΪMHM_BOOL_LOAD��
 *			����ֵΪBOOL���ͣ������Ƿ�Load�ɹ�
 *			
 *		��methodΪMHM_VOID_FREE��
 *			����ֵ���κ�����
 *		
 *		��methodΪMHM_FARPROC_GETPROC��
 *			����ֵΪFARPROC���ͣ������ȡ��Ŀ�꺯���ĵ�ַ������NULLΪ��ȡʧ��
 *		
 * 
 * 
\************************************************************************/

extern unsigned char mmLoaderShellCode[3712];

EXTERN_C VOID
mmLoaderSCStart();

EXTERN_C VOID
mmLoaderSCEnd();

EXTERN_C int __stdcall
MemModuleHelper(PMEM_MODULE pMmeModule, MMHELPER_METHOD method, LPCTSTR lpModuleName, LPCSTR lpProcName, BOOL bCallEntry);

typedef int (__stdcall * Type_MemModuleHelper)(PMEM_MODULE, MMHELPER_METHOD, LPCTSTR, LPCSTR, BOOL);

EXTERN_C BOOL __stdcall
LoadMemModule(PMEM_MODULE pMemModule, LPCTSTR lpName, BOOL bCallEntry);

EXTERN_C FARPROC __stdcall
GetMemModuleProc(PMEM_MODULE pMemModule, LPCSTR lpName); 

EXTERN_C VOID __stdcall
FreeMemModule(PMEM_MODULE pMemModule);

#endif