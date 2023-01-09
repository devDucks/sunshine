import time
from typing import Tuple, Union

import serial
from serial.tools import list_ports


class ArduinoError(Exception):
    msg = ""


class Arduino:
    vendors = [0x2341, 0x1a86]
    port = None

    def __init__(self):
        ports = list_ports.comports()

        for port in ports:
            if port.vid in self.vendors:
                self.port = serial.Serial(port.device, 9600, write_timeout=2, timeout=2)

                # Wait for the port to init completely
                time.sleep(2)
                break

        if not port:
            raise ArduinoError()

    def write(self, payload):
        self.port.write(payload)
        time.sleep(0.5)

    def read_all(self):
        while not self.port.readable():
            time.sleep(0.1)

        return self.port.read_all()
