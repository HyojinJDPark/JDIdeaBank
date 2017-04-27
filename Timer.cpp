#include "Timer.h"

Timer::Timer()
{
	bTimerExist = TIMER_NO_EXIST;
}

Timer::~Timer()
{
	Timer_DeleteTimer();
}

int Timer::Timer_RegistCallback(ft_callback_TimerEnd a_ftCallback)
{
	DPRINTF_TIMER("[Timer_RegistCallback] - START\n");
	ft_TimerCallback = a_ftCallback;
	sa.sa_flags = SA_SIGINFO;
	// sa.sa_handler = ;     /* Only one can be choosen between sa_sigaction and sa_handler */
	sa.sa_sigaction = ft_TimerCallback;

	DPRINTF_TIMER("[Timer_RegistCallback] - ft_TimerCallback : %p\n",ft_TimerCallback);
	sigemptyset(&sa.sa_mask);
	
	if(sigaction(signo, &sa, NULL) == -1)
	{
		DPRINTF_TIMER("[Timer_RegistCallback] - sigaction Err\n");
		return TIMER_RETURN_ERR;
	}
	
	DPRINTF_TIMER("[Timer_RegistCallback] - END\n");
	return TIMER_RETURN;
}

int Timer::Timer_CreateTimer(ft_callback_TimerEnd a_ftCallback,int sig_signo)		// a_ftCallback is Timer callback
{
	DPRINTF_TIMER("[Timer_CreateTimer] - START\n");
	if(bTimerExist == TIMER_EXIST)
	{
		DPRINTF_TIMER("[Timer_CreateTimer] - Timer Exists\n");
		return TIMER_RETURN;
	}
	if(a_ftCallback == NULL)
	{
		DPRINTF_TIMER("[Timer_CreateTimer] - regist function must be existed\n");
		return TIMER_RETURN;
	}
	
	signo = sig_signo;
	
	if(Timer_RegistCallback(a_ftCallback) == TIMER_RETURN_ERR)
	{

		DPRINTF_TIMER("[Timer_CreateTimer] - Timer RegistCallback Err\n");
		return TIMER_RETURN_ERR;
	}
	
	stSev.sigev_notify = SIGEV_SIGNAL;
	stSev.sigev_signo = signo;
	
	if(timer_create(CLOCK_REALTIME, &stSev,&timer_id) == -1)
	{
		DPRINTF_TIMER("[Timer_CreateTimer] - timer create Err\n");
		return TIMER_RETURN_ERR;
	}
	
	bTimerExist = TIMER_EXIST;
	
	DPRINTF_TIMER("[Timer_CreateTimer] - END\n");
	return TIMER_RETURN;
}

int Timer::Timer_SetTimer(int sec)
{
	if(bTimerExist == TIMER_NO_EXIST)
	{
		DPRINTF_TIMER("[Timer_SetTimer] - Timer no exist\n");
		return TIMER_RETURN_ERR;
	}
	DPRINTF_TIMER("[Timer_SetTimer] - START\n");
	
	stIts.it_value.tv_sec = sec;
	stIts.it_value.tv_nsec = 0;
	
	timer_settime(timer_id,	0, &stIts,NULL);
	
	DPRINTF_TIMER("[Timer_SetTimer] - END\n");
	return TIMER_RETURN;
}

int Timer::Timer_DeleteTimer()
{
	DPRINTF_TIMER("[Timer_DeleteTimer] - START\n");
	if(bTimerExist == TIMER_NO_EXIST)
	{
		DPRINTF_TIMER("[Timer_DeleteTimer] - Timer no exist\n");
		return TIMER_RETURN;
	}
	
	timer_delete(timer_id);
	bTimerExist = TIMER_NO_EXIST;
	
	DPRINTF_TIMER("[Timer_DeleteTimer] - END\n");
	return TIMER_RETURN;
}
