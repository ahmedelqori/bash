#!/bin/bash



# Loop 100 times
for (( j=0; j<100; j++ )); do
  # Execute the commands and append to the file
  COMMAND="echo First >> a | echo Second >> a | echo Third >> a | echo '' >> a"
  echo "$COMMAND" | ./minishell
done

# Display the contents of the file
cat a
