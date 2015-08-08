#ifndef EVENT_H
#define EVENT_H

/*
###############################################################################
EventType enum definition
###############################################################################
*/

enum EventType
{
	OBSERVER,
	ARRIVAL,
	DEPARTURE
};

/*
###############################################################################
Event class prototype
###############################################################################
*/

class Event
{
public:
	Event(EventType eventType, double time);
	virtual ~Event();
	EventType getEventType();
	double getTime();
	Event* getPreviousEvent();
	Event* getNextEvent();
	void setPreviousEvent(Event* argEvent);
	void setNextEvent(Event* argEvent);
private:
	EventType m_eventType;
	double m_time;
	Event* m_previousEvent;
	Event* m_nextEvent;
};

/*
###############################################################################
EventQueue class prototype
###############################################################################
*/

class EventQueue
{
public:
	EventQueue();
	virtual ~EventQueue();
	void enqueue(Event& argEvent);
	Event* dequeue();
	Event* peekFront();
	Event* peekBack();
	bool isEmpty();
private:
	Event* m_tail;
	Event* m_head;
};

/*
###############################################################################
EventScheduler class prototype
###############################################################################
*/

class EventScheduler
{
public:
	EventScheduler(double T, double lambda, double L, double alpha, double C, int K);
	virtual ~EventScheduler();
	void simulate();
private:
	double m_T;
	double m_lambda;
	double m_L;
	double m_alpha;
	double m_C;
	double m_previousObserverTime;
	double m_previousArrivalTime;
	double m_previousDepartureTime;
	int m_K;
	int m_No;
	int m_Na;
	int m_Nd;
	int m_Ni;
	int m_Nl;
	long int m_aggregateBufferedPackets;
	EventQueue* m_observerEventQueue;
	EventQueue* m_arrivalEventQueue;
	EventQueue* m_departureEventQueue;
	void generateObserverEvents();
	void generateArrivalEvents();
	void observerEventHandler(Event& observerEvent);
	void arrivalEventHandler(Event& arrivalEvent);
	void departureEventHandler(Event& departureEvent);
	void benchmark();
	Event* getFirstEvent(Event* observerEvent, Event* arrivalEvent, Event* departureEvent);
};

#endif // EVENT_H
