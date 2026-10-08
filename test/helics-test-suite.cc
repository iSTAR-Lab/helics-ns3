/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
Copyright (c) 2017-2019, Battelle Memorial Institute; Lawrence Livermore National Security, LLC; Alliance for Sustainable Energy, LLC.  See the top-level NOTICE for additional details. All rights reserved.

SPDX-License-Identifier: BSD-3-Clause
*/

#include "ns3/helics.h"
#include "ns3/helics-id-tag.h"

#include "ns3/packet.h"
#include "ns3/test.h"

// Do not put your test classes in namespace ns3.  You may find it useful
// to use the using directive to access the ns3 namespace directly
using namespace ns3;

/**
 * @ingroup tests
 *
 * Check that a HelicsIdTag survives being attached to and read back from a packet.
 */
class HelicsIdTagTestCase : public TestCase
{
public:
  HelicsIdTagTestCase ();

private:
  void DoRun (void) override;
};

HelicsIdTagTestCase::HelicsIdTagTestCase ()
  : TestCase ("HelicsIdTag packet tag round trip")
{
}

void
HelicsIdTagTestCase::DoRun (void)
{
  Ptr<Packet> p = Create<Packet> (10);
  p->AddPacketTag (HelicsIdTag (42));

  HelicsIdTag tag;
  NS_TEST_ASSERT_MSG_EQ (p->PeekPacketTag (tag), true, "HelicsIdTag not found on packet");
  NS_TEST_ASSERT_MSG_EQ (tag.GetHelicsId (), 42U, "HelicsIdTag id changed");
  NS_TEST_ASSERT_MSG_EQ (static_cast<uint32_t> (tag), 42U, "HelicsIdTag conversion operator mismatch");
  NS_TEST_ASSERT_MSG_EQ (tag.GetSerializedSize (), 4U, "Unexpected HelicsIdTag serialized size");
}

/**
 * @ingroup tests
 *
 * HELICS module test suite.
 */
class HelicsTestSuite : public TestSuite
{
public:
  HelicsTestSuite ();
};

HelicsTestSuite::HelicsTestSuite ()
  : TestSuite ("helics", Type::UNIT)
{
  AddTestCase (new HelicsIdTagTestCase, TestCase::Duration::QUICK);
}

static HelicsTestSuite helicsTestSuite; ///< Static variable for test initialization

