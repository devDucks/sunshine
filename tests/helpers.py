import time
import serial
from serial.tools import list_ports

ERR_MSG = """
No Arduino or compatible devices found, check your device is connected.
If it is, check the vendor id; at the moment we support only 2341 and 1a86 vendors.
(On Linux use lsusb to list serial devices)
"""


class ArduinoError(Exception):
    pass


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

        if not self.port:
            raise ArduinoError(ERR_MSG)

    def write(self, payload):
        self.port.write(payload)
        time.sleep(0.5)

    def read_all(self):
        while not self.port.readable():
            time.sleep(0.1)

        return self.port.read_all()
