#!/bin/bash
# for VARIABLE in file1 file2 file3
# do
# 	command1 on $VARIABLE
# 	command2
# 	commandN
# done
echo ""
echo "test 0 5"
# ./main data_10000000-elems_0-kperct_5-lperct_1seed1650756504.dat
./main data_10000000-elems_0-kperct_5-lperct_1seed1650769546.dat
./main data_10000000-elems_0-kperct_5-lperct_1seed1650769961.dat

echo ""
echo "test 1 1"
# ./main data_10000000-elems_1-kperct_1-lperct_1seed1650756519.dat
./main data_10000000-elems_1-kperct_1-lperct_1seed1650769565.dat
./main data_10000000-elems_1-kperct_1-lperct_1seed1650769964.dat

echo ""
echo "test 3 3"
# ./main data_10000000-elems_3-kperct_3-lperct_1seed1650756523.dat
./main data_10000000-elems_3-kperct_3-lperct_1seed1650769571.dat
./main data_10000000-elems_3-kperct_3-lperct_1seed1650769969.dat

echo ""
echo "test 5 5"
# ./main data_10000000-elems_5-kperct_5-lperct_1seed1649432836.dat
# ./main data_10000000-elems_5-kperct_5-lperct_1seed1650756530.dat
./main data_10000000-elems_5-kperct_5-lperct_1seed1650769579.dat
./main data_10000000-elems_5-kperct_5-lperct_1seed1650769973.dat

echo ""
echo "test 50 50"
# ./main data_10000000-elems_50-kperct_50-lperct_1seed1650756534.dat
./main data_10000000-elems_50-kperct_50-lperct_1seed1650769583.dat
./main data_10000000-elems_50-kperct_50-lperct_1seed1650769977.dat
