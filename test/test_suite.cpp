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
#include "foster.hpp"
#include "polynomial.hpp"
#include "pole_analysis.hpp"
#include "rational_function.hpp"
#include "total_removal.hpp"

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

void test_PolynomialRepresentation(void)
{
    const std::vector<double> coefficients = {2.0, 3.0, 4.0};
    const Polynomial polynomial(coefficients);

    TEST_CHECK(polynomial.coefficients() == coefficients);
}

void test_PolynomialSum(void)
{
    const Polynomial first({2.0, 3.0, 4.0});
    const Polynomial second({5.0, 6.0});
    const Polynomial result = first + second;

    TEST_CHECK(result.coefficients() == std::vector<double>({2.0, 8.0, 10.0}));
}

void test_PolynomialMultiplication(void)
{
    const Polynomial first({1.0, 2.0});
    const Polynomial second({3.0, 4.0});
    const Polynomial result = first * second;

    TEST_CHECK(result.coefficients() == std::vector<double>({3.0, 10.0, 8.0}));
}

void test_RationalFunctionConstructionAndAccess(void)
{
    const Polynomial numerator({1.0, 2.0});
    const Polynomial denominator({3.0, 4.0});
    const RationalFunction rationalFunction(numerator, denominator);

    TEST_CHECK(rationalFunction.numerator().coefficients() ==
               numerator.coefficients());
    TEST_CHECK(rationalFunction.denominator().coefficients() ==
               denominator.coefficients());
}

void test_RationalFunctionReplacement(void)
{
    const Polynomial initialNumerator({1.0, 2.0});
    const Polynomial initialDenominator({3.0, 4.0});
    RationalFunction rationalFunction(initialNumerator, initialDenominator);
    const Polynomial updatedNumerator({5.0, 6.0});
    const Polynomial updatedDenominator({7.0, 8.0});

    rationalFunction.replace(updatedNumerator, updatedDenominator);

    TEST_CHECK(rationalFunction.numerator().coefficients() ==
               updatedNumerator.coefficients());
    TEST_CHECK(rationalFunction.denominator().coefficients() ==
               updatedDenominator.coefficients());
}

void test_PoleAnalysisWithNoPoles(void)
{
    const RationalFunction rationalFunction(Polynomial({1.0}),
                                                  Polynomial({2.0}));

    TEST_CHECK(identifyRemovalOptions(rationalFunction).empty());
}

void test_PoleAnalysisWithRealPoles(void)
{
    const RationalFunction rationalFunction(Polynomial({1.0}),
                                                  Polynomial({1.0, -3.0, 2.0}));
    const std::vector<RemovalOption> options =
        identifyRemovalOptions(rationalFunction);

    TEST_CHECK(options.size() == 2U);
    TEST_CHECK(options[0].index == 0U);
    TEST_CHECK(options[1].index == 1U);
    TEST_CHECK(std::abs(options[0].pole.real() - 1.0) < 1.0e-10);
    TEST_CHECK(std::abs(options[1].pole.real() - 2.0) < 1.0e-10);
    TEST_CHECK(options[0].multiplicity == 1U);
    TEST_CHECK(options[1].multiplicity == 1U);
}

void test_PoleAnalysisWithComplexAndRepeatedPoles(void)
{
    const RationalFunction rationalFunction(
        Polynomial({1.0}), Polynomial({1.0, -2.0, 2.0}));
    const std::vector<RemovalOption> complexOptions =
        identifyRemovalOptions(rationalFunction);

    TEST_CHECK(complexOptions.size() == 2U);
    TEST_CHECK(std::abs(complexOptions[0].pole.real() - 1.0) < 1.0e-10);
    TEST_CHECK(std::abs(std::abs(complexOptions[0].pole.imag()) - 1.0) <
               1.0e-10);

    const RationalFunction repeatedFunction(
        Polynomial({1.0}), Polynomial({1.0, -2.0, 1.0}));
    const std::vector<RemovalOption> repeatedOptions =
        identifyRemovalOptions(repeatedFunction);

    TEST_CHECK(repeatedOptions.size() == 1U);
    TEST_CHECK(repeatedOptions[0].multiplicity == 2U);
}

void test_TotalRemovalValidation(void)
{
    const RationalFunction rationalFunction(
        Polynomial({1.0}), Polynomial({1.0, -3.0, 2.0}));
    const std::vector<RemovalOption> options =
        identifyRemovalOptions(rationalFunction);

    TEST_CHECK(validateTotalRemoval(rationalFunction, options[0]));

    const RationalFunction repeatedFunction(
        Polynomial({1.0}), Polynomial({1.0, -2.0, 1.0}));
    const RemovalOption repeatedOption =
        identifyRemovalOptions(repeatedFunction)[0];
    TEST_CHECK(!validateTotalRemoval(repeatedFunction, repeatedOption));
    TEST_CHECK(repeatedFunction.denominator().coefficients() ==
               std::vector<double>({1.0, -2.0, 1.0}));
}

void test_FosterExtractionForRealPole(void)
{
    const RationalFunction rationalFunction(
        Polynomial({1.0}), Polynomial({1.0, 1.0}));
    const RemovalOption option = identifyRemovalOptions(rationalFunction)[0];
    FosterComponent component;

    TEST_CHECK(extractFosterComponent(rationalFunction, option, component));
    TEST_CHECK(component.type == FosterComponentType::ParallelRC);
    TEST_CHECK(std::abs(component.resistance - 1.0) < 1.0e-10);
    TEST_CHECK(std::abs(component.capacitance - 1.0) < 1.0e-10);
}

void test_FosterExtractionForImaginaryPolePair(void)
{
    const RationalFunction rationalFunction(
        Polynomial({1.0, 0.0}), Polynomial({1.0, 0.0, 1.0}));
    const RemovalOption option = identifyRemovalOptions(rationalFunction)[0];
    FosterComponent component;

    TEST_CHECK(extractFosterComponent(rationalFunction, option, component));
    TEST_CHECK(component.type == FosterComponentType::ParallelLC);
    TEST_CHECK(std::abs(component.capacitance - 1.0) < 1.0e-10);
    TEST_CHECK(std::abs(component.inductance - 1.0) < 1.0e-10);
}

void test_FosterExtractionRejectsUnsupportedPole(void)
{
    const RationalFunction rationalFunction(
        Polynomial({1.0}), Polynomial({1.0, 1.0, 1.0}));
    const RemovalOption option = identifyRemovalOptions(rationalFunction)[0];
    FosterComponent component;

    TEST_CHECK(!extractFosterComponent(rationalFunction, option, component));
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
        { "Polynomial representation", test_PolynomialRepresentation },
        { "Polynomial sum", test_PolynomialSum },
        { "Polynomial multiplication", test_PolynomialMultiplication },
        { "Rational function construction and access",
            test_RationalFunctionConstructionAndAccess },
        { "Rational function replacement", test_RationalFunctionReplacement },
        { "Pole analysis with no poles", test_PoleAnalysisWithNoPoles },
        { "Pole analysis with real poles", test_PoleAnalysisWithRealPoles },
        { "Pole analysis with complex and repeated poles",
            test_PoleAnalysisWithComplexAndRepeatedPoles },
    { "Total removal validation", test_TotalRemovalValidation },
        { "Foster extraction for real pole", test_FosterExtractionForRealPole },
        { "Foster extraction for imaginary pole pair",
            test_FosterExtractionForImaginaryPolePair },
        { "Foster extraction rejects unsupported pole",
            test_FosterExtractionRejectsUnsupportedPole },
    { NULL, NULL }
};
