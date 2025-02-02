// D3DDevice.h: interface for the CD3DDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined ___D3DDEVICE_H
#define ___D3DDEVICE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef enum PSTYPE
{
	PS_STAGE1 = 0,
	PS_MODULATE,
	PS_MODULATE2X,
	PS_MODULATE4X,
	PS_ADD,
	PS_ADDSIGNED,
	PS_ADDSIGNED2X,
	PS_SUBTRACT,
	PS_ADDSMOOTH,
	PS_BLENDDIFFUSEALPHA,
	PS_BLENDTEXTUREALPHA,
	PS_BLENDFACTORALPHA,
	PS_BLENDTEXTUREALPHAPM,
	PS_BLENDCURRENTALPHA,
	PS_MODULATEALPHA_ADDCOLOR,
	PS_MODULATECOLOR_ADDALPHA,
	PS_MODULATEINVALPHA_ADDCOLOR,
	PS_MODULATEINVCOLOR_ADDALPHA,
	PS_DOTPRODUCT3,
	PS_MULTIPLYADD,
	PS_LERP,
	PS_SHADER,
	PS_DETAILMAP,
	PS_MAP,
	PS_COUNT
} *LPPSTYPE;


typedef enum VSTYPE
{
	VS_WMESHVERTEX = 0,
	VS_MESHVERTEX,
	VS_LVERTEX,
	VS_COUNT
} *LPVSTYPE;


typedef enum PSCONSTANT
{
	PC_COMMON = 0,
	PC_ARG,
	PC_TFACTOR,
	PC_COUNT
} *LPPSCONSTANT;


typedef enum VSCONSTANT
{
	VC_COMMON = 0,
	VC_WORLD,
	VC_PROJ,
	VC_TEXTRAN0,
	VC_TEXTRAN1,
	VC_MTRLAMBIENT,
	VC_MTRLDIFFUSE,
	VC_AMBIENT,
	VC_CAMPOS,
	VC_LIGHTCOUNT,
	VC_LIGHTAMBIENT,
	VC_LIGHTDIFFUSE,
	VC_LIGHTDIR,
	VC_SKINNING,
	VC_COUNT
} *LPVSCONSTANT;

typedef enum TEXTURE_DETAIL_LEVEL
{
	TEXTURE_DETAIL_LOW = 0,
	TEXTURE_DETAIL_MED,
	TEXTURE_DETAIL_HI,
	TEXTURE_DETAIL_COUNT
} *LPTEXTURE_DETAIL;

typedef struct tagGAMEOPTION
{
	DWORD m_dwPresentationInterval;
	DWORD m_dwSwapEffect;
	DWORD m_dwBehavior;
	DWORD m_dwScreenX;
	DWORD m_dwScreenY;

	BYTE m_bWindowedMode;
	BYTE m_bUseSHADER;

	TEXTURE_DETAIL_LEVEL m_nTextureDetail;

	tagGAMEOPTION()
	{
		m_dwPresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_dwSwapEffect = D3DSWAPEFFECT_COPY;
		m_dwBehavior = D3DCREATE_MIXED_VERTEXPROCESSING;
		m_dwScreenX = 1024;
		m_dwScreenY = 768;

		m_bWindowedMode = FALSE;
		m_bUseSHADER = TRUE;

		m_nTextureDetail = TEXTURE_DETAIL_COUNT;
	}
} GAMEOPTION, *LPGAMEOPTION;


class CD3DDevice
{
protected:
	D3DFORMAT GetBestZFormat(
		UINT nAdapter,
		D3DDEVTYPE nType,
		D3DFORMAT nFormat);

	void InitBACK( D3DDISPLAYMODE *pMODE);
	void ReleaseBACK();
	void InitCAPS();

public:
	LPDIRECT3DTEXTURE9 LoadTexture(
		LPBYTE pResData,
		UINT nLength,
		UINT nMipLevels);

	BOOL InitDevices( CWnd *pWnd);
	BOOL ResetHost();
	BOOL Reset();

	void BeginGLOWScene();
	void EndGLOWScene(
		CD3DCamera *pCAMERA,
		FLOAT fGlowRange);
	void ReleaseDevice();

public:
	void SetResetFlag( BYTE bRESET);
	BYTE GetResetFlag();

public:
	CRITICAL_SECTION m_cs;

	BYTE m_bUseTHREAD;
	BYTE m_bRESET;

public:
	static DWORD m_dwPolyCount;

	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3D9 m_pD3D;

	LPDIRECT3DVERTEXSHADER9 m_pVertexShader[VS_COUNT];
	LPDIRECT3DPIXELSHADER9 m_pPixelShader[PS_COUNT];
	LPDIRECT3DVERTEXDECLARATION9 m_pDECL[VS_COUNT];

	CString m_strResourceType;
	BYTE m_bEnableSHADER;

	DWORD m_dwVertexShader[VS_COUNT];
	DWORD m_dwPixelShader[PS_COUNT];

	WORD m_vConstantVS[VC_COUNT];
	WORD m_vConstantPS[PC_COUNT];

	D3DPRESENT_PARAMETERS m_vPRESENT;
	GAMEOPTION m_option;
	D3DCAPS9 m_vCAPS;

	ULONGLONG m_lVIDEOMEM;
	ULONGLONG m_lSYSMEM;

	LPDIRECT3DVERTEXBUFFER9 m_pBACKVB;
	LPDIRECT3DTEXTURE9 m_pGRAYTEX;
	LPDIRECT3DTEXTURE9 m_pGLOWTEX;
	LPDIRECT3DTEXTURE9 m_pBACKTEX;
	LPDIRECT3DTEXTURE9 m_pBACKTEX2;
	LPDIRECT3DSURFACE9 m_pGRAYBUF;
	LPDIRECT3DSURFACE9 m_pGLOWBUF;
	LPDIRECT3DSURFACE9 m_pBACKBUF;
	LPDIRECT3DSURFACE9 m_pBACKBUF2;
	LPDIRECT3DSURFACE9 m_pRTARGET;
	LPDIRECT3DSURFACE9 m_pZBUF;

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pEraserVB;
	LPDIRECT3DINDEXBUFFER9 m_pEraserIB;

	CWnd* m_pMainWnd;

public:
	CD3DDevice();
	virtual ~CD3DDevice();
};


#endif // !defined ___D3DDEVICE_H
