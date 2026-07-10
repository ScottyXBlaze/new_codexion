#!/bin/sh

PROG="./codexion"
PASS=0
FAIL=0

green="$(printf '\033[32m')"
red="$(printf '\033[31m')"
reset="$(printf '\033[0m')"

run_test() {
	name="$1"
	shift
	if "$@"; then
		PASS=$((PASS + 1))
		printf "%s[PASS]%s %s\n" "$green" "$reset" "$name"
	else
		FAIL=$((FAIL + 1))
		printf "%s[FAIL]%s %s\n" "$red" "$reset" "$name"
	fi
}

build_prog() {
	make -s fclean >/dev/null 2>&1 || return 1
	make -s >/dev/null 2>&1 || return 1
	[ -x "$PROG" ]
}

test_invalid_arg_count() {
	$PROG 4 800 200 200 200 2 50 >/dev/null 2>&1
	[ $? -ne 0 ]
}

test_invalid_integer() {
	$PROG 4 800 nope 200 200 2 50 fifo >/dev/null 2>&1
	[ $? -ne 0 ]
}

test_negative_value() {
	$PROG 4 -800 200 200 200 2 50 fifo >/dev/null 2>&1
	[ $? -ne 0 ]
}

test_invalid_scheduler() {
	$PROG 4 800 200 200 200 2 50 rr >/dev/null 2>&1
	[ $? -ne 0 ]
}

test_fifo_feasible_run() {
	timeout 8s $PROG 4 1200 120 120 120 2 20 fifo >.test_fifo.log 2>&1 || return 1
	grep -q "is compiling" .test_fifo.log || return 1
	! grep -q "burned out" .test_fifo.log
}

test_edf_feasible_run() {
	timeout 8s $PROG 4 1200 120 120 120 2 20 edf >.test_edf.log 2>&1 || return 1
	grep -q "is compiling" .test_edf.log || return 1
	! grep -q "burned out" .test_edf.log
}

test_log_line_format() {
	timeout 8s $PROG 4 1200 120 120 120 1 10 fifo >.test_format.log 2>&1 || return 1
	awk '
		/./ {
			if ($0 !~ /^[0-9]+ [0-9]+ (has taken a dongle|is compiling|is debugging|is refactoring|burned out)$/)
				bad=1
		}
		END { exit bad }
	' .test_format.log
}

test_compile_needs_two_dongles() {
	timeout 8s $PROG 4 1200 100 100 100 1 10 fifo >.test_dongles.log 2>&1 || return 1
	awk '
		{
			id=$2
			if ($3 == "has")
				take[id]++
			else if ($3 == "is" && $4 == "compiling") {
				if (take[id] < 2) bad=1
				else take[id]-=2
			}
		}
		END { exit bad }
	' .test_dongles.log
}

test_burnout_happens() {
	timeout 8s $PROG 2 200 300 10 10 0 0 fifo >.test_burnout.log 2>&1 || return 1
	grep -q "burned out" .test_burnout.log
}

test_burnout_timing() {
	timeout 8s $PROG 2 200 300 10 10 0 0 fifo >.test_burnout_time.log 2>&1 || return 1
	ts="$(awk '/burned out/ {print $1; exit}' .test_burnout_time.log)"
	[ -n "$ts" ] || return 1
	[ "$ts" -le 210 ]
}

test_single_coder_subject_case() {
	timeout 5s $PROG 1 200 60 60 60 1 10 fifo >.test_one_coder.log 2>&1
	# Subject says 1 coder is a valid topology; this test checks acceptance.
	# We accept either a normal run or a burnout run, but reject immediate arg rejection.
	! grep -qi "not enough coder" .test_one_coder.log
}

cleanup_logs() {
	rm -f .test_*.log
}

main() {
	run_test "Build program" build_prog || {
		printf "%sCould not build codexion%s\n" "$red" "$reset"
		exit 1
	}

	run_test "Reject invalid arg count" test_invalid_arg_count
	run_test "Reject non-integer argument" test_invalid_integer
	run_test "Reject negative values" test_negative_value
	run_test "Reject invalid scheduler" test_invalid_scheduler
	run_test "FIFO feasible scenario (no burnout)" test_fifo_feasible_run
	run_test "EDF feasible scenario (no burnout)" test_edf_feasible_run
	run_test "Log line format is valid" test_log_line_format
	run_test "Compile is preceded by two dongle takes" test_compile_needs_two_dongles
	run_test "Burnout is detected in impossible case" test_burnout_happens
	run_test "Burnout log appears around deadline (<= 10ms target)" test_burnout_timing
	run_test "Single coder subject topology is accepted" test_single_coder_subject_case

	printf "\nResult: %d passed, %d failed\n" "$PASS" "$FAIL"
	cleanup_logs
	[ "$FAIL" -eq 0 ]
}

main
