import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

df = pd.read_csv(Path(__file__).parent.parent / "results2.csv")
avg = df.groupby(["n", "algorithm"])["time_ns"].mean().unstack()
avg_smooth = avg.rolling(window=20, center=True, min_periods=1).mean()

avg_smooth.plot(figsize=(10, 6))
plt.xlabel("n")
plt.ylabel("Time (nanoseconds)")
plt.title("Searching Algorithm Complexity (n=10 to 1000)")
plt.legend(title="Algorithm")
plt.show()
