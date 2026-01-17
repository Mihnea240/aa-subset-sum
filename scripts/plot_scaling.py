import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def plot(csv_file, output_path):
    df = pd.read_csv(csv_file)
    df['Method'] = df['command'].apply(lambda x: 'MITM' if 'mitm' in x else 'DP')

    plt.figure(figsize=(10, 6))
    for method in df['Method'].unique():
        subset = df[df['Method'] == method].sort_values('parameter_n')
        plt.plot(subset['parameter_n'], subset['mean'], marker='o', label=method)

    plt.yscale('log')
    plt.xlabel('Number of Elements (N)')
    plt.ylabel('Mean Execution Time (s)')
    plt.title('Performance Scaling: MITM vs DP')
    plt.legend()
    plt.grid(True, which="both", ls="-", alpha=0.2)
    
    # Ensure directory exists and save
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    plt.savefig(output_path, dpi=300)
    print(f"Graph saved to: {output_path}")

if __name__ == "__main__":
    # Usage: python plot_scaling.py <input.csv> <output.png>
    plot(sys.argv[1], sys.argv[2])