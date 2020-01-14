#ifndef _VORX_ERROR_CODE_DEFINE_HEAD_FILE
#define _VORX_ERROR_CODE_DEFINE_HEAD_FILE

namespace vfc
{
#ifndef ERRCODE_BASE
	#define ERRCODE_BASE 0
#endif // !defined ERRCODE_BASE
	
	enum VORX_ERRCODE
	{
		ERR_SUCCESS		= 0,		//ִ�гɹ�
/*
		ERR_UNKNOWN		= ERRCODE_BASE+1,		//δ֪����
		ERR_UNEXIST		= ERRCODE_BASE+2,		//�豸������
		ERR_NETSEND		= ERRCODE_BASE+3,		//���緢��ʧ��
		ERR_NETTIMEOUT	= ERRCODE_BASE+4,		//������ջ�Ӧ����ʱ
		ERR_UNKNOWNCMD	= ERRCODE_BASE+5,		//δ֪����
		ERR_UNLOGINED	= ERRCODE_BASE+6,		//�ն�δ��¼
		ERR_UNSUPPORT	= ERRCODE_BASE+7,		//��֧�ֵ�ָ��
		ERR_SPACE		= ERRCODE_BASE+8,		//�������ռ䲻��
		ERR_INSTANCE	= ERRCODE_BASE+9,		//ʵ��������
		ERR_UNINITIALIZE= ERRCODE_BASE+10,		//δ��ʼ��
		ERR_FORMAT		= ERRCODE_BASE+11,		//����ʽ����
		ERR_PARAM		= ERRCODE_BASE+12,		//��������
		ERR_DEVICE		= ERRCODE_BASE+13,		//ɾ���б�ʱ,Ŀ���豸δ�ҵ�
		ERR_TARGET		= ERRCODE_BASE+14		//ɾ���б�ʱ,Ŀ���ַδ�ҵ�
*/
		// ����ͨ��
		ERR_NETSEND		= ERRCODE_BASE+0x0101,	//���緢��ʧ��
		ERR_PROTO		= ERRCODE_BASE+0x0102,	//Э���ʽ����
		ERR_UNSUPPORT	= ERRCODE_BASE+0x0103,	//δ֧�ֵ�ָ��
		ERR_NETTIMEOUT	= ERRCODE_BASE+0x0104,	//����Ӧ��ʱ
		ERR_FORMAT		= ERRCODE_BASE+0x0105,	//����ʽ����
		ERR_NETINIT		= ERRCODE_BASE+0x0106,	//��ͨ������ʧ��
		ERR_UNKNOWNCMD	= ERRCODE_BASE+0x0107,	//δ֪����
		// ���ݿ����
		ERR_CONNECTDB	= ERRCODE_BASE+0x0201,	//�������ݿ�ʧ��
		ERR_UNCONNECTDB	= ERRCODE_BASE+0x0202,	//δ�������ݿ�
		ERR_READDB		= ERRCODE_BASE+0x0203,	//��ȡ���ݿ�����ʧ��
		ERR_MODIFYDB	= ERRCODE_BASE+0x0204,	//д���ݿ�ʧ��
		// �ڴ�
		ERR_MEMORY		= ERRCODE_BASE+0x0301,	//�����ڴ�ʧ��
		ERR_SPACE		= ERRCODE_BASE+0x0302,	//�������ռ䲻��
		// ���
		ERR_UNLOGINED	= ERRCODE_BASE+0x0401,	//�ն�δ��¼
		ERR_UNINITIALIZE= ERRCODE_BASE+0x0402,	//δ��ʼ��
		ERR_INSTANCE	= ERRCODE_BASE+0x0403,	//ʵ��������
		ERR_EXISTINSTANCE=ERRCODE_BASE+0x0404,	//ʵ���Ѵ���
		ERR_PARAM		= ERRCODE_BASE+0x0405,	//��������
		ERR_DEVICE		= ERRCODE_BASE+0x0406,	//ɾ���б�ʱ,Ŀ���豸δ�ҵ�
		ERR_TARGET		= ERRCODE_BASE+0x0407,	//ɾ���б�ʱ,Ŀ���ַδ�ҵ�
		ERR_UNEXIST		= ERRCODE_BASE+0x0408,	//�豸������
		// �߳�/����
		ERR_THREAD		= ERRCODE_BASE+0x0501,	//�̴߳���
		// �ļ�����
		ERR_CREATEDIR	= ERRCODE_BASE+0x0601,	//����Ŀ¼ʧ��
		ERR_DELDIR		= ERRCODE_BASE+0x0602,	//ɾ��Ŀ¼ʧ��
		ERR_OPENDIR		= ERRCODE_BASE+0x0603,	//��Ŀ¼ʧ��
		ERR_CREATEFILE	= ERRCODE_BASE+0x0604,	//�����ļ�ʧ��
		ERR_DELLFILE	= ERRCODE_BASE+0x0605,	//ɾ���ļ�ʧ��
		ERR_OPENFILE	= ERRCODE_BASE+0x0606,	//���ļ�ʧ��
		ERR_WRITEFILE	= ERRCODE_BASE+0x0607,	//д�ļ�ʧ��
		ERR_CLOSEFILE	= ERRCODE_BASE+0x0608,	//�ر��ļ�ʧ��
		ERR_SRCTYPEUNDEF= ERRCODE_BASE+0x0609,	//stream�е�m_nSrcTypeΪ-1
	};

	struct VorxErrDesc
	{
		int nCode;
		char szDesc[50];
	};

/*
	const VorxErrDesc g_errdesc[] = 
	{
		{ERR_SUCCESS, "�ɹ�"},
		{ERR_UNKNOWN, "δ֪����"},
		{ERR_UNEXIST, "�豸������"},
		{ERR_NETSEND, "���緢��ʧ��"},
		{ERR_NETTIMEOUT, "������ջ�Ӧ����ʱ"},
		{ERR_UNKNOWNCMD, "δ֪����"},
		{ERR_UNLOGINED, "�ն�δ��¼"},
		{ERR_UNSUPPORT, "��֧�ֵ�ָ��"},
		{ERR_SPACE, "�������ռ䲻��"},
		{ERR_INSTANCE, "ʵ��������"},
		{ERR_UNINITIALIZE, "δ��ʼ��"},
		{ERR_FORMAT, "����ʽ����"},
		{ERR_PARAM, "��������"},
		{ERR_DEVICE, "ɾ���б�ʱ,Ŀ���豸δ�ҵ�"},
		{ERR_TARGET, "ɾ���б�ʱ,Ŀ���ַδ�ҵ�"}
	};
*/
	const VorxErrDesc g_errdesc[] = 
	{
		{ERR_SUCCESS, "�ɹ�"},
// 		{ERR_UNKNOWN, "δ֪����"},
		// ����ͨ��
		{ERR_NETSEND, "���緢��ʧ��"},
		{ERR_PROTO, "Э���ʽ����"},
		{ERR_UNSUPPORT, "��֧�ֵ�ָ��"},
		{ERR_NETTIMEOUT, "������ջ�Ӧ����ʱ"},
		{ERR_FORMAT, "����ʽ����"},
		{ERR_NETINIT, "������ʧ��"},
		{ERR_UNKNOWNCMD, "δ֪����"},
		// ���ݿ����
		{ERR_CONNECTDB, "�������ݿ�ʧ��"},
		{ERR_UNCONNECTDB, "δ�������ݿ�"},
		{ERR_READDB, "��ȡ���ݿ�����ʧ��"},
		{ERR_MODIFYDB, "д���ݿ�����ʧ��"},
		// �ڴ�
		{ERR_MEMORY, "�����ڴ�ʧ��"},
		{ERR_SPACE, "�������ռ䲻��"},
		// ���
		{ERR_UNLOGINED, "�ն�δ��¼"},
		{ERR_UNINITIALIZE, "δ��ʼ��"},
		{ERR_INSTANCE, "ʵ��������"},
		{ERR_EXISTINSTANCE, "ʵ���Ѵ���"},
		{ERR_PARAM, "��������"},
		{ERR_DEVICE, "ɾ���б�ʱ,Ŀ���豸δ�ҵ�"},
		{ERR_TARGET, "ɾ���б�ʱ,Ŀ���ַδ�ҵ�"},
		{ERR_UNEXIST, "�豸������"},
		// �߳�/����
		{ERR_THREAD, "�̴߳���"},
		// �ļ�����
		{ERR_CREATEDIR, "����Ŀ¼ʧ��"},
		{ERR_DELDIR, "ɾ��Ŀ¼ʧ��"},
		{ERR_OPENDIR, "��Ŀ¼ʧ��"},
		{ERR_CREATEFILE, "�����ļ�ʧ��"},
		{ERR_DELLFILE, "ɾ���ļ�ʧ��"},
		{ERR_OPENFILE, "���ļ�ʧ��"},
		{ERR_WRITEFILE, "�����ļ�ʧ��"},
		{ERR_CLOSEFILE, "�ر��ļ�ʧ��"}
	};
}

#endif
