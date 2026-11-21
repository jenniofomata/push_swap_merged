#!/bin/bash
# Operation-count benchmark for push_swap.
# Usage: tests/bench.sh [runs]          (default 20)
# Override the checker with: CHECKER=/path/to/checker_linux tests/bench.sh
# Not part of the graded submission.

cd "$(dirname "$0")/.." || exit 1
CHECKER=${CHECKER:-tests/checker_linux}
RUNS=${1:-20}

if [ ! -x "$CHECKER" ]; then
    echo "checker not found or not executable: $CHECKER" >&2
    exit 1
fi

make --no-print-directory >/dev/null || exit 1

bench()
{
    size=$1
    range=$2
    flag=$3
    tot=0
    max=0
    min=99999999
    fail=0
    for _ in $(seq "$RUNS"); do
        arg=$(shuf -i 1-"$range" -n "$size" | tr '\n' ' ')
        ops=$(./push_swap $flag $arg)
        n=$(printf '%s' "$ops" | grep -c .)
        verdict=$(printf '%s\n' "$ops" | $CHECKER $arg)
        if [ "$verdict" != "OK" ]; then
            fail=$((fail + 1))
        fi
        tot=$((tot + n))
        if [ "$n" -gt "$max" ]; then max=$n; fi
        if [ "$n" -lt "$min" ]; then min=$n; fi
    done
    printf '  %-11s avg=%-7s min=%-7s max=%-7s failures=%s\n' \
        "${flag:-<default>}" "$((tot / RUNS))" "$min" "$max" "$fail"
}

echo "=== 100 numbers   (pass < 2000   good < 1500   excellent < 700) ==="
bench 100 500 --simple
bench 100 500 --medium
bench 100 500 --complex
bench 100 500 ""

echo "=== 500 numbers   (pass < 12000  good < 8000   excellent < 5500) ==="
bench 500 1000 --medium
bench 500 1000 --complex
bench 500 1000 ""
