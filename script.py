import numpy as np
import struct

from time import sleep
from serial import Serial
from os import system, remove

port = "/dev/ttyUSB0"
baudrate = 115200


class Test:
    def __init__(self, x, function, a, b, exact_result, tool_approximation):
        assert len(x) == 500, "The array must be 500-elements long"
        
        self.y = function(x)
        self.a = a
        self.b = b
        self.exact_result = exact_result
        self.tool_approximation = tool_approximation
    
    def generate_report(self, serial):
        
        serial.write("{:.16f}\n".format(self.a).encode("ascii"))
        #response = serial.readline()
        serial.write("{:.16f}\n".format(self.b).encode("ascii"))
        #response = serial.readline()

        for number in self.y:
            serial.write("{:.16f}\n".format(number).encode("ascii"))
            #response = serial.readline()
            # print("{:.4f} {}".format(number, response))
        
        arduino_result, = struct.unpack("f", serial.read(4))

        with open("input.bin", "wb") as file:
            file.write(np.array([self.a, self.b], dtype=np.float32))
            file.write(self.y)
        
        system("./main")

        pc_result = 0

        with open("output.bin", "rb") as file:
            pc_result, = struct.unpack("f", file.read(4))

        remove("input.bin")
        remove("output.bin")

        return np.array([
            arduino_result,
            pc_result,
            self.exact_result,
            self.exact_result - arduino_result,
            self.exact_result - pc_result,
            self.exact_result - self.tool_approximation
        ])

def getArduinoConnection():
    while True:
        try:
            serial = Serial(port, baudrate)
            print('Arduino conectado')
            break
        except:
            pass
    
    sleep(2)
    
    return serial

def main():
    connection = getArduinoConnection()

    tests = [
        Test(
            x=np.linspace(0, 1, num=500, dtype=np.float32),
            a=0,
            b=1,
            function=lambda x: x,
            exact_result=0.5,
            tool_approximation=0.4999999999999999
        ),
        Test(
            x=np.linspace(0, 1, num=500, dtype=np.float32),
            a=0,
            b=1,
            function=lambda x: x ** 2,
            exact_result=0.3333333333333333,
            tool_approximation=0.3333340026746880
        ),Test(
            x=np.linspace(1, 3, num=500, dtype=np.float32),
            a=1,
            b=3,
            function=lambda x: 6 * x ** 2 + 5 * x,
            exact_result=72.0000000000000000,
            tool_approximation=72.0000321283850200
        ),Test(
            x=np.linspace(1, 10, num=500, dtype=np.float32),
            a=1,
            b=10,
            function=lambda x: np.log(x),
            exact_result=14.0258509299404568,
            tool_approximation=14.0258265327417000
        ),Test(
            x=np.linspace(0, 6.283185307179586, num=500, dtype=np.float32),
            a=0,
            b=6.283185307179586,
            function=lambda x: np.sin(x),
            exact_result=0,
            tool_approximation=3.5941550175457e-16
        ),Test(
            x=np.linspace(0, 6.283185307179586, num=500, dtype=np.float32),
            a=0,
            b=6.283185307179586,
            function=lambda x: np.cos(500 * x),
            exact_result= -0.0000053071700000,
            tool_approximation=-2.9265103921728e-13
        ),
    ]

    results = np.array([ test.generate_report(serial=connection) for test in tests ])
    
    for [ arduino_result, pc_result, actual_area, arduino_error, pc_error, tool_error ] in results:
        print("{:+.10e}\t{:+.10e}\t{:+.10e}\t{:+.10e}\t{:+.10e}\t{:+.10e}".format(arduino_result, pc_result, actual_area, arduino_error, pc_error, tool_error))

    connection.close()

if __name__ == "__main__":
    main()