#!/usr/bin/env python3
import os.path
import sys

import numpy as np
from dpkt.pcap import Reader
from tqdm import tqdm, trange

if len(sys.argv) < 2:
    print('Usage:', os.path.basename(sys.argv[0]), 'PATH', file=sys.stderr)
    print(file=sys.stderr)
    print('Error: path to pcap file is not specified.', file=sys.stderr)
    exit(1)

path = sys.argv[1]

prev_time = 0
inter_arrival_times = []
step = 0.010  # 10ms
time_series = []
with open(path, 'rb') as f:
    for time, _ in tqdm(Reader(f), unit=' packets', desc='Read file'):
        inter_arrival_time = float(time - prev_time)
        inter_arrival_times.append(inter_arrival_time)
        prev_time = time

        idx = int(np.floor(time / step))
        while idx != len(time_series) - 1:
            time_series.append(0)
        time_series[idx] += 1


def aggvar(series):
    n = 50
    m_values = np.logspace(0, np.log10(len(series) // 5), n)
    variances = np.zeros(n)
    for i in trange(n, desc='Calculate'):
        n_sections = len(series) // m_values[i]
        aggregated = np.array_split(series, n_sections)
        aggregated = [np.mean(i) for i in aggregated]
        variances[i] = np.var(aggregated)

    poly = np.polyfit(np.log10(m_values), np.log10(variances), 1)
    beta = -poly[0]
    H = 1 - beta / 2

    return H


print(aggvar(inter_arrival_times))
print(aggvar(time_series))
