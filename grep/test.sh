#!/bin/bash
LOG="test_log.log"
: > $LOG
OK=0
NOTOK=0
NUMBER=0
echo -e "hello world\nhello world\nhello hello\nHello WORLD"> test.txt
echo -e "hello world\nHelloo"> test1.txt
echo -e "WORLD"> pattern.txt
run_test(){
    ./my_grep "$@" > my_text.txt
    grep "$@" > sys.txt
    if diff -u my_text.txt sys.txt >> $LOG; then
    echo "Test $@: OK!"
    ((OK++))
    else
    echo "Test "$@": You func didnot $LOG test"
    ((NOTOK++))
    fi
    ((NUMBER++))
}
run_test -i "hello" test.txt
run_test -v "hello" test.txt
run_test -c "hello" test.txt test1.txt
run_test -l "hello" test.txt test1.txt
run_test -n "hello" test.txt
run_test -e "hello" -e "world" test.txt
run_test -h "hello" test.txt test1.txt
run_test -s "hello" test0.txt test1.txt
run_test -f pattern.txt test1.txt
run_test -o "hello" test.txt
run_test -iv "hello" test.txt
run_test -in "hello" test.txt
run_test -hn "hello" test.txt
run_test -io "hello" test.txt
run_test -oiv "hello" test.txt
run_test -hni "hello" test.txt

echo "Ok $OK/$NUMBER|Bad $NOTOK/$NUMBER"

rm -f test.txt test1.txt sys.txt my_text.txt pattern.txt
