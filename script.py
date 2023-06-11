import numpy as np
import struct

from abc import ABC
from time import sleep
from serial import Serial
from typing import Tuple, List
from os import system, remove


class IArduinoConnection(ABC):
    def sendArray(self, array: np.ndarray):
        ...
    
    def readFloat(self) -> np.float32:
        ...
    
    def close(self):
        ...

class PySerialArduinoConnection(IArduinoConnection):
    def __init__(self, serial: Serial):
        self.serial = serial

    def sendArray(self, array: np.ndarray):
        self.serial.write(array)
    
    def readFloat(self) -> np.float32:
        content = self.serial.read(4)
        value, = struct.unpack("f", content)

        return value

    def close(self):
        self.serial.close()

def get_pySerial_connection():
    while True:
        try:
            serial = Serial(baudrate=115200, port="/dev/ttyUSB0")
            print('Arduino conectado')
            break
        except:
            pass
    
    sleep(2)
    
    return PySerialArduinoConnection(serial=serial)

def main():
    connection: IArduinoConnection = get_pySerial_connection()

    test_points = 513
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
        -0.0000053071700000,
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

        connection.sendArray(np.array([a, b], dtype=np.float32))
        connection.sendArray(f_x)
        arduino_result = connection.readFloat()

        with open("input.bin", "wb") as file:
            file.write(np.array([a, b], dtype=np.float32))
            file.write(f_x)
        
        system("./main")

        with open("output.bin", "rb") as file:
            content = file.read(4)
        
        remove("input.bin")
        remove("output.bin")
        
        pc_result, = struct.unpack("f", content)

        arduino_results.append(arduino_result)
        pc_results.append(pc_result)
    

    output = [
        arduino_results,
        pc_results,
        reference_tool_outputs,
        arduino_results - test_exact_outputs,
        pc_results - test_exact_outputs,
        reference_tool_outputs - test_exact_outputs
    ]

    output = np.array(output).transpose()

    for line in output:
        print('\t'.join([ "{:+10e}".format(x) for x in line ]))
    

    connection.close()

if __name__ == "__main__":
    main()