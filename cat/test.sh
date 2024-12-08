#!/bin/bash

flags=("-b" "-e" "-E" "-n" "-s" "-t" "-T" "-v")
num_flags=$((2 ** ${#flags[@]}))
test_number=1

file_list=(
    ./test/char.txt
    ./test/test_case.txt
    ./test/test_data_1.txt
    ./test/test_data_2.txt
    ./test/test_data_3.txt
    ./test/test_data_4.txt
    ./test/test_data_5.txt
    ./test/test_data_6.txt
    ./test/test_data_7.txt
    ./test/test_data_8.txt
    ./test/test_data_9.txt
    ./test/test_data_10.txt
)

for file in "${file_list[@]}"; do
    success=1
    for ((i=1; i<$num_flags; i++)); do
        cmd_cat="cat"
        cmd_s21_cat="./s21_cat"
        for ((j=0; j<${#flags[@]}; j++)); do
            if [[ $((i & (2**j))) -ne 0 ]]; then
                cmd_cat+=" ${flags[$j]}"
                cmd_s21_cat+=" ${flags[$j]}"
            fi
        done
        cat_output=$(eval $cmd_cat $file | tr -d '\0')
        s21_cat_output=$(eval $cmd_s21_cat $file | tr -d '\0')
        if [ "$cat_output" != "$s21_cat_output" ]; then
            success=0
            break
        fi
    done
    if [ $success -eq 1 ]; then
        echo "Test $test_number success"
    else
        echo "Test $test_number failed"
    fi
    echo "---------------"
    test_number=$((test_number + 1))
done