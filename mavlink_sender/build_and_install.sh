#! /bin/sh

if [ -d build ]
then
  rm -rf build
fi

mkdir build && cd build
cmake ..

if [ $? -ne 0 ]
then
  exit $?
fi

make -j1

if [ $? -ne 0 ]
then
  exit $?
fi

make install

exit $?