#!/bin/bash
# Error-handling matrix for push_swap, mirroring the evaluation sheet.
# Usage: tests/test_errors.sh
# Not part of the graded submission.

cd "$(dirname "$0")/.." || exit 1
make --no-print-directory >/dev/null || exit 1

pass=0
fail=0

check()
{
    desc=$1
    expect=$2
    shift 2
    out=$(./push_swap "$@" 2>&1)
    if [ "$out" = "$expect" ]; then
        pass=$((pass + 1))
        printf '  PASS  %-32s -> [%s]\n' "$desc" "$out"
    else
        fail=$((fail + 1))
        printf '  FAIL  %-32s -> got [%s] want [%s]\n' "$desc" "$out" "$expect"
    fi
}

check "no arguments"            ""
check "non-numeric"             "Error" 0 one 2 3
check "duplicate"               "Error" 3 2 3
check "above INT_MAX"           "Error" 2147483648
check "below INT_MIN"           "Error" -2147483649
check "INT_MIN accepted"        ""      -2147483648
check "INT_MAX accepted"        ""      2147483647
check "empty string"            "Error" ""
check "whitespace only"         "Error" "   "
check "empty among numbers"     "Error" "" 1 2 3
check "whitespace among numbers" "Error" 1 2 "  " 3
check "lone minus"              "Error" -
check "lone plus"               "Error" +
check "trailing garbage"        "Error" 12abc
check "unknown flag"            "Error" --bogus 1 2
check "quoted list"             ""      "1 2 3"
check "quoted list duplicate"   "Error" "1 2 2"
check "flag without numbers"    ""      --bench
check "already sorted"          ""      0 1 2 3 4 5 6 7 8 9

echo
echo "  passed: $pass   failed: $fail"
[ "$fail" -eq 0 ]
