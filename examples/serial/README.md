Example application using serial communication
==============================================

This directory contains example code of a controlled vehicle application that communicate using a UART.
Each application consists of:

- A ground control station.
- A remote operated vehicle.

Ground control sends commands to the vehicle and vehicle answers and sends reports periodically.


Virtual serial port configuration
---------------------------------

1. Determine real ports in the system

~~~bash
ls /dev/tty*
~~~

2. Connect real port to virtual port (replace `/dev/realport` for the real port, for example `/dev/tty0`).

~~~bash
sudo socat -d -d pty,raw,echo=0,link=/dev/virtualport,group-late=dialout,mode=660 pty,raw,echo=0,link=/dev/tty0,group-late=dialout,mode=660
~~~
