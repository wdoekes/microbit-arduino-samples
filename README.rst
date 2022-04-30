micro:bit and Arduino IDE samples
---------------------------------

At `blynkkk legacy bbc micro:bit + arduino-ide
<https://github.com/blynkkk/docs/blob/main/legacy-platform/legacy-articles/bbc-micro-bit-+-arduino-ide.md>`_
there is an extensive writeup on programming the *BBC micro:bit* using
the *Arduino IDE*.

Here, the short summary, when you're using *Ubuntu/Focal*:

- The *micro:bit* (v1) is built up of a *Nordic Semiconductor nRF51*
  CPU, and the board contains a 5x5 LED display, two buttons,
  *Bluetooth* `and more
  <https://lancaster-university.github.io/microbit-docs/device/>`_.

- **DO NOT** use *SnapCraft* for the *Arduino IDE*. The toolchain that comes
  with `Sandeep Mistry's nRF5 Arduino core
  <https://github.com/sandeepmistry/arduino-nRF5>`_ requires *i386*
  libraries. The *snap* sandbox will not be able to find
  ``libudev1:i386``. Instead, fetch the *Linux tar.gz* from the `Arduino
  downloads <https://www.arduino.cc/en/software>`_. You can sandbox it
  using *firejail* with the *arduino.profile*: `exec firejail
  --private=/home/USER/Sandbox/arduino arduino/arduino`::

    $ ls ~/Sandbox/arduino -nog
    total 125584
    lrwxrwxrwx 1        14 apr 27 21:54 arduino -> arduino-1.8.19
    drwxrwxr-x 7      4096 apr 27 22:53 Arduino
    drwxr-xr-x 9      4096 apr 27 22:04 arduino-1.8.19
    -rw-rw-r-- 1 128583740 apr 27 21:50 arduino-1.8.19-linux64.tar.xz

  The default *firejail* profile needs some adjustment::

    $ cat /etc/firejail/arduino.local
    ignore noexec ${HOME}
    include allow-python3.inc
    # this last one is needed for access to USB/hidraw
    ignore noroot

- If you've followed the `setup instructions
  <https://github.com/sandeepmistry/arduino-nRF5#installing>`_, you've:

  - added
    ``https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json``
    as board URL;
  - installed the *Nordic Semiconductor nRF5 Boards*;
  - selected said board, and selected Softdevice *S110*.

- Connect a *micro:bit* using a USB-cable. You should see it show up in
  an ``lsusb`` listing. If you don't, double check that your cable has
  data pins::

    $ lsusb | grep NXP
    Bus 001 Device 118: ID 0d28:0204 NXP ARM mbed


This should be sufficient to get the initial samples working.

Enable one of the samples in `<microbit-arduino-samples.ino>`_ by
uncommenting it, open the Serial Console, and upload it.
