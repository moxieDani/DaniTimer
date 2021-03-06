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
        SUCCESS                    = 0x00000000,
        INVALID_STATE              = 0x20000001,
        INIT_FAILED                = 0x20000002,
        START_FAILED               = 0x20000003,
		PAUSE_FAILED               = 0x20000004,
		SET_ONTIME_EVENT_FAILED    = 0x20000005,
		SET_PROPERTY_FAILED        = 0x20000006
    };
	
	enum Property
	{
		TIMER_MODE                  = 0x30000001,
		BEGIN_TIME_MILLI_SECOND     = 0x30000002,
		END_TIME_MILLI_SECOND       = 0x30000003
	};
}
