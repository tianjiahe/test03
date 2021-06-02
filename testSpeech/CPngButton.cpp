#include "pch.h"
#include "PngButton.h"

#include "TransparentPNG.h"

// CBitmapButtonEx

IMPLEMENT_DYNAMIC(CPngButton, CBitmapButton)

CPngButton::CPngButton(): CBitmapButton()
	, m_lButtonDown(FALSE)
	, m_bMouseOver(FALSE)
	, m_bTrack(FALSE)
	, m_first(true)
{
}

CPngButton::~CPngButton()
{
	if (NULL != m_imageButtonUp)
	{
		::DeleteObject(m_imageButtonUp);
	}
	if (NULL != m_imageButtonDown)
	{
		::DeleteObject(m_imageButtonDown);
	}
	if (NULL != m_imageBitmapNormal)
	{
		::DeleteObject(m_imageButtonDown);
	}
}


BEGIN_MESSAGE_MAP(CPngButton, CBitmapButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CBitmapButtonEx 消息处理程序

BOOL CPngButton::SetButtonUpBitmapEx(const CString& szFilePath)
{
	if (!m_imageButtonUp.IsNull())
	{
		m_imageButtonUp.Destroy();
	}
	m_imageButtonUp.Load(szFilePath);
	if (!m_imageButtonUp.IsNull())
	{
		CTransparentPNG tran;
		tran(&m_imageButtonUp);
	}
	return !m_imageButtonUp.IsNull();
}


BOOL CPngButton::SetButtonNormalBitmapEx(const CString& szFilePath)
{
	if (!m_imageBitmapNormal.IsNull())
	{
		m_imageBitmapNormal.Destroy();
	}
	m_imageBitmapNormal.Load(szFilePath);
	if (!m_imageBitmapNormal.IsNull())
	{
		CTransparentPNG tran;
		tran(&m_imageBitmapNormal);
	}
	return !m_imageBitmapNormal.IsNull();
}

// BOOL CPngButton::SetRedPointImage(const CString& szFilePath)
// {
//     if (!m_imageRedPoint.IsNull())
//     {
//         m_imageRedPoint.Destroy();
//     }
//     m_imageRedPoint.Load(szFilePath);
//     if (!m_imageRedPoint.IsNull())
//     {
//         CTransparentPNG tran;
//         tran(&m_imageRedPoint);
//     }
//     return !m_imageRedPoint.IsNull();
// }
BOOL CPngButton::SetButtonDownBitmapEx(const CString& szFilePath)
{
	if (!m_imageButtonDown.IsNull())
	{
		m_imageButtonDown.Destroy();
	}
	m_imageButtonDown.Load(szFilePath);
	if (!m_imageButtonDown.IsNull())
	{
		CTransparentPNG tran;
		tran(&m_imageButtonDown);
	}
	return !m_imageButtonDown.IsNull();
}

void CPngButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	CRect rect = lpDrawItemStruct->rcItem;

	if (m_first)
	{// 复制背景
		CDialog* pParent = (CDialog*)GetParent();
		CPoint pt(0, 0);
		MapWindowPoints(pParent, &pt, 1);
		CDC * pdc = GetParent()->GetDC();
		m_bkDc.CreateCompatibleDC(pdc);
		CBitmap memBmp;
		memBmp.CreateCompatibleBitmap(pdc, rect.right, rect.bottom);
		m_bkDc.SelectObject(&memBmp);
		m_bkDc.BitBlt(0, 0, rect.right, rect.bottom, pdc, pt.x, pt.y, SRCCOPY);
		ReleaseDC(pdc);
		m_first = false;
	}
	//     CClientDC dc(this);
	//     dc.Rectangle (rect);
		// 背景
	CDC* thisdc = NULL;
	thisdc = GetDC();
	thisdc->BitBlt(0, 0, rect.right, rect.bottom, &m_bkDc, 0/*rect.right*/, 0/*rect.bottom*/, SRCCOPY);

	if (m_lButtonDown)
	{
		if (m_imageButtonDown.IsNull())
		{
			//             CString szLog;
			//             szLog.Format(_T("m_imageButtonDown 未加载背景图片!"));
			//             AppLog(szLog);
		}
		else
		{
			m_imageButtonDown.Draw(thisdc->m_hDC, rect/*m_rectDrawButton*/);
		}
	}
	else
	{
		if (m_bMouseOver)
		{
			if (m_imageButtonUp.IsNull())
			{
				//                 CString szLog;
				//                 szLog.Format(_T("m_imageButtonUp 未加载背景图片!"));
				//                 AppLog(szLog);
			}
			else
			{
				m_imageButtonUp.Draw(thisdc->m_hDC, rect/*m_rectDrawButton*/);
			}
		}
		else
		{
			if (m_imageBitmapNormal.IsNull())
			{
				//                 CString szLog;
				//                 szLog.Format(_T("m_imageBitmapNormal 未加载背景图片!"));
				//                 AppLog(szLog);
			}
			else
			{
				m_imageBitmapNormal.Draw(thisdc->m_hDC, rect/*m_rectDrawButton*/);
			}
		}
	}
	if (0 == this->ReleaseDC(thisdc))
	{
		//         CString szLog;
		//         szLog.Format(_T("ReleaseDC error!"));
		//         AppLog(szLog);
	}
}

void CPngButton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	ModifyStyle(0, WS_CLIPCHILDREN | BS_OWNERDRAW); //设置按钮的有效区域 

//     CRect rect;
//     GetClientRect(&rect);
//     CDialog* pParent=(CDialog*)GetParent();  
//     CPoint pt(rect.left, rect.top);  
//     MapWindowPoints(pParent, &pt, 1);  
//     CDC * pdc = GetParent ()->GetDC ();
//     // 复制背景
//     m_bkDc.CreateCompatibleDC (pdc);
//     CBitmap memBmp;
//     memBmp.CreateCompatibleBitmap(pdc, rect.right, rect.bottom);
//     m_bkDc.SelectObject(&memBmp);
//     m_bkDc.BitBlt (0, 0, rect.right, rect.bottom, pdc, 0, 0, SRCCOPY);
//     ReleaseDC (pdc); 

//     m_btRgn.CreateRectRgnIndirect (rc);
//     SetWindowRgn(m_btRgn, TRUE); 

	CBitmapButton::PreSubclassWindow();
}

void CPngButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_lButtonDown = TRUE;
	CBitmapButton::OnLButtonDown(nFlags, point);
}

void CPngButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_lButtonDown = FALSE;
	CBitmapButton::OnLButtonUp(nFlags, point);
}

BOOL CPngButton::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_MOUSELEAVE)
	{
		m_bTrack = FALSE;
		m_bMouseOver = FALSE;
		InvalidateRect(NULL);
	}
	else if (pMsg->message == WM_MOUSEHOVER)
	{
		m_bMouseOver = TRUE;
		InvalidateRect(NULL);
	}

	return CBitmapButton::PreTranslateMessage(pMsg);
}

void CPngButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (!m_bTrack)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = HOVER_DEFAULT;
		tme.hwndTrack = m_hWnd;

		m_bTrack = _TrackMouseEvent(&tme);
	}

	CBitmapButton::OnMouseMove(nFlags, point);
}


