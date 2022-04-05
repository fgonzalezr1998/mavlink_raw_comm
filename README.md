# Mavlink Raw Communication

![example workflow](https://github.com/fgonzalezr1998/mavlink_raw_comm/actions/workflows/cmake.yml/badge.svg)

## Summary

C++ library to encode/decode Mavlinkv1 packages to be sended by serial port or UDP socket to flight controller or to be read (WIP)

* **Mainteiner status:** Mainteined
* **Mainteiner:** Fernando González Ramos <fergonzaramos@yahoo.es>
* **Author:** Fernando González <fergonzaramos@yahoo.es>
* **License:** BSD

> NOTE: Work In Progress

## How to Build

* Clone this repository and move inside it

* ``$ cd mavlink_raw_comm``

* Compile the source code. You can compile in two ways:

	* Manually:

		```
		$ mkdir build && cd build
		$ cmake ..
		$ make
		```
		In this point, the source code will be compiled but not installed. To install it:

		```
		$ make install
		```
		Two directories will be created in the project root: *bin* (where *main* program will be found), and *lib* (where the static libraries will be stored)

	* Automatic compilation and installation:

		```
		$ ./build_and_install.sh
		```