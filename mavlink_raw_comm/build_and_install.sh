#! /bin/sh

rm -rf build bin lib 2> /dev/null

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

make test

if [ $? -ne 0 ]
then
  exit $?
fi

make install

exit $?