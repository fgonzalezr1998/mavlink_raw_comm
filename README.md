# mavlink_raw_comm

![example workflow](https://github.com/fgonzalezr1998/mavlink_raw_comm/actions/workflows/cmake.yml/badge.svg)

C++ library to encode Mavlinkv1 packages to be sended by serial port or UDP socket to flight controller (WIP)

## ¿How to check if the digest is correct?

With the next command, you can send a binary text (hexadecimal) by udp to be read by other program (for example from python or netcat)

```
$ echo 'fe3600ff00fd02' | xxd -r -p -| nc -u localhost 14540
```