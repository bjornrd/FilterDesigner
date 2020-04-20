# This Python file uses the following encoding: utf-8

# python -m pip install --user numpy scipy matplotlib ipython jupyter pandas sympy nose

from scipy.fft import fft, ifft, fftfreq, fftshift
from matplotlib import pyplot as plt
import numpy as np

if __name__ == "__main__":
    a = [1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0]
    b = fft(a);
    c = ifft(b).real;

    print(a)
    print(b)

    mag     = np.sqrt(b.real*b.real + b.imag*b.imag)
    phase   = np.arctan2(b.imag,b.real);

    plt.plot(b)
    plt.plot(c)
    plt.plot(mag)
    plt.plot(phase)
    plt.legend(['fft', 'ifft', 'fft.magnitude', 'fft.phase'])
    plt.grid()
    plt.show()
