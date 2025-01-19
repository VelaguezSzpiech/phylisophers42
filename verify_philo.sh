#!/bin/bash

# Configuration
EXPECTED_EATS=4  # Set this to the number of times each philosopher must eat
SIMULATION="./philo"  # Path to the philosopher simulation binary
ARGS="30 800 300 300 $EXPECTED_EATS"  # Update with the appropriate arguments for your simulation

# Run the simulation and capture output
OUTPUT=$($SIMULATION $ARGS)

# Initialize variables
declare -A eat_counts
ALL_PASSED=true

# Extract philosopher eating counts from the output
echo "$OUTPUT" | grep -Eo 'Philosopher [0-9]+ has eaten [0-9]+ times' | while read -r line; do
    PHILO=$(echo "$line" | grep -Eo 'Philosopher [0-9]+' | grep -Eo '[0-9]+')
    EATS=$(echo "$line" | grep -Eo '[0-9]+ times' | grep -Eo '[0-9]+')

    # Store the number of times this philosopher ate
    eat_counts[$PHILO]=$EATS

    # Check if it matches the expected count
    if [[ "$EATS" -ne "$EXPECTED_EATS" ]]; then
        echo "Philosopher $PHILO ate $EATS times. Expected: $EXPECTED_EATS times."
        ALL_PASSED=false
    fi
done

# Report overall result
if [[ "$ALL_PASSED" == true ]]; then
    echo "All philosophers ate the expected number of times ($EXPECTED_EATS)."
else
    echo "Some philosophers did not eat the expected number of times."
fi
