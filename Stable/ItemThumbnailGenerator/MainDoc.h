// MainDoc.h : CMainDoc Ŭ������ �������̽�
//


#pragma once

class CMainDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMainDoc();
	DECLARE_DYNCREATE(CMainDoc)

// Ư��
public:

// �۾�
public:

// ������
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����
public:
	virtual ~CMainDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};


