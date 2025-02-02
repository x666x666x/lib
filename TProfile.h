#pragma once

// =====================================================================
/**	@class		CTProfileNode
	@author		Greg Hjelstrom & Byon Garrabrant & COFT
	@version	0.1
	@date		2005-03-15
	@brief		�̴� �������ϸ� �ý��� ���ο����� ���̴� Ŭ�����̴�.
				�� Ŭ������ �ڵ� �� �ϳ��� �Һ��� �� �ð��� �� ����
				ȣ�� Ƚ���� �����Ѵ�. CPU �� �� ����� �����ȿ� ������,
				�� ���� ���� �ð��� �����Ѵ�.
	
*/// ===================================================================
class CTProfileNode {
	// #####################################################################
	// ��� ����
	// #####################################################################
public:
	const char*		Name;
	int				TotalCalls;
	float			TotalTime;
	__int64			StartTime;
	int				RecursionCounter;

	CTProfileNode*	Parent;
	CTProfileNode*	Child;
	CTProfileNode*	Sibling;

	// #####################################################################
	// ��� �Լ�
	// #####################################################################
public:	
	/**
		������
		@param name		�� ����� �̸�
		@param parent	�θ� ���
	*/
	CTProfileNode( const char * name, CTProfileNode * parent );
	/// �Ҹ���
	~CTProfileNode( void );

	CTProfileNode * 	Get_Sub_Node( const char * name );

	CTProfileNode * 	Get_Parent( void )			{ return Parent; }
	CTProfileNode * 	Get_Sibling( void )			{ return Sibling; }
	CTProfileNode * 	Get_Child( void )			{ return Child; }

	void			Reset( void );
	void			Call( void );
	bool			Return( void );

	const char *	Get_Name( void )			{ return Name; }
	int				Get_Total_Calls( void )		{ return TotalCalls; }
	float			Get_Total_Time( void )		{ return TotalTime; }
	
};// end of CTProfileNode

// =====================================================================
/**	@ingroup	CTProfileIterator
	@class		Profile
	@author		Greg Hjelstrom & Byon Garrabrant & COFT
	@version	0.1
	@date		2005-03-15
	@brief		�� Ŭ������ �������� Ʈ���� ���ϰ� Ž���ϴµ� ���̴� ��
				�����̴�. �� Ŭ������ Ʈ��Ž�� �� Ư�� ����� ���� ǥ�ÿ�
				�ʿ��� �Լ��� �����Ѵ�.  �Ϲ������� �ϳ��� ���� �׿� ��
				�� ����� �ڽ� ������ ǥ�õȴ�. �� �ڽĿ� ���ؼ��� ��
				�Һ�ð�, �� ȣ�� Ƚ��, ������ �� ȣ�� Ƚ��, ������ �� ��
				�� �ð� ���� ǥ�õȴ�.

*/// ===================================================================
class CTProfileIterator {

	friend	class CTProfileManager;

	// #####################################################################
	// ��� ����
	// #####################################################################
public:
	CTProfileNode*	CurrentParent;
	CTProfileNode*	CurrentChild;

	// #####################################################################
	// ��� �Լ�
	// #####################################################################
protected:
	CTProfileIterator( CTProfileNode * start );
	
public:	
	// Access all the children of the current parent
	//
	void				First(void);
	void				Next(void);
	bool				Is_Done(void);

	void				Enter_Child( int index );		// Make the given child the new parent
	void				Enter_Largest_Child( void );	// Make the largest child the new parent
	void				Enter_Parent( void );			// Make the current parent's parent the new parent

	// Access the current child
	//
	const char *		Get_Current_Name( void )			{ return CurrentChild->Get_Name(); }
	int					Get_Current_Total_Calls( void )		{ return CurrentChild->Get_Total_Calls(); }
	float				Get_Current_Total_Time( void )		{ return CurrentChild->Get_Total_Time(); }

	// Access the current parent
	//
	const char *		Get_Current_Parent_Name( void )			{ return CurrentParent->Get_Name(); }
	int					Get_Current_Parent_Total_Calls( void )	{ return CurrentParent->Get_Total_Calls(); }
	float				Get_Current_Parent_Total_Time( void )	{ return CurrentParent->Get_Total_Time(); }

};// end of CTProfileIterator

// =====================================================================
/**	@ingroup	CTProfileManager
	@class		Profile
	@author		Greg Hjelstrom & Byon Garrabrant & COFT
	@version	0.1
	@date		2005-03-15
	@brief		�� Ŭ������ �������ϸ� �ý��ۿ� ���� �ܺ� �������̽��̴�.
				�� Ŭ������ ���� ����ȴ� �ڵ� ������ �ش��ϴ� �������� Ʈ
				���� ����Ű�� CurrentNode �����͸� �����Ѵ�. ���� ǥ�� ��
				������ �������� Ʈ���� ������ �� ���� �Լ��鵵 �����Ѵ�.

*/// ===================================================================
class CTProfileManager {
	// #####################################################################
	// ��� ����
	// #####################################################################
public:
	static	CTProfileNode		Root;
	static	CTProfileNode*		CurrentNode;
	static	int					FrameCounter;
	static	__int64				ResetTime;

	// #####################################################################
	// ��� �Լ�
	// #####################################################################
public:	
	/**
		�������� ǥ���� �����Ѵ�. �� �Լ��� ��û�� ���������� �̸��� ���� �����
		�̸��� ���Ͽ� ������� ��ȯ�� �����Ѵ�.
		
		@param name		���� �̸�
	*/
	static	void				Start_Profile( const char* name );
	
	/**
		�������� ǥ���� ������. �� �Լ��� �켱 ���� ��忡 ���� Return() �Լ���
		ȣ���ؼ� �ð� ������ �����ϰ� ����� ����Ѵ�. �������� �����ڴ� ǥ�� ��
		������ ���� ��带 ��� �����ϹǷ�, �� ���������� ��� �˻��� �Ͼ��
		�ʴ´�. ��� ������ �ƴ϶�� �θ� ��带 ���� ���� �����.
	*/
	static	void				Stop_Profile( void );

	static	void				Reset( void );
	static	void				Increment_Frame_Counter( void );
	static	int					Get_Frame_Count_Since_Reset( void )		{ return FrameCounter; }
	static	float				Get_Time_Since_Reset( void );

	static	CTProfileIterator *	Get_Iterator( void )	{ return new CTProfileIterator( &Root ); }
	static	void				Release_Iterator( CTProfileIterator * iterator ) { delete iterator; }

	//* ���� �������� ���¸� �α����Ͽ� ����Ѵ�.
	static	void				Log(CTProfileNode* node = NULL, int depth = 0);

};// end of CTProfileManager

// =====================================================================
/*!	@ingroup	CTProfileSample
	@class		Profile
	@author		Greg Hjelstrom & Byon Garrabrant & COFT
	@version	0.1
	@date		2005-03-15
	@brief		�� ���� Ŭ������ �����ڿ��� Start_Profile �� ȣ���ϰ� �Ҹ���
				���� Stop_Profile �� ȣ���ϴ� �͸��� ������ �ӹ��̴�.

*/// ===================================================================
class CTProfileSample {
	// #####################################################################
	// ��� �Լ�
	// #####################################################################
public:
	CTProfileSample( const char * name )
	{ 
		CTProfileManager::Start_Profile( name ); 
	}

	~CTProfileSample( void )					
	{ 
		CTProfileManager::Stop_Profile(); 
	}

};// end of CTProfileSample

// =====================================================================
// Macro
// =====================================================================
#ifdef TEST_MODE
	#define	TPROFILE_AUTO( name )		CTProfileSample __profile( name )
	#define	TPROFILE_START( name )		CTProfileManager::Start_Profile( name )
	#define	TPROFILE_END( name )		CTProfileManager::Stop_Profile()
	#define TPROFILE_RESET				CTProfileManager::Reset();
	#define TPROFILE_LOG(node)			CTProfileManager::Log(node);
#else
	#define	TPROFILE_AUTO( name )		
	#define	TPROFILE_START( name )		
	#define	TPROFILE_END( name )		
	#define TPROFILE_RESET			
	#define TPROFILE_LOG(node)		
#endif

class CProfiler
{
public:
	double m_dAccumulatedSec;
	UINT m_uNumberOfTimes;

public:
	CProfiler()
	{
		m_dAccumulatedSec = 0;
		m_uNumberOfTimes = 0;
	}

	~CProfiler()
	{
	}
};

class CProfileSample
{
public:
	inline CProfileSample( CProfiler& p, BOOL bProfile=TRUE )
		: m_Profiler(p), m_bProfile(bProfile)
	{
		if( m_bStartProfiling && m_bProfile )
			QueryPerformanceCounter( &m_liStartTime );
	}

	inline ~CProfileSample()
	{
		if( m_bStartProfiling && m_bProfile )
		{
			LARGE_INTEGER liEnd;
			QueryPerformanceCounter(&liEnd);

			++m_Profiler.m_uNumberOfTimes;
			m_Profiler.m_dAccumulatedSec +=
				( ((double)liEnd.QuadPart) / m_liFrequency.QuadPart) - ( ((double)m_liStartTime.QuadPart) / m_liFrequency.QuadPart);
		}
	}

public:
	CProfiler& m_Profiler;
	LARGE_INTEGER m_liStartTime;
	BOOL m_bProfile;

public:
	static LARGE_INTEGER m_liFrequency;
	static BOOL m_bStartProfiling;

	static void InitFrequency()
	{
		QueryPerformanceFrequency(&m_liFrequency);
	}
	
	static void StartProfiling()
	{
		m_bStartProfiling = TRUE;
	}
};