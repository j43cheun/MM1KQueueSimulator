#include "Event.h"
#include <cstddef>
#include "Random.h"
#include "time.h"
#include <iostream>;
#include "Log.h"
#include <iomanip>
#include <cmath>

/*
###############################################################################
Event class definition
###############################################################################
*/

Event::Event(EventType eventType, double time)
{
	m_eventType = eventType;
	m_time = time;
	m_previousEvent = NULL;
	m_nextEvent = NULL;
}

Event::~Event()
{
	// Empty destructor.
}

EventType Event::getEventType()
{
	return m_eventType;
}

double Event::getTime()
{
	return m_time;
}

Event* Event::getPreviousEvent()
{
	return m_previousEvent;
}

Event* Event::getNextEvent()
{
	return m_nextEvent;
}

void Event::setPreviousEvent(Event* argEvent)
{
	m_previousEvent = argEvent;
}

void Event::setNextEvent(Event* argEvent)
{
	m_nextEvent = argEvent;
}

/*
###############################################################################
EventQueue class definition
###############################################################################
*/

EventQueue::EventQueue()
{
	m_tail = NULL;
	m_head = NULL;
}

EventQueue::~EventQueue()
{
	while (m_tail != NULL)
	{
		Event* tmp = m_tail;
		m_tail = m_tail->getPreviousEvent();
		tmp->setPreviousEvent(NULL);
		tmp->setNextEvent(NULL);
		delete tmp;
	}
}

void EventQueue::enqueue(Event& argEvent)
{
	if (isEmpty())
	{
		m_tail = &argEvent;
		m_tail->setPreviousEvent(NULL);
		m_tail->setNextEvent(NULL);
		m_head = m_tail;
	}
	else
	{
		Event* tmp = m_tail;
		m_tail = &argEvent;
		m_tail->setPreviousEvent(tmp);
		m_tail->setNextEvent(NULL);
		tmp->setNextEvent(m_tail);
	}
}

Event* EventQueue::dequeue()
{
	Event* tmp = NULL;
	if (m_head != NULL)
	{
		tmp = m_head;
		if (m_head == m_tail)
		{
			m_tail = NULL;
			m_head = NULL;
		}
		else
		{
			m_head = m_head->getNextEvent();
			m_head->setPreviousEvent(NULL);
		} 0;
		tmp->setPreviousEvent(NULL);
		tmp->setNextEvent(NULL);
	}
	return tmp;
}

Event* EventQueue::peekFront()
{
	return m_head;
}

Event* EventQueue::peekBack()
{
	return m_tail;
}

bool EventQueue::isEmpty()
{
	return (m_tail == NULL && m_head == NULL);
}

/*
###############################################################################
EventScheduler class definition
###############################################################################
*/

EventScheduler::EventScheduler(double T, double lambda, double L, double alpha, double C, int K)
{
	m_T = T;
	m_lambda = lambda;
	m_L = L;
	m_alpha = alpha;
	m_C = C;
	m_K = K;
	m_No = 0;
	m_Na = 0;
	m_Nd = 0;
	m_Ni = 0;
	m_Nl = 0;
	m_previousObserverTime = 0;
	m_previousArrivalTime = 0;
	m_previousDepartureTime = -1.0;
	m_aggregateBufferedPackets = 0;
	m_observerEventQueue = new EventQueue();
	m_arrivalEventQueue = new EventQueue();
	m_departureEventQueue = new EventQueue();
	seed(static_cast<int>(time(NULL)));
}

EventScheduler::~EventScheduler()
{
	delete m_observerEventQueue;
	delete m_arrivalEventQueue;
	delete m_departureEventQueue;
}

void EventScheduler::generateObserverEvents()
{
	if (m_previousObserverTime <= m_T)
	{
		m_previousObserverTime += generateExponentialRandomVariable(m_alpha);
		Event* observerEvent = new Event(OBSERVER, m_previousObserverTime);
		m_observerEventQueue->enqueue(*observerEvent);
	}
}

void EventScheduler::generateArrivalEvents()
{
	if (m_previousArrivalTime <= m_T)
	{
		m_previousArrivalTime += generateExponentialRandomVariable(m_lambda);
		Event* arrivalEvent = new Event(ARRIVAL, m_previousArrivalTime);
		m_arrivalEventQueue->enqueue(*arrivalEvent);
	}
}

void EventScheduler::observerEventHandler(Event& observerEvent)
{
	int bufferedPackets = m_Na - m_Nd - m_Nl;
	m_No++;
	m_aggregateBufferedPackets += bufferedPackets;
	if (bufferedPackets == 0)
	{
		m_Ni++;
	}
	delete &observerEvent;
}

void EventScheduler::arrivalEventHandler(Event& arrivalEvent)
{
	int bufferedPackets = m_Na - m_Nd - m_Nl;
	if (m_K < 0 || !(m_Na >= m_Nd + m_Nl + m_K))
	{
		long int packetLength = ceil(generateExponentialRandomVariable(1.0 / m_L));
		double transmissionDelay = static_cast<long double>(packetLength) / m_C;
		double departureTime;
		if (bufferedPackets == 0 || m_previousDepartureTime < 0)
		{
			departureTime = arrivalEvent.getTime() + transmissionDelay;
		}
		else
		{
			departureTime = m_previousDepartureTime + transmissionDelay;
		}
		Event* departureEvent = new Event(DEPARTURE, departureTime);
		m_previousDepartureTime = departureTime;
		m_departureEventQueue->enqueue(*departureEvent);
	}
	else
	{
		m_Nl++;
	}
	m_Na++;
	delete &arrivalEvent;
}

void EventScheduler::departureEventHandler(Event& departureEvent)
{
	m_Nd++;
	delete &departureEvent;
}

Event* EventScheduler::getFirstEvent(Event* observerEvent, Event* arrivalEvent, Event* departureEvent)
{
	Event* firstEvent = NULL;
	if (observerEvent != NULL && arrivalEvent != NULL && departureEvent != NULL)
	{
		if (observerEvent->getTime() < arrivalEvent->getTime() && observerEvent->getTime() < departureEvent->getTime())
		{
			firstEvent = observerEvent;
		}
		else if (arrivalEvent->getTime() < observerEvent->getTime() && arrivalEvent->getTime() < departureEvent->getTime())
		{
			firstEvent = arrivalEvent;
		}
		else
		{
			firstEvent = departureEvent;
		}
	}
	else if (observerEvent != NULL && arrivalEvent != NULL)
	{
		if (observerEvent->getTime() < arrivalEvent->getTime())
		{
			firstEvent = observerEvent;
		}
		else
		{
			firstEvent = arrivalEvent;
		}
	}
	else if (observerEvent != NULL && departureEvent != NULL)
	{
		if (observerEvent->getTime() < departureEvent->getTime())
		{
			firstEvent = observerEvent;
		}
		else
		{
			firstEvent = departureEvent;
		}
	}
	else if (arrivalEvent != NULL && departureEvent != NULL)
	{
		if (arrivalEvent->getTime() < departureEvent->getTime())
		{
			firstEvent = arrivalEvent;
		}
		else
		{
			firstEvent = departureEvent;
		}
	}
	else if (observerEvent != NULL)
	{
		firstEvent = observerEvent;
	}
	else if (arrivalEvent != NULL)
	{
		firstEvent = arrivalEvent;
	}
	else if (departureEvent != NULL)
	{
		firstEvent = departureEvent;
	}
	return firstEvent;
}

void EventScheduler::benchmark()
{
	const double rho = m_L * m_lambda / m_C;
	const double avgBufferedPackets = static_cast<long double>(m_aggregateBufferedPackets) / static_cast<double>(m_No);
	const double pIdle = static_cast<double>(m_Ni) / static_cast<double>(m_No);
	const double pLoss = static_cast<double>(m_Nl) / static_cast<double>(m_Na);

	std::cout << "m_aggregateBufferedPackets  = " << m_aggregateBufferedPackets << "\n";
	std::cout << "m_No  = " << m_No << "\n";
	std::cout << "m_Ni  = " << m_Ni << "\n";
	std::cout << "m_Nl  = " << m_Nl << "\n";
	std::cout << "m_Na  = " << m_Na << "\n";
	std::cout << "m_Nd  = " << m_Nd << "\n";
	std::cout << "E[N]   = " << avgBufferedPackets << "\n";
	std::cout << "Pidle  = " << pIdle << "\n";
	std::cout << "Ploss  = " << pLoss << "\n";

	const int cardinality = 6;
	double values[cardinality];
	values[0] = rho;
	values[1] = m_lambda;
	values[2] = m_alpha;
	values[3] = avgBufferedPackets;
	values[4] = pIdle;
	values[5] = pLoss;
	Logger::getInstance()->csvLog(values, cardinality);
}

void EventScheduler::simulate()
{
	generateObserverEvents();
	generateArrivalEvents();
	
	while (!m_observerEventQueue->isEmpty() || !m_arrivalEventQueue->isEmpty() || !m_departureEventQueue->isEmpty())
	{
		Event* firstEvent = getFirstEvent(m_observerEventQueue->peekFront(), m_arrivalEventQueue->peekFront(), m_departureEventQueue->peekFront());

		if (firstEvent != NULL)
		{
			switch (firstEvent->getEventType())
			{
			case OBSERVER:
				m_observerEventQueue->dequeue();
				observerEventHandler(*firstEvent);
				break;
			case ARRIVAL:
				m_arrivalEventQueue->dequeue();
				arrivalEventHandler(*firstEvent);
				break;
			case DEPARTURE:
				m_departureEventQueue->dequeue();
				departureEventHandler(*firstEvent);
				break;
			default:
				break;
			}
		}
		
		generateObserverEvents();
		generateArrivalEvents();
	}
	benchmark();
}

