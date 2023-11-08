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

print("Médianes par ligne:", medians)
print("Moyennes par ligne:", means)
print("Écarts types par ligne:", stds)

plt.figure()
plt.plot(nbThreads, means, marker='o', linestyle='-', label='Mean')
plt.plot(nbThreads, medians, marker='o', linestyle='-', label='Median')
plt.errorbar(nbThreads, medians, yerr=stds, fmt='o', label='Std Dev')

plt.title('Médiane en fonction du nombre de threads')
plt.xlabel('Nombre de threads')
plt.ylabel('Médiane')
plt.legend()
plt.grid()
plt.savefig("perfs_compilation.png")
plt.savefig("perfs_compilation.pdf")
plt.show()