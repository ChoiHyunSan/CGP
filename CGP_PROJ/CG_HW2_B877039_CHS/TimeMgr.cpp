#include "pch.h"
#include "TimeMgr.h"
#include "systemclass.h"
#include "windows.h"

TimeMgr::TimeMgr() :
	m_llCurCount({}),
	m_llFrequency({}),
	m_llPrevCount({}),
	m_iCallCount(0),
	m_dDT(.0),
	m_dAcc(0),
	m_iFPS(0)
{

}

TimeMgr::~TimeMgr()
{

}

void TimeMgr::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// ���� ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_llPrevCount = m_llCurCount;
}

void TimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT; // DT ����

	if (m_dAcc > 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0;

		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d , DT : %f \n", m_iFPS, m_dDT);
		OutputDebugStringW(szBuffer);
	}
}
