import numpy as np



def main():
    a = 0
    b = 1
    x = np.linspace(a, b, num=500, dtype=np.float64)
    y = x * x

    with open('input.bin', 'wb') as file:
        file.write(np.array([a, b], dtype=np.float64))
        file.write(y)



if __name__ == '__main__':
    main()
