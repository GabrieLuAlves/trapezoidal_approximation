import numpy as np
import struct

from abc import ABC, abstractmethod
from time import sleep
from serial import Serial
from typing import Tuple, List
from os import system, remove


port = "COM11"
baudrade=115200
executable=".\main.exe"

class ArduinoConnection(ABC):
    @abstractmethod
    def writeArray(self, array: np.ndarray):
        ...

    @abstractmethod
    def readline(self) -> str:
        ...
    
    @abstractmethod
    def read_uint32_t(self) -> int:
        ...
    
    @abstractmethod
    def readFloat(self) -> np.float32:
        ...
    
    @abstractmethod
    def close(self):
        ...

class PySerialArduinoConnection(ArduinoConnection):
    def __init__(self, serial: Serial):
        self.serial = serial

    def writeArray(self, array: np.ndarray):
        self.serial.write(array)

    def readline(self) -> str:
        return self.serial.readline().decode("ascii")
    
    def read_uint32_t(self) -> int:
        data = self.serial.read(4)
        data, = struct.unpack("I", data)
        return data 

    def readFloat(self) -> np.float32:
        content = self.serial.read(4)
        value, = struct.unpack("f", content)

        return value

    def close(self):
        self.serial.close()

def get_pySerial_connection() -> ArduinoConnection:
    while True:
        try:
            serial = Serial(baudrate=baudrade, port=port)
            print('Arduino conectado')
            break
        except:
            pass
    
    sleep(2)
    
    return PySerialArduinoConnection(serial=serial)

def main():
    connection: ArduinoConnection = get_pySerial_connection()

    test_points = 500
    test_inputs = [
        [0, 1,                  lambda x: x],
        [0, 1,                  lambda x: x ** 2],
        [1, 3,                  lambda x: 6 * x ** 2 + 5 * x],
        [1, 10,                 lambda x: np.log(x)],
        [0, 6.283185307179586,  lambda x: np.sin(x)],
        [0, 6.283185307179586,  lambda x: np.cos(500 * x)],
    ]

    test_exact_outputs = np.array([
        +00.5,
        +00.3333333333333333,
        +72.0000000000000000,
        +14.0258509299404568,
        +00,     
        +00,
    ])

    reference_tool_outputs = np.array([
        +00.4999999999999999,
        +00.3333340026746880,
        +72.0000321283850200,
        +14.0258265327417000,
        +3.5941550175457e-16,
        -2.9265103921728e-13
    ])

    arduino_results = []

    pc_results = []

    for [a, b, function] in test_inputs:
        x = np.linspace(a, b, num=test_points, dtype=np.float32)
        f_x = function(x)

        connection.writeArray(np.array([a, b], dtype=np.float32))
        connection.writeArray(f_x)

        arduino_result = connection.readFloat()
        elapsed_time = connection.read_uint32_t()
        
        print("{:+012.8f}  {:8d}".format(arduino_result, elapsed_time))

        with open("input.bin", "wb") as file:
            file.write(np.array([a, b], dtype=np.float32))
            file.write(f_x)
        
        system(executable)

        with open("output.bin", "rb") as file:
            content = file.read(4)
        
        remove("input.bin")
        remove("output.bin")
        
        pc_result, = struct.unpack("f", content)

    connection.close()

if __name__ == "__main__":
    main()