#!/bin/bash
# Usage: tests/run_all.sh [runs]      (random inputs per size, default 20)
# Prints a PASS/FAIL line per section and a summary. Exit code 0 = all pass.
# Not part of the graded submission.

cd "$(dirname "$0")/.." || exit 1
RUNS=${1:-20}
REF=tests/checker_linux
LOG=$(mktemp)
trap 'rm -f "$LOG"' EXIT
declare -a RESULTS
FAILS=0

section() { printf '\n=== %s ===\n' "$1"; }
result()
{
    if [ "$2" -eq 0 ]; then
        RESULTS+=("PASS  $1")
    else
        RESULTS+=("FAIL  $1")
        FAILS=$((FAILS + 1))
    fi
}
randlist() { shuf -i 1-100000 -n "$1" | tr '\n' ' '; }

# 1. Norminette ---------------------------------------------------------------
section "Norminette"
if command -v norminette >/dev/null; then
    norminette src include > "$LOG" 2>&1
    grep -v ': OK!' "$LOG"
    ! grep -q 'Error' "$LOG"
    result "Norminette" $?
else
    echo "norminette not installed, skipped"
fi

# 2. Build --------------------------------------------------------------------
section "Build"
ok=0
make --no-print-directory re > "$LOG" 2>&1 || ok=1
make --no-print-directory bonus > "$LOG" 2>&1 || ok=1
relink=$(make --no-print-directory all bonus 2>&1 | grep -c -- ' -o ')
echo "make re + make bonus: $([ $ok -eq 0 ] && echo ok || echo FAILED)"
echo "commands run by a second make: $relink (0 = no relink)"
[ $ok -eq 0 ] && [ "$relink" -eq 0 ]
result "Build, bonus, no relink" $?

# 3. Error handling -----------------------------------------------------------
section "Parser tests (test_parser.sh)"
bash tests/test_parser.sh > "$LOG" 2>&1
st=$?
grep -E 'Total|Passed|Failed' "$LOG" | tail -3
result "Parser tests" $st

section "Error tests (test_errors.sh)"
bash tests/test_errors.sh > "$LOG" 2>&1
st=$?
grep -E 'FAIL|passed:' "$LOG"
result "Error tests" $st

# 4. Checker bonus against the reference checker ------------------------------
section "Checker bonus vs tests/checker_linux"
bad=0
cmp_checker()
{
    input=$1
    shift
    mine=$(printf "$input" | ./checker "$@" 2>&1)
    theirs=$(printf "$input" | $REF "$@" 2>&1)
    if [ "$mine" = "$theirs" ]; then
        printf '  same  %-30s -> [%s]\n' "$(echo "$input" | tr '\n' ' ') | $*" "$mine"
    else
        printf '  DIFF  %-30s -> got [%s] want [%s]\n' "$input | $*" "$mine" "$theirs"
        bad=1
    fi
}
cmp_checker 'sa\npb\nrrr\n' 0 9 1 8 2 7 3 6 4 5
cmp_checker '' 0 1 2
cmp_checker 'pb\nra\npb\nra\nsa\nra\npa\npa\n' 0 9 1 8 2
cmp_checker 'foo\n' 3 2 1
cmp_checker ' sa\n' 3 2 1
cmp_checker 'sa \n' 3 2 1
cmp_checker 'sa\n' 1 2 2
cmp_checker 'sa\n' 1 two 3
cmp_checker 'sa' 2 1
cmp_checker 'sa\n' 2 1
result "Checker bonus" $bad

# 5. Sorting: correctness and move counts --------------------------------------
section "Sorting ($RUNS random inputs per size)"
bad=0
avg_of()
{
    size=$1
    flag=$2
    tot=0
    worst=0
    for _ in $(seq "$RUNS"); do
        arg=$(randlist "$size")
        ops=$(./push_swap $flag $arg)
        n=$(printf '%s' "$ops" | grep -c .)
        if [ "$( { [ -n "$ops" ] && printf '%s\n' "$ops"; } | $REF $arg)" != "OK" ]; then
            echo "  KO: $flag $arg" >&2
            bad=1
        fi
        tot=$((tot + n))
        [ "$n" -gt "$worst" ] && worst=$n
    done
    AVG=$((tot / RUNS))
    WORST=$worst
}
for size in 1 2 3 5 10 50; do
    for flag in --simple --medium --complex --adaptive; do
        avg_of $size $flag
        printf '  %4s %-11s avg %-6s worst %s\n' "$size" "$flag" "$AVG" "$WORST"
        if [ "$size" -eq 3 ] && [ "$WORST" -gt 3 ]; then bad=1; echo "  3 numbers need more than 3 moves" >&2; fi
        if [ "$size" -eq 5 ] && [ "$WORST" -gt 12 ]; then bad=1; echo "  5 numbers need more than 12 moves" >&2; fi
        [ "$size" -eq 50 ] && [ "$flag" = "--simple" ] && S50=$AVG
        [ "$size" -eq 50 ] && [ "$flag" = "--complex" ] && C50=$AVG
    done
done
if [ "$C50" -ge "$S50" ]; then
    echo "  --complex ($C50) does not beat --simple ($S50) on 50 numbers" >&2
    bad=1
fi
tier()
{
    if [ "$1" -lt "$2" ]; then echo excellent
    elif [ "$1" -lt "$3" ]; then echo good
    elif [ "$1" -lt "$4" ]; then echo pass
    else echo "OVER THE LIMIT"; fi
}
for flag in --simple --medium --complex --adaptive; do
    avg_of 100 $flag
    printf '   100 %-11s avg %-6s worst %-6s %s\n' "$flag" "$AVG" "$WORST" "$(tier $AVG 700 1500 2000)"
    [ "$flag" = "--adaptive" ] && [ "$AVG" -ge 2000 ] && bad=1
done
for flag in --medium --complex --adaptive; do
    avg_of 500 $flag
    printf '   500 %-11s avg %-6s worst %-6s %s\n' "$flag" "$AVG" "$WORST" "$(tier $AVG 5500 8000 12000)"
    [ "$flag" = "--adaptive" ] && [ "$AVG" -ge 12000 ] && bad=1
done
result "Sorting: checker OK and move limits" $bad

# 6. AddressSanitizer -----------------------------------------------------------
section "AddressSanitizer + UBSan build (make debug)"
bad=0
if make --no-print-directory debug > "$LOG" 2>&1 \
    && make --no-print-directory bonus CFLAGS="-Wall -Wextra -Werror -g -fsanitize=address,undefined" > "$LOG" 2>&1; then
    for flag in --simple --medium --complex --adaptive "--bench"; do
        for size in 0 1 3 5 100 500; do
            arg=$(randlist "$size")
            ./push_swap $flag $arg 2>"$LOG" | ./checker $arg > /dev/null 2>>"$LOG"
            if grep -q -E 'Sanitizer|runtime error' "$LOG"; then
                echo "  problem: $flag with $size numbers" >&2
                bad=1
            fi
        done
    done
    for args in "1 2 2" "1 abc" "" "--bogus 1"; do
        ./push_swap $args > /dev/null 2>"$LOG"
        grep -q -E 'Sanitizer|runtime error' "$LOG" && bad=1 && echo "  problem: $args" >&2
    done
    echo "  $([ $bad -eq 0 ] && echo 'no errors or leaks' || echo 'see problems above')"
else
    echo "  sanitizer build failed" >&2
    bad=1
fi
make --no-print-directory re > /dev/null 2>&1
make --no-print-directory bonus > /dev/null 2>&1
result "AddressSanitizer + UBSan" $bad

# Summary -----------------------------------------------------------------------
section "Summary"
printf '  %s\n' "${RESULTS[@]}"
echo
[ "$FAILS" -eq 0 ] && echo "  all checks passed" || echo "  $FAILS section(s) failed"
[ "$FAILS" -eq 0 ]
