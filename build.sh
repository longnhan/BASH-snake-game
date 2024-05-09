#!/bin/bash

echo "User name: $USER"

echo "-----------------------"
echo "|- COMPILING PROJECT -|"
echo "-----------------------"

CUR_DIR=${PWD}

echo "Current directory: $CUR_DIR"

mkdir -p $CUR_DIR/result

cd $CUR_DIR/result/
rm -r *

echo "Choose your build type 1: Release | 2: Debug"
read COMPL_TYPE

case $COMPL_TYPE in
    1)
        echo "Building release version..."
        cmake -DCMAKE_BUILD_TYPE=Release ..
    ;;
    2)
        echo "Building debug version..."
        cmake -DCMAKE_BUILD_TYPE=Debug ..
    ;;
    *)
        echo "Invalid option"
        exit 1
    ;;
esac

make

echo "-----------------------"
echo "|-- FINISH COMPILING -|"
echo "-----------------------"