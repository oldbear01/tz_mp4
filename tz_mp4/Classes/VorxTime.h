// VorxTime.h: interface for the CVorxTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VORXTIME_H__44F12EB7_C892_404A_BF68_253E20B7D575__INCLUDED_)
#define AFX_VORXTIME_H__44F12EB7_C892_404A_BF68_253E20B7D575__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MacroDefine.h"

namespace vfc
{
	class CVorxTime 
	{
	public:
#ifdef BIG_EDIAN
		UINT32 year:12;								//��
		UINT32 month:4;								//��
		UINT32 day:5;								//��
		UINT32 hour:5;								//ʱ
		UINT32 minute:6;							//��
		
		UINT32 second:6;							//��
		UINT32 enable:1;							//�Ƿ���Ч
		UINT32 used:1;								//�Ƿ�ʹ��
		UINT32 cover:1;								//�Ƿ񸲸�
		UINT32 reserved:23;							//����
#else
		UINT32 minute:6;							//��
		UINT32 hour:5;								//ʱ
		UINT32 day:5;								//��
		UINT32 month:4;								//��
		UINT32 year:12;								//��
		
		UINT32 reserved:23;							//����
		UINT32 cover:1;								//�Ƿ񸲸�
		UINT32 used:1;								//�Ƿ�ʹ��
		UINT32 enable:1;							//�Ƿ���Ч
		UINT32 second:6;							//��
#endif
		
	public:
		bool operator>(const CVorxTime& tm) const;	//ʱ��Ƚ����������
		bool operator>=(const CVorxTime& tm) const;
		bool operator<(const CVorxTime& tm) const;
		bool operator<=(const CVorxTime& tm) const;
		bool operator==(const CVorxTime& tm) const;
		bool operator!=(const CVorxTime& tm) const;
		int operator-(const CVorxTime& tm) const;
		CVorxTime operator-(const int tm) const;
		CVorxTime operator+(const int tm) const;
		void operator+=(const int tm);
		void operator-=(const int tm);

		void SetValue(const CVorxTime& tm);
		bool SetValue(LPCTSTR sTime);
		bool SetValue(int nYear,int nMon,int nDay,int nHour,int nMin,int nSec);

		time_t GetTime() const;
		void SetTime(time_t tm);
#ifdef WIN32
		void SetTime(SYSTEMTIME tm);
		void GetTime(SYSTEMTIME &sysTm);
#endif // defined WIN32

		void GetCurrentTime();						//ȡ��ǰʱ��
		void GetCurrentRTCTime();					//ȡ��ǰRTC(Ӳ��)ʱ��
		void ToString(char* sRet,bool bSeparate);	//ת�����ַ���
		bool IsValid(){return year>0;}
		
		CVorxTime();
		~CVorxTime();
	};
	typedef CVorxTime CVorxIndex;
}
#endif // !defined(AFX_VORXTIME_H__44F12EB7_C892_404A_BF68_253E20B7D575__INCLUDED_)
