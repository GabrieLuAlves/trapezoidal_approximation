import numpy as np


tests_data = np.array([
    [lambda x: x,                   0.0,    1.0,                +00.4999999999999999, 00.5000000000000000],
    [lambda x: x ** 2,              0.0,    1.0,                +00.3333340026746880, 00.3333333333333333],
    [lambda x: 6 * x ** 2 + 5 * x,  1.0,    3.0,                +72.0000321283850200, 72.0000000000000000],
    [lambda x: np.log(x),           1.0,    10.0,               +14.0258265327417000, 14.0258509299404568],
    [lambda x: np.sin(x),           0.0,    6.283185307179586,  +3.5941550175457e-16, 00.0000000000000000],
    [lambda x: np.cos(500 * x),     0.0,    6.283185307179586,  -2.9265103921728e-13, -0.0000053071700000]
])

def main():
    with open('input.bin', 'wb') as file:
        file.write(np.uint32(len(tests_data)))
        for [function, a, b, tool_results, exact_results] in tests_data:
            x = np.linspace(a, b, num=500, dtype=np.float64)

            constants = np.array([exact_results, tool_results, a, b], dtype=np.float64)
            y = function(x)

            data = np.concatenate((constants, y))

            file.write(data)

            expected = np.sum(y[1:-1])
            expected += (y[0] + y[-1]) / 2.0
            expected *= (x[-1] - x[0]) / 499.0

        file.close()


if __name__ == '__main__':
    main()