#!/bin/bash

TEST_DIR="./tests"
LIB_DIR="./libs"
ALL_TEST_FILES=$(find "$TEST_DIR" -name 'test_*.c')
ERROR_LOG="$TEST_DIR/test_errors.log"

function print_box() {
    local content="$1"
    local content_length=${#content}
    local box_width=$((content_length + 4))
    printf '%0.s-' $(seq 1 $box_width)
    printf '\n'
    printf '| %-*s |\n' "$content_length" "$content"
    printf '%0.s-' $(seq 1 $box_width)
    printf '\n'
}

function find_required_libs() {
    local test_file="$1"
    local included_headers=$(grep -oP '#include\s*"\K[^"]+' "$test_file")
    local required_libs=""

    for header in $included_headers; do
        local lib_file=$(find "$LIB_DIR" -name "${header%.*}.c")
        if [ ! -z "$lib_file" ] && [[ ! " ${processed_libs[*]} " =~ " ${lib_file} " ]]; then
            required_libs+="$lib_file "
            processed_libs+=("$lib_file")
            required_libs+=$(find_required_libs "$lib_file")
        fi
    done
    echo "$required_libs"
}

# Clear the existing error log
if [ -f "$ERROR_LOG" ]; then
    rm "$ERROR_LOG"
fi

if [ $# -eq 0 ]; then
    TEST_FILES="$ALL_TEST_FILES"
else
    TEST_FILES=""
    for arg in "$@"; do
        TEST_FILES+=$(find "$TEST_DIR" -name "$arg")" "
    done
fi

declare -a processed_libs

for test_file in $TEST_FILES; do
    lib_name=$(basename "$test_file" .c | cut -c 6-)
    output_file="test_${lib_name}_bin"
    C_LIBS=$(find_required_libs "$test_file")

    # Remove duplicate libraries
    C_LIBS=$(echo "$C_LIBS" | xargs -n1 | sort -u | xargs)

    print_box "Compiling $test_file"

    gcc -g "$test_file" $C_LIBS -I. -I./libs -o "$TEST_DIR/${output_file}" 2>> "$ERROR_LOG"

    if [ $? -ne 0 ]; then
        print_box "Compilation failed for $test_file"
        echo "-----------------------------------------" >> "$ERROR_LOG"
        echo "Compilation failed for $test_file" >> "$ERROR_LOG"
        echo "-----------------------------------------" >> "$ERROR_LOG"
    else
        print_box "Running $test_file"

        "$TEST_DIR/$output_file"
        error_code=$?

        print_box "Exit code for $test_file: $error_code"
    fi

    # if [ -s "$TEST_DIR/${output_file}" ]; then
    #     rm "$TEST_DIR/${output_file}"
    # fi

    # Clear processed_libs for the next test file
    processed_libs=()
done
