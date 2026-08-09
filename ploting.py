import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")
avg = df.groupby(["n", "algorithm"])["time_us"].mean().unstack()

avg.plot(figsize=(10,6))
plt.xlabel("n")
plt.ylabel("Time (micro seconds)")
plt.title("Sorting Algorithm Complexity")
plt.legend(title="Algorithm")
plt.show()