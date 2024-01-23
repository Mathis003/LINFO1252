# CU_UNREFERENCED_PARAMETER(pTest) appears in file Sources/Console/Console.c
# Can you indicate the line number of this command ?
grep -n 'CU_UNREFERENCED_PARAMETER(pTest)' CUnit/Sources/Console/Console.c

# In which file has the CU_trim_left prototype been defined ?
# Answer with the name of the file.
grep -E 'define.*CU_trim_left|CU_trim_left.*define' CUnit/*

# The function assert is frequently used in the CUnit source code.
# Can you count the number of lines where assert appears in all the files of the working directory?
grep -r 'assert' CUnit/* | wc -l