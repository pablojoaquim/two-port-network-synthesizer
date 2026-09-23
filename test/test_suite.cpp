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
#include <string>

#include "acutest.h"
#include "cli_parser.hpp"

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
void test_ParseValidVectors(void)
{
    char argument0[] = "application";
    char argument1[] = "[1,1,2]";
    char argument2[] = "[2,1,3]";
    char *arguments[] = {argument0, argument1, argument2};
    ParsedInput input;
    std::string errorMessage;

    TEST_CHECK(parseCommandLine(3, arguments, input, errorMessage));
    TEST_CHECK(input.numerator.size() == 3U);
    TEST_CHECK(input.denominator.size() == 3U);
    TEST_CHECK(input.numerator[0] == 1.0);
    TEST_CHECK(input.numerator[2] == 2.0);
    TEST_CHECK(errorMessage.empty());
}

void test_RejectMissingArguments(void)
{
    char argument0[] = "application";
    char *arguments[] = {argument0};
    ParsedInput input;
    std::string errorMessage;

    TEST_CHECK(!parseCommandLine(1, arguments, input, errorMessage));
    TEST_CHECK(!errorMessage.empty());
}

void test_RejectMalformedVector(void)
{
    char argument0[] = "application";
    char argument1[] = "[1,invalid]";
    char argument2[] = "[1,2]";
    char *arguments[] = {argument0, argument1, argument2};
    ParsedInput input;
    std::string errorMessage;

    TEST_CHECK(!parseCommandLine(3, arguments, input, errorMessage));
    TEST_CHECK(!errorMessage.empty());
}

void test_RejectNonFiniteAndIncompatibleVectors(void)
{
    char argument0[] = "application";
    char argument1[] = "[1,nan]";
    char argument2[] = "[0,0]";
    char *arguments[] = {argument0, argument1, argument2};
    ParsedInput input;
    std::string errorMessage;

    TEST_CHECK(!parseCommandLine(3, arguments, input, errorMessage));
    TEST_CHECK(!errorMessage.empty());

    char validNumerator[] = "[1,2]";
    char zeroDenominator[] = "[0,0]";
    char *incompatibleArguments[] = {argument0, validNumerator,
                                     zeroDenominator};
    TEST_CHECK(!parseCommandLine(3, incompatibleArguments, input,
                                 errorMessage));
}

/*===========================================================================*
 * Test list
 *===========================================================================*/
TEST_LIST = {
    { "Parse valid vectors", test_ParseValidVectors },
    { "Reject missing arguments", test_RejectMissingArguments },
    { "Reject malformed vector", test_RejectMalformedVector },
    { "Reject non-finite and incompatible vectors",
      test_RejectNonFiniteAndIncompatibleVectors },
    { NULL, NULL }
};
