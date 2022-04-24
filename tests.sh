#!/bin/bash
echo ""
echo "test 0 5"
./main data_10000000-elems_0-kperct_5-lperct_1seed1650756504.dat

echo ""
echo "test 1 1"
./main data_10000000-elems_1-kperct_1-lperct_1seed1650756519.dat

echo ""
echo "test 3 3"
./main data_10000000-elems_3-kperct_3-lperct_1seed1650756523.dat

echo ""
echo "test 5 5"
./main data_10000000-elems_5-kperct_5-lperct_1seed1650756530.dat

echo ""
echo "test 50 50"
./main data_10000000-elems_50-kperct_50-lperct_1seed1650756534.dat