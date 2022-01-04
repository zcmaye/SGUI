#pragma once
using  Uint32 = unsigned int;
class SElapsedTimer
{
public:
	SElapsedTimer();

	void start();		//��ʼ
	void reStart();		//�ؿ�
	void stop();		//ֹͣ
	void pause();		//��ͣ
	void resume();		//��֮ͣ��ָ�

	Uint32  elapsed();	//������SElapsedTimer�ϴ����������ĺ����� 
	bool isStarted();	//�Ƿ�������
	bool isPaused();	//�Ƿ���ͣ��
private:
	Uint32 m_startTicks;	//��ʱ����ʼʱ��ʱ��ʱ��
	Uint32 m_pausedTicks;	//��ʱ��ͣʱ�洢��ʱ��
	
	bool m_paused;			//�Ƿ���ͣ��
	bool m_started;			//�Ƿ�ʼ��
};

