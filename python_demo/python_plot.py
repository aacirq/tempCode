import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    n, f = 1.0, 3.0
    x = np.linspace(1, 3, 100)
    y = np.zeros(x.shape)
    for i in range(len(x)):
        y[i] = n + f - n * f / x[i] - x[i]
    plt.plot(x, y, '-')
    plt.show()
    