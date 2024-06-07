#!/bin/bash

# Create a test file with 100 commands
for i in {1..100}; do
  echo "echo Command $i" >> test_commands.txt
done

# Add one more command to exceed the history limit
echo "echo Command 101" >> test_commands.txt

# Run the shell program and pass the test file as input
./part3.out < test_commands.txt
