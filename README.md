# ppbp-ns3-simulation

Hurst exponent estimation of network traffic trace generated with ns-3 simulator and Poisson Pareto Burst Process model 
implementation https://github.com/sharan-naribole/PPBP-ns3. Generate pcap traffic trace with given Hurst exponent set as 
PPBP model parameter (Pareto distribution shape parameter), estimate Hurst exponent using aggregated variances method for
inter-arrival times and packet counts per 10 ms, and calculate the average values for 10 experiments.

## Instructions

* See https://github.com/sharan-naribole/PPBP-ns3#instructions

* Copy `test.py` and `run.sh` files to root folder of ns-3 installation

* Execute `./run.sh` command

## Results

### Inter-arrival times

|             | H=0.6      | H=0.7      | H=0.8      | H=0.9      |
|-------------|------------|------------|------------|------------|
| 1           | 0.6420     | 0.6882     | 0.7345     | 0.7667     |
| 2           | 0.6714     | 0.7109     | 0.7605     | 0.8176     |
| 3           | 0.6584     | 0.7079     | 0.7480     | 0.7921     |
| 4           | 0.6248     | 0.6682     | 0.7250     | 0.7731     |
| 5           | 0.6761     | 0.7215     | 0.7742     | 0.8348     |
| 6           | 0.6229     | 0.6485     | 0.6894     | 0.7357     |
| 7           | 0.6505     | 0.6908     | 0.7352     | 0.7893     |
| 8           | 0.6275     | 0.6688     | 0.7182     | 0.7693     |
| 9           | 0.6306     | 0.6667     | 0.7195     | 0.7827     |
| 10          | 0.6344     | 0.6681     | 0.7096     | 0.7536     |
| **Average** | **0.6439** | **0.6840** | **0.7314** | **0.7815** |

### Packet counts per 10 ms

|             | H=0.6      | H=0.7      | H=0.8      | H=0.9      |
|-------------|------------|------------|------------|------------|
| 1           | 0,6792     | 0,7188     | 0,7610     | 0,7993     |
| 2           | 0,7002     | 0,7463     | 0,8011     | 0,8581     |
| 3           | 0,6779     | 0,7404     | 0,7794     | 0,8192     |
| 4           | 0,6606     | 0,7056     | 0,7627     | 0,8110     |
| 5           | 0,7134     | 0,7574     | 0,8128     | 0,8632     |
| 6           | 0,6538     | 0,6839     | 0,7205     | 0,7721     |
| 7           | 0,6881     | 0,7291     | 0,7775     | 0,8394     |
| 8           | 0,6442     | 0,7014     | 0,7469     | 0,8157     |
| 9           | 0,6670     | 0,7034     | 0,7617     | 0,8159     |
| 10          | 0,6565     | 0,6936     | 0,7516     | 0,7907     |
| **Average** | **0,6741** | **0,7180** | **0,7675** | **0,8185** |
