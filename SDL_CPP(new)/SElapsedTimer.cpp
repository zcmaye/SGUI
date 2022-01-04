#include "SElapsedTimer.h"
#include"Configure.h"
SElapsedTimer::SElapsedTimer()
    : m_startTicks(0)
    , m_pausedTicks(0)
    , m_paused(false)
    , m_started(false)
{
}

void SElapsedTimer::start()
{
    m_started = true;
    m_paused = false;

    //��ȡ��ǰʱ��ʱ��
    m_startTicks = SDL_GetTicks();
    m_pausedTicks = 0;
}

void SElapsedTimer::reStart()
{
}

void SElapsedTimer::stop()
{
    //ֹͣ��ʱ��
    m_started = false;
    m_paused = false;

    m_startTicks = 0;
    m_pausedTicks = 0;
}

void SElapsedTimer::pause()
{
    //�����ʱ���������У����һ�û����ͣ
    if (m_started && !m_paused)
    {
        m_paused = true;    //��ͣ��ʱ��

        //������ͣ�Ŀ̶�(��ǰʱ�� - ��ʼʱ��==�����೤ʱ��)
        m_pausedTicks = SDL_GetTicks() - m_startTicks;
        m_startTicks = 0;   //���ÿ�ʼ��ʱ��
    }
}

void SElapsedTimer::resume()
{
    //�����ʱ���������в���ͣ��
    if (m_started && m_paused)
    {
        //ȡ����ͣ
        m_paused = false;

        //���迪ʼʱ��
        m_startTicks = SDL_GetTicks() - m_pausedTicks;
        
        //������ͣʱ��
        m_pausedTicks = 0;
    }
}

Uint32 SElapsedTimer::elapsed()
{
    //���������������
    if (m_started)
    {
        //�����ʱ������ͣ
        if (m_paused)
        {
            return m_pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - m_startTicks;
        }
    }

    return 0;
}

bool SElapsedTimer::isStarted()
{
    return m_started;
}

bool SElapsedTimer::isPaused()
{
    return m_paused;
}
