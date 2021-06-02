#pragma once
#include <afxwin.h>

class CSmartButton :public CButton
{
	DECLARE_DYNAMIC(CSmartButton)
		
public:
	CSmartButton();
	virtual ~CSmartButton();

	CImage  m_imgButton;				//��ť����ͼ��
	CString m_strImgPath;			//��ťpng·�����������㣬����������3��״̬
	CString m_strImgParentPath;		//�����ڱ���ͼƬ����·����͸��png��Ҫʹ��

	void SetImagePath(CString strImgPath, CString strParentImgPath);   //���ð�ť����ͼƬ·���������ڱ���ͼƬ·��
	//��ʼ����ť����Ҫ�ǵ�����ť��λ�ã�����͸��ɫ
	bool InitMyButton(int nX/*���Ͻ�X����*/, int nY/*���Ͻ�Y����*/, int nW/*ͼ���*/, int nH/*ͼ���*/, bool bIsPng/*�Ƿ���PNGͼƬ*/);
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);	//�Ի��ƺ���

protected:
	DECLARE_MESSAGE_MAP()
};

