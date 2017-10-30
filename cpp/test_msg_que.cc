//#include "DataType.h"
#include <time.h>
#include <deque>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <assert.h>


typedef unsigned int PARAM;
typedef unsigned int DWORD;

typedef struct tagMSG
{
	DWORD		msg;
	PARAM		wpa;
	PARAM		lpa;
	DWORD		time;
}MSG;

typedef std::deque<MSG> MSGQUEUE;

class CMsgQue
{
public:
	CMsgQue(int size = 1024);
	virtual ~CMsgQue();

	int SendMessage (DWORD msg, PARAM wpa = 0, PARAM lpa = 0);
	int RecvMessage (MSG *pMsg);
	void ClearMessage();

protected:
private:
	MSGQUEUE m_Queue;
	pthread_mutex_t m_Mutex;
	sem_t m_Semaphore;
	int m_nMaxMsg;
	int m_nMsg;
};

CMsgQue::CMsgQue(int size)
	: m_nMaxMsg(size), m_nMsg(0)
{
	pthread_mutex_init(&m_Mutex, NULL);
	sem_init(&m_Semaphore, 0, 0);
}

CMsgQue::~CMsgQue()
{
	sem_destroy(&m_Semaphore);
	pthread_mutex_destroy(&m_Mutex);
}

int CMsgQue::SendMessage(DWORD msg, PARAM wpa/* = 0 */, PARAM lpa/* = 0 */)
{
	MSG m = {msg, wpa, lpa, ::time(NULL)};
	//printf("send msg -- msg: %u, wpa: %u, lpa: %u\n", m.msg, m.wpa, m.lpa);
	pthread_mutex_lock(&m_Mutex);
	if ((1 + m_nMsg) > m_nMaxMsg) {
		pthread_mutex_unlock(&m_Mutex);
		return -1;
	}
	m_Queue.push_back(m);
	MSG* pMsg = &m_Queue.front();
	m_nMsg++;
	pthread_mutex_unlock(&m_Mutex);
	sem_post(&m_Semaphore);
	return 0;
}

int CMsgQue::RecvMessage(MSG *pMsg)
{
	if (!pMsg) return -2;
	sem_wait(&m_Semaphore);
	pthread_mutex_lock(&m_Mutex);
	if (m_Queue.size() <= 0) {
		pthread_mutex_unlock(&m_Mutex);
		return -1;
	}
	m_nMsg--;
	*pMsg = m_Queue.front();
	//printf("recv -- msg: %u, wpa: %u, lpa: %u\n", pMsg->msg, pMsg->wpa, pMsg->lpa);
	m_Queue.pop_front();
	pthread_mutex_unlock(&m_Mutex);
	return 0;
}

void CMsgQue::ClearMessage()
{
	pthread_mutex_lock(&m_Mutex);
	m_Queue.clear();
	pthread_mutex_unlock(&m_Mutex);
}

CMsgQue g_cMsgQue;

void* ThreadProc(void*)
{
	MSG msg;
	while (1) {
		g_cMsgQue.RecvMessage(&msg);
		if (msg.msg == 0) {
			break ;
		}
	};
}

#include <unistd.h>

void* SendRoutine(void*)
{
	MSG msg;
	int count = 10;
	while (count--) {
		g_cMsgQue.SendMessage(1, 2, 4);
		::usleep(20000);
	}
	g_cMsgQue.SendMessage(0);
}

int main()
{
	pthread_t tid;
	pthread_t tid2;
	pthread_create(&tid, 0, &ThreadProc, NULL);
	pthread_create(&tid2, 0, &SendRoutine, NULL);
	int count = 10;
	while (count--) {
		g_cMsgQue.SendMessage(2, 4, 6);
		::usleep(12000);
	}
	pthread_join(tid, 0);
	pthread_join(tid2, 0);

	return 0;
}
