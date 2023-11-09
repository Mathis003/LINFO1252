OUTPUT_FILE="mesures.csv"
nbThreads=(1 2 3 4 5 6 7 8)
times=()

make -C "Modest" -s clean
echo "NbThreads,Time1,Time2,Time3,Time4,Time5" > ${OUTPUT_FILE}
for i in {1..8}
do
    for j in {1..5}
    do
        TIME=$(/usr/bin/time -f %e make -C "Modest" -s -j$i 2>&1 | tail -n 1)
        times[${j}-1]=${TIME}
        make -C "Modest" -s clean
    done
    echo "${nbThreads[${i}-1]},${times[0]},${times[1]},${times[2]},${times[3]},${times[4]}" >> ${OUTPUT_FILE}
done