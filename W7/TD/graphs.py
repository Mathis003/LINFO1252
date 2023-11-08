from matplotlib import pyplot as plt
import pandas as pd

data = pd.read_csv("mesures.csv")
nbThreads = data['NbThreads']
data = data.drop(columns="NbThreads")

medians = []
means = []
stds = []

for index, row in data.iterrows():
    medians.append(row.median())
    means.append(row.mean())
    stds.append(row.std())

#print("Médianes par ligne:", medians)
#print("Moyennes par ligne:", means)
#print("Écarts types par ligne:", stds)

plt.figure()
plt.plot(nbThreads, means, marker='o', markersize=6, color='blue', linestyle='-', label='Mean')
plt.scatter(nbThreads, medians, color='green', label='Median', s=40)
plt.errorbar(nbThreads, medians, yerr=stds, fmt='o', markersize=5, color='red', label='Std Dev')
plt.title('Compilation Time Performance Metrics vs. Number of Threads')
plt.xlabel('Number of Threads []')
plt.ylabel('Execution Time [sec]')
plt.legend()
plt.grid()
plt.savefig("perfs_compilation.png")
plt.savefig("perfs_compilation.pdf")
plt.show()