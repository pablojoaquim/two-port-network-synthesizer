/*===========================================================================*/
/**
 * @file test_suite.cpp
 *
 *------------------------------------------------------------------------------
 * Copyright (c) 2026 - Pablo Joaquim
 * MIT License: https://opensource.org/licenses/MIT
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 * Unit tests
 * 
 * @todo Divide this file content using an abstraction layers concept
 *
 * @section ABBR ABBREVIATIONS:
 *   - @todo List any abbreviations, precede each with a dash ('-').
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *     - @todo Update list of design document(s).
 *
 *   - Requirements Document(s):
 *     - @todo Update list of requirements document(s)
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - @todo Update list of other applicable standards
 *
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/
#include <iostream>
#include <memory>
#include "acutest.h"

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/

/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Local Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Local Variables Definitions
 *===========================================================================*/

/*===========================================================================*
 * Local Function Prototypes
 *===========================================================================*/

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Test cases
 *===========================================================================*/

/*****************************************************************************
 * @fn         test_Example
 * @brief      Example unit test. 
 *             This test is intentionally kept as a template. 
 *             Replace it with project-specific tests. 
 * @param [in] void
 * @return     void
 *****************************************************************************/
void test_Example(void) 
{ 
    TEST_CHECK(1 == 1); 
}

/*===========================================================================*
 * Test list
 *===========================================================================*/
TEST_LIST = {
    { "Example", test_Example },
    { NULL, NULL }
};
