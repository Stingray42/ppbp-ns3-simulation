#!/usr/bin/env bash

set -euo pipefail

function avg() {
  awk '{ total += $1; count++ } END { print total/count }' "$@"
}

for h in {6..9}; do
  dir="simulation_results/H0_$h"
  mkdir -p $dir
  for run in {1..10}; do
    ./ns3 run "myppbp --n=1 --h=0.$h --t=30min --RngRun=$run"
    pcap_name="ppbp_h0.$h-$run.pcap"
    mapfile -t output < <(./test.py $pcap_name)
    echo "${output[0]}" >> "$dir/iat.txt"
    echo "${output[1]}" >> "$dir/10ms.txt"
  done
  avg "$dir/iat.txt" > "$dir/iat_average.txt"
  avg "$dir/10ms.txt" > "$dir/10ms_average.txt"
done
