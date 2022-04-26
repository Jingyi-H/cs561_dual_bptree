#!/bin/bash
# for VARIABLE in file1 file2 file3
# do
# 	command1 on $VARIABLE
# 	command2
# 	commandN
# done
echo ""
echo "test 0 5"
# ./main createdata_10000000-elems_0-K_500000-L_1234seed1650847988.dat
# ./main createdata_10000000-elems_0-K_500000-L_1seed1650908753.dat
./main createdata_10000000-elems_0-K_500000-L_2seed1650917491.dat

echo ""
echo "test 1 1"
# ./main createdata_10000000-elems_100000-K_100000-L_1234seed1650847955.dat
# ./main createdata_10000000-elems_100000-K_100000-L_1seed1650908742.dat
./main createdata_10000000-elems_100000-K_100000-L_2seed1650917505.dat

echo ""
echo "test 3 3"
# ./main createdata_10000000-elems_300000-K_300000-L_1234seed1650847942.dat
# ./main createdata_10000000-elems_300000-K_300000-L_1seed1650908731.dat
./main createdata_10000000-elems_300000-K_300000-L_2seed1650917523.dat

echo ""
echo "test 5 5"
# ./main createdata_10000000-elems_500000-K_500000-L_1234seed1650847931.dat
# ./main createdata_10000000-elems_500000-K_500000-L_1seed1650908722.dat
./main createdata_10000000-elems_500000-K_500000-L_2seed1650917540.dat

echo ""
echo "test 50 50"
# ./main createdata_10000000-elems_5000000-K_5000000-L_1seed1650908662.dat
./main createdata_10000000-elems_5000000-K_5000000-L_2seed1650917469.dat
