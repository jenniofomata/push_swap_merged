#!/bin/bash

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
ORANGE='\033[0;33m'
NC='\033[0m' # No Color
BOLD='\033[1m'

# Counters
TOTAL=0
PASSED=0
FAILED=0
LEAKS=0

# Array to store failed tests
declare -a FAILED_TESTS

# Default values
CUSTOM_SIZE=0
CUSTOM_COUNT=10
EXTRA_MODE=0
TEST_SIMPLE=0
TEST_MEDIUM=0
TEST_COMPLEX=0
RUN_STANDARD_TESTS=1
ART_MODE=0
DISORDER_MODE=0
DISORDER_TARGET=""
DISORDER_TOLERANCE=0.05

# Print section header
print_section() {
    echo ""
    echo -e "${BOLD}${BLUE}╔══════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${BOLD}${BLUE}║${WHITE}  $1${BLUE}${NC}"
    echo -e "${BOLD}${BLUE}╚══════════════════════════════════════════════════════════════╝${NC}"
    echo ""
}

# Test function for error cases
run_error_test() {
    local test_name="$1"
    shift
    local args=("$@")

    TOTAL=$((TOTAL + 1))

    if command -v valgrind &> /dev/null; then
        leak_output=$(valgrind --leak-check=full --error-exitcode=42 --log-fd=9 \
            "$ROOT_DIR/push_swap" "${args[@]}" 9>&1 1>/dev/null 2>&1)
        leak_status=$?
        if [ $leak_status -eq 42 ]; then
            LEAKS=$((LEAKS + 1))
            echo -e "${YELLOW}⚠ LEAK${NC} ${test_name}: ${RED}Memory leak detected!${NC}"
            FAILED_TESTS+=("${test_name} - Memory leak")
            return
        fi
    fi

    output=$("$ROOT_DIR/push_swap" "${args[@]}" 2>&1)

    if echo "$output" | grep -q "Error"; then
        echo -e "${GREEN}✓ PASS${NC} ${test_name}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC} ${test_name}: Expected 'Error', got: '$output'"
        FAILED=$((FAILED + 1))
        FAILED_TESTS+=("${test_name} - Expected Error, got: $output")
    fi
}

# Print failed tests summary
print_failed_tests() {
    if [ ${#FAILED_TESTS[@]} -gt 0 ]; then
        echo ""
        print_section "FAILED TESTS DETAILS"
        echo -e "${RED}${BOLD}The following tests failed:${NC}\n"
        for test in "${FAILED_TESTS[@]}"; do
            echo -e "${RED}  ✗${NC} $test"
        done
        echo ""
    fi
}

# Print summary
print_summary() {
    print_section "TEST SUMMARY"
    echo -e "${BOLD}${WHITE}Total Tests: ${CYAN}$TOTAL${NC}"
    echo -e "${BOLD}${GREEN}Passed: $PASSED${NC}"
    echo -e "${BOLD}${RED}Failed: $FAILED${NC}"

    if [ $LEAKS -gt 0 ]; then
        echo -e "${BOLD}${YELLOW}Memory Leaks: $LEAKS${NC}"
    fi

    print_failed_tests

    if [ $FAILED -eq 0 ] && [ $LEAKS -eq 0 ]; then
        echo -e "${GREEN}╔══════════════════════════════════════════════════════════════╗${NC}"
        echo -e "${GREEN}║${BOLD}${WHITE}                  🎉 ALL TESTS PASSED! 🎉                     ${GREEN}║${NC}"
        echo -e "${GREEN}╚══════════════════════════════════════════════════════════════╝${NC}"
        exit 0
    elif [ $FAILED -eq 0 ]; then
        echo -e "${YELLOW}╔══════════════════════════════════════════════════════════════╗${NC}"
        echo -e "${YELLOW}║${BOLD}${WHITE}         Tests passed but memory leaks detected! 🔧         ${YELLOW}║${NC}"
        echo -e "${YELLOW}╚══════════════════════════════════════════════════════════════╝${NC}"
        exit 1
    else
        echo -e "${RED}╔══════════════════════════════════════════════════════════════╗${NC}"
        echo -e "${RED}║${BOLD}${WHITE}                   ❌ SOME TESTS FAILED ❌                  ${RED}║${NC}"
        echo -e "${RED}╚══════════════════════════════════════════════════════════════╝${NC}"
        exit 1
    fi
}

# ─── Standard mode ───────────────────────────
if [ $RUN_STANDARD_TESTS -eq 1 ]; then
    # ============= ERROR TESTS =============
    print_section "ERROR TESTS - Empty & Whitespace"
    run_error_test "Empty string" ""
    run_error_test "Only spaces" "   "
    run_error_test "Only tabs" "	"
    run_error_test "Empty with valid numbers" 1 2 3 ""
    run_error_test "Leading empty argument" "" 1 2 3
    run_error_test "Middle empty argument" 1 "" 2 3
    run_error_test "Multiple empty strings" "" "" ""
    run_error_test "Only newlines" $'\n\n\n'
    run_error_test "Only mixed whitespace" $' \t\n \t '
    run_error_test "Multiple whitespace arguments" " " "  " $'\t'
    run_error_test "Whitespace between arguments" "1" " " "2" " " "3"

    print_section "ERROR TESTS - Invalid Characters"
    run_error_test "Letter in middle" 1 2 a 3
    run_error_test "Letter at end" 1 2 3a
    run_error_test "Letter at start" a1 2 3
    run_error_test "Only letters" abc def
    run_error_test "Special characters" 1 2 @ 3
    run_error_test "Plus attached to number" 1 2 3+4
    run_error_test "Minus attached to number" 1 2 3-4
    run_error_test "Letter inside number" 123abc456
    run_error_test "Letters around number" a123b
    run_error_test "Special character inside number" 12@34
    run_error_test "Dot inside number" 12.34
    run_error_test "Comma inside number" 12,34
    run_error_test "Slash inside number" 12/34
    run_error_test "Underscore inside number" 12_34
    run_error_test "Colon inside number" 12:34
    run_error_test "Semicolon inside number" 12\;34
    run_error_test "Backslash inside number" '12\34'
    run_error_test "Quote inside number" "12'34"
    run_error_test "Double quote inside number" '12"34'
    run_error_test "Unicode character" 12é34
    run_error_test "Emoji inside number" '12😀34'

    print_section "ERROR TESTS - Invalid Signs"
    run_error_test "Only plus sign" +
    run_error_test "Only minus sign" -
    run_error_test "Double plus" ++
    run_error_test "Double minus" --
    run_error_test "Plus minus" +-
    run_error_test "Minus plus" -+
    run_error_test "Double sign in number" 1 2 --3
    run_error_test "Plus at end" 42+
    run_error_test "Minus at end" 42-
    run_error_test "Triple plus" +++
    run_error_test "Triple minus" ---
    run_error_test "Triple mixed signs" ++-
    run_error_test "Sign in middle" 12+34
    run_error_test "Sign between numbers" 1 + 2
    run_error_test "Sign after whitespace" "  + 42"
    run_error_test "Sign before whitespace" "+ 42"
    run_error_test "Multiple signs in sequence" 1 ++2 3
    run_error_test "Sign after valid number" 1 2 + 3
    run_error_test "Repeated signs at end" 42++
    run_error_test "Repeated signs at start" --42

    print_section "ERROR TESTS - Integer Overflow (INT_MAX/MIN)"
    run_error_test "INT_MAX + 1"               2147483648
    run_error_test "INT_MIN - 1"               -2147483649
    run_error_test "INT_MAX + 1 with valid"    1 2147483648
    run_error_test "INT_MIN - 1 with valid"    -2147483649 1
    run_error_test "Multiple overflow"         9999999999 8888888888
    run_error_test "+INT_MAX + 1"              +2147483648
    run_error_test "INT_MAX + 2"               2147483649
    run_error_test "INT_MIN - 2"               -2147483650
    run_error_test "INT_MAX + 10"              2147483657
    run_error_test "INT_MIN - 10"              -2147483658
    run_error_test "Positive overflow with zeros" 0002147483648
    run_error_test "Negative overflow with zeros" -0002147483649
    run_error_test "Positive overflow with plus" +2147483648
    run_error_test "Overflow after valid numbers" 1 2 3 2147483648
    run_error_test "Overflow before valid numbers" 2147483648 1 2 3
    run_error_test "Overflow between valid numbers" 1 2 2147483648 3
    run_error_test "Mixed positive and negative overflow" 2147483648 -2147483649
    run_error_test "Positive overflow with negative sign" -2147483649

    print_section "ERROR TESTS - Long Long Overflow (LLONG_MAX x2)"
    run_error_test "LLONG_MAX" 9223372036854775807
    run_error_test "LLONG_MAX + 1" 9223372036854775808
    run_error_test "LLONG_MIN" -9223372036854775808
    run_error_test "LLONG_MIN - 1" -9223372036854775809
    run_error_test "Double LLONG_MAX" 18446744073709551615
    run_error_test "Beyond LLONG x2" 99999999999999999999
    run_error_test "20 digits positive" 12345678901234567890
    run_error_test "20 digits negative" -12345678901234567890
    run_error_test "Extreme overflow" 999999999999999999999999999999
    run_error_test "LLONG_MAX + 2" 9223372036854775809
    run_error_test "LLONG_MIN - 2" -9223372036854775810
    run_error_test "Positive 30 digits" 123456789012345678901234567890
    run_error_test "Negative 30 digits" -123456789012345678901234567890
    run_error_test "100 digits positive" "$(printf '9%.0s' {1..100})"
    run_error_test "100 digits negative" "-$(printf '9%.0s' {1..100})"
    run_error_test "Leading zeros before overflow" 00000000009223372036854775808
    run_error_test "Overflow with plus sign" +9223372036854775808

    print_section "ERROR TESTS - Edge Cases with Overflow"
    run_error_test "Large positive" 999999999999
    run_error_test "Large negative" -999999999999
    run_error_test "Scientific notation attempt" 1e10
    run_error_test "Hex attempt" 0x7FFFFFFF
    run_error_test "Binary attempt" 0b1111
    run_error_test "Octal attempt" 07777777777
    run_error_test "Hex with lowercase prefix" 0xff
    run_error_test "Hex with uppercase prefix" 0XFF
    run_error_test "Binary with uppercase prefix" 0B1010
    run_error_test "Floating point" 3.14159
    run_error_test "Negative floating point" -3.14159
    run_error_test "Exponent notation uppercase" 1E10
    run_error_test "Exponent notation negative" 1e-10
    run_error_test "Infinity" Infinity
    run_error_test "NaN" NaN
    run_error_test "Unsigned suffix" 42u
    run_error_test "Long suffix" 42L

    print_section "ERROR TESTS - Duplicates"
    run_error_test "Simple duplicate" 1 2 3 2
    run_error_test "Adjacent duplicates" 5 5
    run_error_test "Three duplicates" 42 42 42
    run_error_test "Duplicate across args" "1 2" "2 3"
    run_error_test "Zero duplicates" 0 0
    run_error_test "Negative duplicates" -5 -5
    run_error_test "Many duplicates" 1 2 3 4 5 3
    run_error_test "Duplicate at start" 1 1 2 3
    run_error_test "Duplicate at end" 1 2 3 3
    run_error_test "Duplicate in the middle" 1 2 2 3
    run_error_test "Multiple duplicate pairs" 1 2 3 1 2 3
    run_error_test "Multiple repeated values" 1 1 2 2 3 3
    run_error_test "Duplicate across mixed arguments" "1 2 3" "3 4 5"
    run_error_test "Duplicate with negative values" -5 0 5 -5
    run_error_test "Duplicate with INT_MIN" -2147483648 0 -2147483648
    run_error_test "Duplicate with INT_MAX" 2147483647 0 2147483647
    run_error_test "Duplicate zero across arguments" "1 0" "0 2"

    print_summary
fi
