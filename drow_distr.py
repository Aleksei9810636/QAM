import matplotlib.pyplot as plt
import pandas as pd

files = [
    ('results/points_QPSK.csv', 'QPSK'),
    ('results/points_QAM16.csv', 'QAM16'),
    ('results/points_QAM64.csv', 'QAM64')
]

fig, axes = plt.subplots(1, 3, figsize=(18, 6))

for ax, (filename, title) in zip(axes, files):
    try:
        df = pd.read_csv(filename, header=None, names=['I', 'Q'])
        
        ax.scatter(df['I'], df['Q'], s=5, alpha=0.5, c='blue', marker='.')
        ax.axhline(0, color='black', linewidth=0.5)
        ax.axvline(0, color='black', linewidth=0.5)
        ax.grid(True, alpha=0.3)
        ax.set_xlabel('I')
        ax.set_ylabel('Q')
        ax.set_title(f'{title}\n({filename})')
        ax.axis('equal')
                
    except FileNotFoundError:
        ax.text(0.5, 0.5, f'Файл не найден:\n{filename}', 
                ha='center', va='center', transform=ax.transAxes)
        ax.set_title(title)
        print(f"Файл не найден: {filename}")

plt.tight_layout()
plt.savefig('results/pioints_all.png', dpi=150)
