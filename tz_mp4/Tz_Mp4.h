#pragma once

#ifndef _TZ_MP4_H_
#define _TZ_MP4_H_

#ifdef TZ_MP4_EXPORTS
#define TZ_MP4 _declspec(dllexport)
#else
#define TZ_MP4 _declspec(dllimport)
#endif
#ifdef __cplusplus
#include <string>
using namespace std;

extern "C"
{
	/*����˵������ʼ���ӿ�
	 *������
	 *[out]lPlayID���������������ӿڶ�ͨ���ľ������
	 *[in]sFilePath:¼��洢·��
	 *[in]w:ͼ���
	 *[in]h:ͼ���
	 *[in]frameRate:��Ƶ֡��
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool  __stdcall  open_mp4(unsigned int &lPlayID,const char* sFilePath, unsigned int w,unsigned int h,unsigned int frameRate);
	/*����˵��������д��ӿ�
	 *������
	 *[in]lPlayID���������
	 *[in]sData:¼������
	 *[in]nDateLen:¼�����ݳ���
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool __stdcall   write_frame(unsigned int lPlayID,const char* sData,unsigned int nDateLen);
	/*����˵������ȡʱ���ӿ�
	 *������
	 *[in]lPlayID���������
	 *[out]ts:��ʱ��
	 *[out]cur_ts:��ǰʱ��
	 *[return] true �ɹ�  false ʧ�� 
	*/	
	TZ_MP4 bool __stdcall   play_ts(unsigned int lPlayID,unsigned int &ts,unsigned int &cur_ts);
	/*����˵�������Žӿ�
	 *������
	 *[in]lPlayID���������
	 *[in]hWnd:¼�񲥷Ŵ��ھ��
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool __stdcall   play_start(unsigned int lPlayID,unsigned int hWnd);
	/*����˵������ͣ���Žӿ�
	 *������
	 *[in]lPlayID���������
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool __stdcall   play_pause(unsigned int lPlayID);
	/*����˵�����������Žӿ�
	 *������
	 *[in]lPlayID���������
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool __stdcall   play_resume(unsigned int lPlayID);
	/*����˵������һ֡���Žӿ�
	 *������
	 *[in]lPlayID���������
	 *[return] true �ɹ�  false ʧ�� 
	*/	
	TZ_MP4 bool __stdcall   play_step(unsigned int lPlayID);
	/*����˵������һ֡���Žӿ�
	 *������
	 *[in]lPlayID���������
	 *[return] true �ɹ�  false ʧ�� 
	*/	
	TZ_MP4 bool __stdcall   play_step_prev(unsigned int lPlayID);
	
	/*����˵������λ���Žӿ�
	 *������
	 *[in]lPlayID���������
	 *[in]start_time:��λʱ��
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool __stdcall   play_start_time(unsigned int lPlayID,unsigned int start_time);
	/*����˵������ʼ���Ϊ�ļ��ӿ�
	 *������
	 *[in]lPlayID���������
	 *[in]sSavePath:�ļ�·��
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool __stdcall   play_save_start(unsigned int lPlayID,const char* sSavePath);
	/*����˵�����������Ϊ�ļ��ӿ�
	 *������
	 *[in]lPlayID���������
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool __stdcall   play_save_stop(unsigned int lPlayID);
	/*����˵�������ٲ��Žӿ�
	 *������
	 *[in]lPlayID���������
	 *[in]speed:�ٶ�
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool __stdcall   play_speed(unsigned int lPlayID,int speed);
	/*����˵����ֹͣ���Žӿ�
	 *������
	 *[in]lPlayID���������
	 *[return] true �ɹ�  false ʧ�� 
	*/	
	TZ_MP4 bool __stdcall   play_stop(unsigned int lPlayID);
	/*����˵��������ʼ���ӿ�
	 *������
	 *[in]lPlayID���������
	 *[return] true �ɹ�  false ʧ�� 
	*/
	TZ_MP4 bool __stdcall   close_mp4(unsigned int lPlayID);
};
#endif
#endif


