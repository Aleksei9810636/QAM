import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('results/points.csv', header=None, names=['I', 'Q'])

plt.figure(figsize=(8, 8))
plt.scatter(df['I'], df['Q'], s=10, alpha=0.7, c='blue', marker='.')

plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.grid(True, alpha=0.3)
plt.xlabel('I (синфазная компонента)')
plt.ylabel('Q (квадратурная компонента)')
plt.title('Созвездие QPSK с шумом')
plt.axis('equal')

plt.savefig('results/constellation.png', dpi=150)
# plt.show()