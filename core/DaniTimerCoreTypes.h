typedef std::function<int(unsigned long)> DaniTimerCoreCallbackFunc;

namespace TimerCore
{
	enum CountMode
	{
		COUNTUP   = 0x00000000,
		COUNTDOWN = 0x00000001
	};
    
    enum CurrentState
    {
        READY    = 0x10000000,
        PROGRESS = 0x10000001,
        PAUSE    = 0x10000002,
        STOP     = 0x10000003
    };
    
    enum Error
    {
        SUCCESS                  = 0x00000000,
        INVALID_STATE            = 0x20000001,
        INIT_FAILED              = 0x20000002,
        START_FAILED             = 0x20000003,
        REGISTER_CALLBACK_FAILED = 0x20000004        
    };
}
