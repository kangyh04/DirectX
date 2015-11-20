#include "Bone.h"

Bone::Bone(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh) : Node(pDev, pMesh){
	m_nNodeType = NODE_BONE;
	D3DXMatrixIdentity(&m_matSkin.matrix);
}
Bone::~Bone(){}
//DMatrix* Bone::Animate(float frame, DMatrix* pParent, DTrack* pTrack){
//	DMatrix* pMatAni;
//	DMatrix mWI;		// world inverse;
//
//	// �ִϸ��̼� ����� �����.
//	pMatAni = pTrack->Animate(frame);
//	m_matTM = m_matLocal * *pMatAni;
//
//	// ���� posŰ���� ������ local TM�� ��ǥ�� ����Ѵ�.
//	if (pMatAni->matrix._41 == 0.0f && pMatAni->matrix._42 == 0.0f && pMatAni->matrix._43 == 0.0f){
//		m_matTM.matrix._41 = m_matLocal.matrix._41;
//		m_matTM.matrix._42 = m_matLocal.matrix._42;
//		m_matTM.matrix._43 = m_matLocal.matrix._43;
//	}
//	else{ // pos Ű���� ��ǥ������ �����Ѵ�.(�̷��� ���� ������ TM�� pos������ �ι�����ȴ�.)
//		m_matTM.matrix._41 = pMatAni->matrix._41;
//		m_matTM.matrix._42 = pMatAni->matrix._42;
//		m_matTM.matrix._43 = pMatAni->matrix._43;
//	}
//
//	m_matTM = m_matTM * *pParent;
//
//	// mWI = inverse(m_matWorld)
//	D3DXMatrixInverse(&mWI.matrix, NULL, &m_matWorld.matrix);
//	// skin = inverse(m_world) * m_ani * m_parent;
//	m_matSkin = mWI * m_matTM;
//	return &m_matSkin;
//}
DMatrix& Bone::Animate(DMatrix* pParentTM, DTrack* pTrack, float fFrame){
	DMatrix mWI;
	DMatrix* pMatAni;

	pMatAni = pTrack->Animate(fFrame);
	m_matTM = m_matLocal * *pMatAni;

	if (pMatAni->matrix._41 == 0.0f && pMatAni->matrix._42 == 0.0f && pMatAni->matrix._43 == 0.0f){
		m_matTM.matrix._41 = m_matLocal.matrix._41;
		m_matTM.matrix._42 = m_matLocal.matrix._42;
		m_matTM.matrix._43 = m_matLocal.matrix._43;
	}
	else{ 
		m_matTM.matrix._41 = pMatAni->matrix._41;
		m_matTM.matrix._42 = pMatAni->matrix._42;
		m_matTM.matrix._43 = pMatAni->matrix._43;
	}

	m_matTM = m_matTM * *pParentTM;

	D3DXMatrixInverse(&mWI.matrix, NULL, &m_matWorld.matrix);
	m_matSkin = mWI * m_matTM;
	return m_matSkin;
}
DMatrix& Bone::Animate(DMatrix* pParentTM, DTrack* pTrack1, DTrack* pTrack2, float fFrame1, float fFrame2, float blendFrame){
	DMatrix mWI;
	DMatrix* pMatAni;

	pMatAni = pTrack1->BlendAnimate(pTrack2, fFrame1, fFrame2, blendFrame);
	m_matTM = m_matLocal * *pMatAni;

	if (pMatAni->matrix._41 == 0.0f && pMatAni->matrix._42 == 0.0f && pMatAni->matrix._43 == 0.0f){
		m_matTM.matrix._41 = m_matLocal.matrix._41;
		m_matTM.matrix._42 = m_matLocal.matrix._42;
		m_matTM.matrix._43 = m_matLocal.matrix._43;
	}
	else{
		m_matTM.matrix._41 = pMatAni->matrix._41;
		m_matTM.matrix._42 = pMatAni->matrix._42;
		m_matTM.matrix._43 = pMatAni->matrix._43;
	}

	m_matTM = m_matTM * *pParentTM;

	D3DXMatrixInverse(&mWI.matrix, NULL, &m_matWorld.matrix);
	m_matSkin = mWI * m_matTM;
	return m_matSkin;
}
DMatrix& Bone::Animate(DMatrix* pParentTM, DMatrix* pTrackMat){
	DMatrix mWI;
	m_matTM = m_matLocal * *pTrackMat;

	// ���� posŰ���� ������ local TM�� ��ǥ�� ����Ѵ�.
	if (pTrackMat->matrix._41 == 0.0f && pTrackMat->matrix._42 == 0.0f && pTrackMat->matrix._43 == 0.0f){
		m_matTM.matrix._41 = m_matLocal.matrix._41;
		m_matTM.matrix._42 = m_matLocal.matrix._42;
		m_matTM.matrix._43 = m_matLocal.matrix._43;
	}
	else{ // pos Ű���� ��ǥ������ �����Ѵ�.(�̷��� ���� ������ TM�� pos������ �ι�����ȴ�.)
		m_matTM.matrix._41 = pTrackMat->matrix._41;
		m_matTM.matrix._42 = pTrackMat->matrix._42;
		m_matTM.matrix._43 = pTrackMat->matrix._43;
	}

	m_matTM = m_matTM * *pParentTM;

	// mWI = inverse(m_matWorld)
	D3DXMatrixInverse(&mWI.matrix, NULL, &m_matWorld.matrix);
	// skin = inverse(m_world) * m_ani * m_parent;
	m_matSkin = mWI * m_matTM;
	return m_matSkin;
}

int Bone::Draw(DMatrix* pTM){
	BoxVertex vtx[8];
	vtx[0] = BoxVertex(-1,  1,  1, 0xffff0000);
	vtx[1] = BoxVertex( 1,  1,  1, 0xffff0000);
	vtx[2] = BoxVertex( 1,  1, -1, 0xffff0000);
	vtx[3] = BoxVertex(-1,  1, -1, 0xffff0000);
	vtx[4] = BoxVertex(-1, -1,  1, 0xffff0000);
	vtx[5] = BoxVertex( 1, -1,  1, 0xffff0000);
	vtx[6] = BoxVertex( 1, -1, -1, 0xffff0000);
	vtx[7] = BoxVertex(-1, -1, -1, 0xffff0000);

	Index3w idx[12] = {
		{ 0, 1, 2 }, { 0, 2, 3 },	/// ����
		{ 4, 6, 5 }, { 4, 7, 6 },	/// �Ʒ���
		{ 0, 3, 7 }, { 0, 7, 4 },	/// �޸�
		{ 1, 5, 6 }, { 1, 6, 2 },	/// ������
		{ 3, 2, 6 }, { 3, 6, 7 },	/// �ո�
		{ 0, 4, 5 }, { 0, 5, 1 },	/// �޸�
	};

	m_pDev->MultiplyTransform(D3DTS_WORLD, &m_matTM.matrix);
	m_pDev->SetFVF(BoxVertex::FVF);
	m_pDev->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 8, 12, idx, D3DFMT_INDEX16, vtx, sizeof(BoxVertex));

	return 1;
}