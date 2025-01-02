#!/bin/zsh

EXECUTABLE="$1" #Program being analysed

# checks if program has been provided
if [ ! -f "$EXECUTABLE" ]; then
  echo "Error: exectable not provided"
  exit 1
fi

#called upon the provided program
VALGRIND_OPTS="--leak-check=full" # --leak-check=full --show-leak-kinds=all --track-origins=yes"

echo "Running with valgrind on $EXECUTABLE"

valgrind $VALGRIND_OPTS ./$EXECUTABLE 2>&1 | tee ../test/valgrind_output.txt

#Just to see if valgrind ran successfully
if (( $? != 0 )); then
    echo "Valgrind encountered an error while running $EXECUTABLE."
else
    echo "Valgrind finished running '$EXECUTABLE'. Output saved to valgrind_output.txt."
fi


