import matplotlib.pyplot as plt
import pandas as pd
import sys

data = pd.read_csv(sys.stdin.read())
print(data)

