#!/bin/bash

echo "test 10000000 0 5: "
./main data_10000000-elems_0-kperct_5-lperct_1seed1649431990.dat

echo "test 10000000 5 5: "
./main data_10000000-elems_5-kperct_5-lperct_1seed1649432006.dat

echo "test 10000000 10 5: "
./main data_10000000-elems_10-kperct_5-lperct_1seed1649432012.dat

echo "test 10000000 25 5: "
./main data_10000000-elems_25-kperct_5-lperct_1seed1649432021.dat

echo "test 10000000 50 5: "
./main data_10000000-elems_50-kperct_5-lperct_1seed1649432025.dat

echo "test 10000000 5 10: "
./main data_10000000-elems_5-kperct_10-lperct_1seed1649435825.dat

echo "test 10000000 5 25: "
./main data_10000000-elems_5-kperct_25-lperct_1seed1649435835.dat

echo "test 10000000 5 50: "
./main data_10000000-elems_5-kperct_50-lperct_1seed1649435951.dat

