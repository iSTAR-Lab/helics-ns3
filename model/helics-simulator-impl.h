/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

#ifndef HELICS_SIMULATOR_IMPL_H
#define HELICS_SIMULATOR_IMPL_H

#include "ns3/simulator-impl.h"
#include "ns3/scheduler.h"
#include "ns3/event-impl.h"

#include "ns3/ptr.h"

#include <list>
#include <mutex>
#include <thread>

/**
 * \file
 * \ingroup simulator
 * ns3::HelicsSimulatorImpl declaration.
 */

namespace ns3 {

/**
 * \ingroup simulator
 *
 * A single process simulator implementation that synchronizes its
 * time advancement with a HELICS co-simulation.
 */
class HelicsSimulatorImpl : public SimulatorImpl
{
public:
  /**
   *  Register this type.
   *  \return The object TypeId.
   */
  static TypeId GetTypeId (void);

  /** Constructor. */
  HelicsSimulatorImpl ();
  /** Destructor. */
  ~HelicsSimulatorImpl () override;

  // Inherited
  void Destroy () override;
  bool IsFinished (void) const override;
  void Stop (void) override;
  EventId Stop (const Time &delay) override;
  EventId Schedule (const Time &delay, EventImpl *event) override;
  void ScheduleWithContext (uint32_t context, const Time &delay, EventImpl *event) override;
  EventId ScheduleNow (EventImpl *event) override;
  EventId ScheduleDestroy (EventImpl *event) override;
  void Remove (const EventId &id) override;
  void Cancel (const EventId &id) override;
  bool IsExpired (const EventId &id) const override;
  void Run (void) override;
  Time Now (void) const override;
  Time GetDelayLeft (const EventId &id) const override;
  Time GetMaximumSimulationTime (void) const override;
  void SetScheduler (ObjectFactory schedulerFactory) override;
  uint32_t GetSystemId (void) const override;
  uint32_t GetContext (void) const override;
  uint64_t GetEventCount (void) const override;

  /**
   * Get the timestamp of the next event.
   * @return the time of the next event, or the maximum simulation time
   *         if there are no events.
   */
  Time Next (void) const;

private:
  void DoDispose (void) override;

  /** Process the next event. */
  void ProcessOneEvent (void);
  /** Move events from a different context into the main event queue. */
  void ProcessEventsWithContext (void);
 
  /** Wrap an event with its execution context. */
  struct EventWithContext {
    /** The event context. */
    uint32_t context;
    /** Event timestamp. */
    uint64_t timestamp;
    /** The event implementation. */
    EventImpl *event;
  };
  /** Container type for the events from a different context. */
  typedef std::list<EventWithContext> EventsWithContext;
  /** The container of events from a different context. */
  EventsWithContext m_eventsWithContext;
  /**
   * Flag \c true if all events with context have been moved to the
   * primary event queue.
   */
  bool m_eventsWithContextEmpty;
  /** Mutex to control access to the list of events with context. */
  std::mutex m_eventsWithContextMutex;

  /** Container type for the events to run at Simulator::Destroy() */
  typedef std::list<EventId> DestroyEvents;
  /** The container of events to run at Destroy. */
  DestroyEvents m_destroyEvents;
  /** Flag calling for the end of the simulation. */
  bool m_stop;
  /** The event priority queue. */
  Ptr<Scheduler> m_events;

  /** Next event unique id. */
  uint32_t m_uid;
  /** Unique id of the current event. */
  uint32_t m_currentUid;
  /** Timestamp of the current event. */
  uint64_t m_currentTs;
  /** Execution context of the current event. */
  uint32_t m_currentContext;
  /** The event count. */
  uint64_t m_eventCount;
  /**
   * Number of events that have been inserted but not yet scheduled,
   *  not counting the Destroy events; this is used for validation
   */
  int m_unscheduledEvents;

  /** Main execution thread. */
  std::thread::id m_mainThreadId;
};

} // namespace ns3

#endif /* HELICS_SIMULATOR_IMPL_H */
