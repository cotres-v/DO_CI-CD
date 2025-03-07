#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0

gcc -Werror -Wextra -Wall s21_cat.c -o s21_cat

flags=("b" "e" "n" "s" "t" "number" "squeeze-blank" "number-nonblank")
input_files=("test_1.txt" "test_2.txt")

for flag in "${flags[@]}"
do
    echo ""
    echo "Testing with flag: -$flag"
    echo ""

    for file in "${input_files[@]}"
    do
        echo "$flag $file:"
        
        if [[ "$flag" =~ ^(b|e|n|s|t)$ ]]; then
            # Execute your program with single-character flags
            ./s21_cat "-$flag" "$file" > your_output.txt
            cat "-$flag" "$file" > original_output.txt
        else
            # Execute your program with long options
            ./s21_cat "--$flag" "$file" > your_output.txt
            cat "--$flag" "$file" > original_output.txt
        fi

        # Compare results
        if diff -q your_output.txt original_output.txt >/dev/null 2>&1;
        then
            let "SUCCESS++"
            echo $'\033[92m'"- Success"$'\033[0m'
        else 
            let "FAIL++"
            echo $'\033[31m'"- Fail"$'\033[0m'
        fi

        let "COUNTER++"

        # Remove temporary files
        rm your_output.txt
        rm original_output.txt
    done
done

echo "Total tests: $COUNTER, Success: $SUCCESS, Fail: $FAIL"
echo