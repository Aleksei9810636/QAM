import matplotlib.pyplot as plt
import pandas as pd

# Читаем CSV
df = pd.read_csv('results/error_sigma.csv')

# Строим график BER от sigma
plt.figure(figsize=(10, 6))
plt.semilogy(df['sigma'], df['ber'], 'b-o', linewidth=2, markersize=4)
plt.xlabel('Sigma (σ)')
plt.ylabel('BER (Bit Error Rate)')
plt.title('QPSK: BER vs Noise Standard Deviation')
plt.grid(True, alpha=0.3)
plt.ylim(1e-6, 1)
plt.savefig('results/ber_plot.png', dpi=150)
plt.show()
