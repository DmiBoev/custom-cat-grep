#!/bin/bash
LOG="test_log.log"
: > $LOG
OK=0
NOTOK=0
NUMBER=0

echo -e "Hello\nWorld\n\n\n\n\nhello\tworld\nhello   world" > test.txt

run_test(){
    ./my_cat "$@" > my_text.txt
    cat "$@" > sys.txt
    
    if diff -u my_text.txt sys.txt >> $LOG; then
        echo "Test $NUMBER [$@]: OK"
        ((OK++))
    else
        echo "Test $NUMBER [$@]: FAIL (check $LOG)"
        ((NOTOK++))
    fi
    ((NUMBER++))
}
run_test -b test.txt
run_test -e test.txt
run_test -n test.txt
run_test -s test.txt
run_test -t test.txt
run_test -n -b test.txt
run_test -sne test.txt

echo "Ok $OK/$NUMBER|Bad $NOTOK/$NUMBER"

rm -f test.txt sys.txt my_text.txt
