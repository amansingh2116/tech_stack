'''Write a program to generate a set of random samples drawn
from the following distributions:
Symmetric Gaussian distribution with the value of skewness as
0 (zero).
Right-skewed Gaussian distribution with the value of skewness
as positive and given as user input.
Left-skewed Gaussian distribution with the value of skewness
as negative and given as user input.'''
import numpy as np

mean = float(input("Enter the mean: "))
std_dev = float(input("Enter the standard deviation: "))
sample_size = int(input("Enter the sample size: "))

samples1 = np.random.normal(mean, std_dev, sample_size)
print("Random samples from symmetric Gaussian distribution:")
print(samples1)

skewness1 = float(input("Enter the positive skewness value: "))
samples2 = np.random.normal(mean, std_dev, sample_size)
shifted_samples1 = samples2 + abs(skewness1) * samples2
print("Random samples from positive skewed Gaussian distribution:")
print(shifted_samples1)

skewness2 = float(input("Enter the negative skewness value: "))
samples3 = np.random.normal(mean, std_dev, sample_size)
shifted_samples2 = samples3 - abs(skewness2) * samples3
print("Random samples from negative skewed Gaussian distribution:")
print(shifted_samples2)