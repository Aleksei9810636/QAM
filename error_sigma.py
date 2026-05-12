import matplotlib.pyplot as plt
import pandas as pd

# Читаем данные
df = pd.read_csv('results/error_sigma.csv')

# Строим график
plt.figure(figsize=(10, 6))
plt.plot(df['sigma'], df['ber'], 'b-o', linewidth=2, markersize=6)

plt.xlabel('Sigma (σ)', fontsize=12)
plt.ylabel('BER (Bit Error Rate)', fontsize=12)

plt.title('QPSK: BER vs Noise Level', fontsize=14)
plt.grid(True, alpha=0.3)


plt.tight_layout()
plt.savefig('results/ber_plot.png', dpi=150)
plt.show()