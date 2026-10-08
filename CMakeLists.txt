# Copyright (c) 2017-2019, Battelle Memorial Institute; Lawrence Livermore National Security, LLC; Alliance for Sustainable Energy, LLC.  See the top-level NOTICE for additional details. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

# HELICS install location; it can also be given with HELICS_DIR or
# CMAKE_PREFIX_PATH
set(NS3_WITH_HELICS
    ""
    CACHE PATH
          "Installation prefix of HELICS 3 for the helics module"
)

find_package(
  HELICS
  3
  QUIET
  HINTS
  ${NS3_WITH_HELICS}
)

if((NOT
    HELICS_FOUND)
   OR (NOT
       TARGET
       HELICS::helicscpp)
)
  message(
    ${HIGHLIGHTED_STATUS}
    "Skipping contrib/helics: HELICS 3 with the C++ shared library (HELICS_BUILD_CXX_SHARED_LIB=ON) not found (set NS3_WITH_HELICS or HELICS_DIR to its install prefix)"
  )
  return()
endif()

message(
  STATUS
    "contrib/helics: using HELICS ${HELICS_VERSION} from ${HELICS_DIR}"
)

build_lib(
  LIBNAME helics
  SOURCE_FILES
    helper/helics-helper.cc
    model/helics-application.cc
    model/helics-filter-application.cc
    model/helics-id-tag.cc
    model/helics-simulator-impl.cc
    model/helics-static-sink-application.cc
    model/helics-static-source-application.cc
    model/helics.cc
  HEADER_FILES
    helper/helics-helper.h
    model/helics-application.h
    model/helics-filter-application.h
    model/helics-id-tag.h
    model/helics-simulator-impl.h
    model/helics-static-sink-application.h
    model/helics-static-source-application.h
    model/helics.h
  LIBRARIES_TO_LINK
    ${libinternet}
    HELICS::helicscpp
  TEST_SOURCES test/helics-test-suite.cc
)
