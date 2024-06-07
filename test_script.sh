
#!/bin/bash

# Create a test file with 101 commands
for i in {1..101}; do
  echo "echo Command $i" >> test_commands.txt
done

# Run the shell program and pass the test file as input
./part3.out < test_commands.txt

./part3.out history
