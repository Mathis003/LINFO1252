# You want to extract an alphabetically sorted list of unique hashtags.
# The list is into the file input.txt.
# The output should be in the file output.txt.

grep '#' input.txt | sort -d | uniq > output.txt