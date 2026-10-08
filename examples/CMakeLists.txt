# Copyright (c) 2017-2019, Battelle Memorial Institute; Lawrence Livermore National Security, LLC; Alliance for Sustainable Energy, LLC.  See the top-level NOTICE for additional details. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

set(ns3_network_example_libs
    ${libhelics}
    ${libcore}
    ${libpoint-to-point}
    ${libcsma}
    ${libinternet}
    ${libapplications}
)

build_lib_example(
  NAME ns3-filter
  SOURCE_FILES ns3-filter.cc
  LIBRARIES_TO_LINK ${ns3_network_example_libs}
)

build_lib_example(
  NAME new-ns3-filter
  SOURCE_FILES new-ns3-filter.cc
  LIBRARIES_TO_LINK ${ns3_network_example_libs}
)

build_lib_example(
  NAME ns3-sndrcv
  SOURCE_FILES ns3-sndrcv.cc
  LIBRARIES_TO_LINK ${ns3_network_example_libs}
)

build_lib_example(
  NAME helics-example
  SOURCE_FILES helics-example.cc
  LIBRARIES_TO_LINK ${libhelics}
)

build_lib_example(
  NAME fed-filter
  SOURCE_FILES fed-filter.cc
  LIBRARIES_TO_LINK ${libhelics}
)

build_lib_example(
  NAME fed-sndrcv
  SOURCE_FILES fed-sndrcv.cc
  LIBRARIES_TO_LINK ${libhelics}
)

build_lib_example(
  NAME fed-pubsub
  SOURCE_FILES fed-pubsub.cc
  LIBRARIES_TO_LINK ${libhelics}
)
