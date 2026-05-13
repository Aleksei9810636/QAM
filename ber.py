import matplotlib.pyplot as plt
import pandas as pd

files = [
    ('results/error_sigma_qpsk.csv', 'QPSK', 'results/ber_qpsk.png'),
    ('results/error_sigma_qam16.csv', 'QAM16', 'results/ber_qam16.png'),
    ('results/error_sigma_qam64.csv', 'QAM64', 'results/ber_qam64.png')
]

for csv_file, title, output_file in files:
    try:
        df = pd.read_csv(csv_file)
        
        plt.figure(figsize=(10, 6))
        plt.plot(df['sigma'], df['ber'], 'b-o', linewidth=2, markersize=6)
        
        plt.xlabel('Sigma (σ)', fontsize=12)
        plt.ylabel('BER (Bit Error Rate)', fontsize=12)
        plt.title(f'{title}: BER vs Noise Level', fontsize=14)
        plt.grid(True, alpha=0.3)
        plt.tight_layout()
        
        plt.savefig(output_file, dpi=150)
        plt.close()
            
    except FileNotFoundError:
        print(f"Файл не найден: {csv_file}")
    except Exception as e:
        print(f"Ошибка при обработке {csv_file}: {e}")