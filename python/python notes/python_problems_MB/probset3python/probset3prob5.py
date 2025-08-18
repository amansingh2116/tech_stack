'''Evaluate the quality of the random number generation
function randint() on a random binary stream generated
with it by applying the following popular randomness tests.

Frequency test: This is based on Kolmogorov-Smirnov or the
chi-square test to verify whether the distribution of the set of
numbers generated matches with uniform distribution.

Runs test: It is basically a chi-square test that examines the
runs up and down or the runs above and below the mean by
comparing the generated values to the expected values.

Autocorrelation test: This tests the correlation between
numbers and compares the sample correlation to the expected
correlation, which is zero.

Gap test: It counts the number of digits appearing between
repetitions of a particular digit and uses Kolmogorov-Smirnov
test to compare with the expected size of gaps.

Poker test: This treats the generated numbers to be grouped
together as a poker hand. Then these hands are compared to
what is expected using chi-square test'''

import numpy as np
from scipy.stats import chisquare, ks_2samp

# Generate a binary stream using randint()
binary_stream = np.random.randint(0, 2, 1000)  # Adjust the size as needed

# Frequency Test (Chi-Square Test)
observed_freq = np.bincount(binary_stream)
expected_freq = np.array([len(binary_stream) / 2, len(binary_stream) / 2])  # Expected for uniform distribution
chi2, p = chisquare(observed_freq, f_exp=expected_freq)
if p < 0.05:
    print("Failed the Chi-Square test")
else:
    print("Passed the Chi-Square test")

# Runs Test (Chi-Square Test)
runs = np.diff(np.where(np.diff(binary_stream != 0)))[0] + 1
n = len(binary_stream)
expected_runs = (2 * n - 1) / 3  # Expected number of runs for a random sequence
observed_runs = len(runs)
chi2, p = chisquare([round(observed_runs)], f_exp=[round(expected_runs)])
if p < 0.05:
    print("Failed the Runs test")
else:
    print("Passed the Runs test")

# Autocorrelation Test
autocorr = np.correlate(binary_stream, binary_stream, mode='full')
expected_autocorr = np.zeros_like(autocorr)
expected_autocorr[len(expected_autocorr) // 2] = 1
if np.array_equal(autocorr, expected_autocorr):
    print("Passed the Autocorrelation test")
else:
    print("Failed the Autocorrelation test")

# Gap Test (Kolmogorov-Smirnov Test)
gap_lengths = np.diff(np.where(np.diff(binary_stream == 1)))[0]
expected_gap_lengths = np.array([0.25 * len(binary_stream), 0.5 * len(binary_stream), 0.25 * len(binary_stream)])
ks_statistic, p = ks_2samp(gap_lengths, expected_gap_lengths)
if p < 0.05:
    print("Failed the Gap test")
else:
    print("Passed the Gap test")

# Poker Test (Chi-Square Test)
poker_hands = [binary_stream[i:i + 5] for i in range(0, len(binary_stream), 5)]
observed_poker_freq = np.bincount([tuple(hand) for hand in poker_hands])
expected_poker_freq = np.array([len(binary_stream) / 32] * 32)  # Expected for a uniform distribution
chi2, p = chisquare(observed_poker_freq, f_exp=expected_poker_freq)
if p < 0.05:
    print("Failed the Poker test")
else:
    print("Passed the Poker test")