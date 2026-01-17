import subprocess
import re
from pathlib import Path
from statistics import mean

TEST_DIR = Path("tests")
EXECUTABLE = "./bin/subset_sum"
ALGORITHM = "sa"
RUNS_PER_TEST = 10

def get_target_from_file(filepath):
    content = filepath.read_text()
    match = re.search(r"Target:\s*(-?\d+)", content)
    return int(match.group(1)) if match else None

def run_benchmark():
    test_files = sorted(TEST_DIR.glob("high_n_*.in"), key=lambda f: int(f.stem.split('_')[2]))
    print(f"{'Fisier':<20} | {'N':<5} | {'Target':<12} | {'Eroare Medie (%)':<15} | {'Succes Rate'}")
    print("-" * 80)
    for test_file in test_files:
        target = get_target_from_file(test_file)
        n_val = test_file.stem.split('_')[2]
        errors = []
        successes = 0
        for _ in range(RUNS_PER_TEST):
            result = subprocess.run([EXECUTABLE, str(test_file), ALGORITHM], capture_output=True, text=True)
            match = re.search(r"Suma gasita:\s*(-?\d+)", result.stdout)
            if match:
                found_sum = int(match.group(1))
                error = abs(found_sum - target)
                errors.append(error)
                if error == 0:
                    successes += 1
        avg_error = mean(errors) if errors else 0
        rel_error_pct = (avg_error / abs(target) * 100) if target else 0
        success_rate = (successes / RUNS_PER_TEST) * 100
        print(f"{test_file.name:<20} | {n_val:<5} | {target:<12} | {rel_error_pct:>14.2f}% | {success_rate:>10.0f}%")

if __name__ == "__main__":
    run_benchmark()