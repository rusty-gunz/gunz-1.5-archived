// GunzItemToolDoc.h : CGunzItemToolDoc Ŭ������ �������̽�
//


#pragma once

class CGunzItemToolDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGunzItemToolDoc();
	DECLARE_DYNCREATE(CGunzItemToolDoc)

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
	virtual ~CGunzItemToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};


