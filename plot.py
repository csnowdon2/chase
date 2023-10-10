import matplotlib.pyplot as plt
import pandas as pd
import sys
import csv

df = pd.read_csv(sys.stdin)

for size in df['size'].unique():
    data = df[df['size'] == size]
    plt.plot(data['stride'], data['latency'],label=str(size/1024)+'KB')

plt.xlabel("Stride (bytes)")
plt.ylabel("Latency (ns)")

plt.xscale("log",base=2)
plt.gca().set_ylim(bottom=0)
plt.legend(bbox_to_anchor=(1.04,0.5), loc="center left")
plt.savefig('graph.png', bbox_inches = "tight")
