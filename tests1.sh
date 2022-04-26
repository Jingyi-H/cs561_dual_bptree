#!/bin/bash

echo "============================================================================="

echo "test 10000000 0 5: "
echo "============================================================================="
echo "trail 1: "
./main data_10000000-elems_0-kperct_5-lperct_1seed1650757063.dat 3
echo "trail 2: "
./main data_10000000-elems_0-kperct_5-lperct_1seed1650757067.dat 3
echo "trail 3: "
./main data_10000000-elems_0-kperct_5-lperct_1seed1650757069.dat 3
echo "============================================================================="

echo "test 10000000 1 1: "
echo "============================================================================="
echo "trail 1: "
./main data_10000000-elems_1-kperct_1-lperct_1seed1650757111.dat 3
echo "trail 2: "
./main data_10000000-elems_1-kperct_1-lperct_1seed1650757113.dat 3
echo "trail 3: "
./main data_10000000-elems_1-kperct_1-lperct_1seed1650757115.dat 3
echo "============================================================================="

echo "test 10000000 3 3: "
echo "============================================================================="
echo "trail 1: "
./main data_10000000-elems_3-kperct_3-lperct_1seed1650757120.dat 3
echo "trail 2: "
./main data_10000000-elems_3-kperct_3-lperct_1seed1650757123.dat 3
echo "trail 3: "
./main data_10000000-elems_3-kperct_3-lperct_1seed1650757124.dat 3
echo "============================================================================="

echo "test 10000000 5 5: "
echo "============================================================================="
echo "trail 1: "
./main data_10000000-elems_5-kperct_5-lperct_1seed1650757129.dat 3
echo "trail 2: "
./main data_10000000-elems_5-kperct_5-lperct_1seed1650757131.dat 3
echo "trail 3: "
./main data_10000000-elems_5-kperct_5-lperct_1seed1650757133.dat 3
echo "============================================================================="


echo "test 10000000 50 50: "
echo "============================================================================="
echo "trail 1: "
./main data_10000000-elems_50-kperct_50-lperct_1seed1650757138.dat 3
echo "trail 2: "
./main data_10000000-elems_50-kperct_50-lperct_1seed1650757140.dat 3
echo "trail 3: "
./main data_10000000-elems_50-kperct_50-lperct_1seed1650757142.dat 3
echo "============================================================================="