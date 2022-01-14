import numpy as np
import wave
import matplotlib.pyplot as plt
from scipy.fftpack import fft

if __name__ == "__main__":
    # 先从本地获取 mp3 的 bytestring 作为数据样本
    filename = "/home/renxin/Music/a.wav"
    f = wave.open(filename, "rb")
    params = f.getparams()
    nchannels, sampwidth, framerate, nframes = params[:4]
    str_data = f.readframes(nframes)
    f.close()
    wave_data = np.fromstring(str_data, dtype = np.short)
    wave_data.shape = -1, 2
    wave_data = wave_data.T
    time = np.arange(0, nframes) / framerate

    # print(len(wave_data[0]))

    idx = 0
    plt.ion()
    while idx + 1000 < len(wave_data[0]):
        plt.cla()
        yy = fft(wave_data[0][idx:idx + 1000])
        plt.plot(abs(yy))
        plt.show()
        plt.pause(0.5)
        idx += 1000

    # plt.figure(1)
    # plt.subplot(2, 1, 1)
    # plt.plot(time, wave_data[0])
    # plt.subplot(2, 1, 2)
    # plt.plot(time, wave_data[1])
    # plt.show()