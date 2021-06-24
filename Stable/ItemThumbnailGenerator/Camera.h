#pragma once

#include "RealSpace2.h"
_USING_NAMESPACE_REALSPACE2
#include "RMeshUtil.h"

// ������ ����
#define DEFAULT_FOV		1.22173048f		// (70.0f / 180.0f * pi)
#define DEFAULT_NEAR_Z	5.0f
#define DEFAULT_FAR_Z	30000.0f	


// ī�޶� ������
struct CameraSetting 
{
	bool bInitialized;
	float m_fDist;
	rvector m_vAt;
	float m_fRotX;
	float m_fRotY;

	CameraSetting() : bInitialized(false) {}
};


// �ӽ÷� ����� ī�޶�

class CTCamera {
public:
	CTCamera() {

		m_rot_x = 0.f;
		m_rot_y = 0.f;
		m_at	= rvector(0.f,0.f,0.f);
		m_dist	= 100.f;

	}

	~CTCamera() {

	}

	void Create(int w,int h) {

		m_dist = 300.f;

		m_at = rvector(0.f,0.f,0.f);//�ٶ󺸴� ��ġ

		RSetCamera(rvector(0.f, 80.f,-m_dist ),m_at ,rvector(0.f,1.f,0.f));

		RSetProjection(DEFAULT_FOV,w/(float)h,DEFAULT_NEAR_Z,DEFAULT_FAR_Z);
	}

	void Render() {

		D3DXMATRIX mat;
		D3DXMatrixTranslation(&mat,m_at.x,m_at.y,m_at.z);

		draw_box(&mat,rvector(5.f,5.f,5.f),rvector(-5.f,-5.f,-5.f),0xffffffff);
	}

	void Update() {

		// ȸ�������� ���� ���͸� �����~
		// dist �� �Ÿ�����

		rvector pos = RealSpace2::RCameraPosition;
		rvector dir = RealSpace2::RCameraDirection;	
		rvector up  = RealSpace2::RCameraUp;

		rvector v = rvector(0.f,0.f,-1.f);

		rmatrix rot = RGetRotX(m_rot_x) * RGetRotY(m_rot_y);

		dir = v * rot;

		D3DXVec3Normalize(&dir,&dir);

		v = dir * m_dist;

		pos = m_at + v;

		RSetCamera(pos,m_at,up);
	}

	void Reset() {

		m_dist = 300.f;

		m_at = rvector(0.f,80.f,0.f);

		m_rot_x = 0.f;
		m_rot_y = 0.f;

		RSetCamera(rvector(0.f, 80.f,-m_dist ),m_at ,rvector(0.f,1.f,0.f));
	}

	void SetCameraSetting(CameraSetting& cs) {

		_ASSERT(cs.bInitialized);
		m_dist = cs.m_fDist;
		m_at = cs.m_vAt;
		m_rot_x = cs.m_fRotX;
		m_rot_y = cs.m_fRotY;

		Update();
	}

	void GetCameraSetting(CameraSetting& cs) {

		cs.m_fDist = m_dist;
		cs.m_vAt = m_at;
		cs.m_fRotX = m_rot_x;
		cs.m_fRotY = m_rot_y;

		cs.bInitialized = true;
	}

	rvector GetPos() {
		return RealSpace2::RCameraPosition;
	}

	rvector GetDir() {
		rvector dir = RealSpace2::RCameraDirection;	
		D3DXVec3Normalize(&dir,&dir);
		return dir;
	}

	rvector GetRight() {

		rvector right;
		rvector dir = RealSpace2::RCameraDirection;
		rvector up = RealSpace2::RCameraUp;

		CrossProduct(&right,dir,up);

		D3DXVec3Normalize(&right,&right);
		return right;
	}

	void Up(float f) {
		m_at.y += f;
	}

	void Down(float f) {
		m_at.y -= f;
	}

	void Front(float f) {
		rvector dir = GetDir();
		m_at += dir * f;

	}

	void Back(float f) {
		rvector dir = GetDir();
		m_at -= dir * f;
	}

	void Left(float f) {
		rvector r = GetRight();
		m_at += r * f;
	}

	void Right(float f) {
		rvector r = GetRight();
		m_at -= r * f;
	}

	void CenterZoomIn(float f) {
		m_dist += f*2;
	}

	void CenterZoomOut(float f) {
		m_dist -= f*2;
	}

	void CenterRotationLeft(float f) {
		m_rot_y -= f;
	}

	void CenterRotationRight(float f) {
		m_rot_y += f;
	}

	void CenterRotationUp(float f) {
		m_rot_x += f;
	}

	void CenterRotationDown(float f) {
		m_rot_x -= f;
	}

	float m_rot_x;
	float m_rot_y;

	rvector m_at;
	float   m_dist;
};