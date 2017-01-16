namespace TimerType
{
	enum CountMode
	{
		COUNTUP   = 0x00000000,
		COUNTDOWN = 0x00000001
	};

	enum Error
	{
		SUCCESS                 = 0x00000000,
		INVALID_STATE           = 0x20000001,
		INIT_FAILED             = 0x20000002,
		START_FAILED            = 0x20000003,
		PAUSE_FAILED            = 0x20000004,
		SET_ONTIME_EVENT_FAILED = 0x20000005,
		SET_PROPERTY_FAILED     = 0x20000006
	};
}
