#pragma once
#include <thread>	//	std::thread

using std::chrono::milliseconds;
using std::thread;

class TimedEvent
{
protected:
	milliseconds IntervalTime;
	thread TimedThread;
	bool Running;
	bool Abort;

private:
	
	//	Virtual 'OnTick' function.
	//	Called every interval.
	inline virtual void OnTick() = 0;

public:

	//	Manually start the timer.
	inline void StartTimer() { Running = true; }
	//	Manually stop the timer.
	inline void StopTimer() { Running = false; }
	//	Check if the timer is running.
	inline const bool TimerRunning() const { return Running; }

	//	TODO:
	//	This only takes effect after the thread wakes from its curent 'sleep_for'.
	//	Change design to eliminate 'sleep_for' and move to something like 'condition_variable'.
	inline void SetInterval(milliseconds NewInterval) { IntervalTime = NewInterval; }

	//	Constructor
	//	const std::chrono::milliseconds Interval = Initial interval in milliseconds.
	//	const bool StartRunning = If the timer starts immediatly after it is constructed.
	inline TimedEvent(const milliseconds Interval, const bool StartRunning = false) :
		IntervalTime(Interval), Running(StartRunning), Abort(false),
		TimedThread([&]() {

		//	TODO:
		//	Find cross-platform methods of controlling thread priority.
		//	Make sure this thread uses the least amount of resources possible.
		//SetPriorityClass(GetCurrentThread(), IDLE_PRIORITY_CLASS);
		//SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);
		
		while (!Abort)
		{
			if (Running)
			{
				OnTick();
			}
			//	TODO:
			//	Get rid of this, it's horrible.
			std::this_thread::sleep_for(IntervalTime);
		}}) {}

		//	Destructor
		inline virtual ~TimedEvent()
		{
			//	Signal our thread to abort its loop.
			Abort = true;
			//	Shut the thread down.
			TimedThread.join();
		}
};
