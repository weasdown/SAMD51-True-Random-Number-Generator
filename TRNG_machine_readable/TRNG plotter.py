import matplotlib.pyplot as plt
import serial
import numpy as np

arduino = serial.Serial(port='COM3', baudrate=2e6)  # open serial port

number_of_samples = 0
sample_limit = int(1e5)  # take 100,000 samples
bins = 1000
sample_set = np.empty([sample_limit + 1], dtype=np.int64)

while number_of_samples <= sample_limit:
    data = str(arduino.readline())  # read in data until a line break character
    sample = int(data[2:len(data) - 5], 2)  # remove leading and line end characters
    sample_set[number_of_samples] = sample
    number_of_samples += 1

plt.figure()
plt.hist(sample_set, bins, histtype='step')
plt.title("Numbers generated by SAMD51 True Random Number Generator, 100,000 samples")
plt.xlabel("Generated number")
plt.xlim([0, 4294967296])
plt.ylabel("Frequency")
plt.show()

# Uncomment this section to calculate and plot the sum of adjacent samples

# bell_samples = np.empty([round(len(sample_set)/2)], dtype=np.int64)
# for i in range(0, round(len(sample_set)/2)):
#     bell_samples[i] = sample_set[i]+sample_set[i+1]
#
# plt.figure()
# plt.hist(bell_samples, bins, histtype='step')
# plt.title("Sum of two adjacent samples")
# plt.xlabel("Generated number")
# plt.xlim([0, 4294967296*2])
# plt.ylabel("Frequency")
# plt.show()
