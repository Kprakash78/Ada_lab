import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

df = pd.read_csv(Path(__file__).parent / "results7.csv")

# Pivot the dataframe for grouped bar chart
pivot_df = df.pivot(index='n', columns='algorithm', values='time_us')

pivot_df.plot(kind='bar', figsize=(10, 6))
plt.xlabel("Matrix size (n x n)")
plt.ylabel("Time (microseconds)")
plt.title("Matrix Multiplication: Naive vs Strassen (n=3 to 8)")
plt.legend(title="Algorithm")
plt.xticks(rotation=0)
plt.tight_layout()
plt.show()
