grep -n 'CU_UNREFERENCED_PARAMETER(pTest)' CUnit/Sources/Console/Console.c
grep -E 'define.*CU_trim_left|CU_trim_left.*define' CUnit/*
grep -r 'assert' CUnit/* | wc -l