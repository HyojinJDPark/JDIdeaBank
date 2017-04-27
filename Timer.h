#include<time.h>
#include<signal.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>


#include "MiddleStruct.h"
#include "Singleton.h"

using namespace std;

typedef void(*ft_callback_TimerEnd)(int signo, siginfo_t* info, void* context);

class Timer
{
	
	private:
		ft_callback_TimerEnd ft_TimerCallback;
		timer_t timer_id;
		struct sigevent stSev;
		struct itimerspec stIts;
		struct sigaction sa;
		struct timespec stTimespec;
		int signo;
		bool bTimerExist;
		
	public :
		Timer();
		~Timer();
		int Timer_CreateTimer(ft_callback_TimerEnd a_ftCallback, int);
		int Timer_SetTimer(int sec);
		int Timer_DeleteTimer();
	private :
		int Timer_RegistCallback(ft_callback_TimerEnd a_ftCallback);
		
};
