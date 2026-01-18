import subprocess
import re
from pathlib import Path
from statistics import mean

TEST_DIR = Path("tests")
EXECUTABLE = "./bin/subset_sum"
ALGORITHM = "sa"
RUNS_PER_TEST = 10

def get_target_from_file(filepath):
    with open(filepath, 'r') as f:
        first_line = f.readline()
        parts = first_line.strip().split()
        if len(parts) < 2:
            return None
        try:
            return int(parts[1])
        except ValueError:
            return None

def run_benchmark():
    # Support both high_n_* and hard_sa_* tests
    test_files = list(TEST_DIR.glob("high_n_*.in")) + list(TEST_DIR.glob("hard_sa_*.in"))
    def extract_n(fname):
        # For high_n_XXX: n is at index 2, for hard_sa_XXX: n is at index 2
        parts = fname.stem.split('_')
        for p in parts:
            if p.isdigit():
                return int(p)
        return -1
    test_files = sorted(test_files, key=extract_n)
    print(f"{'Fisier':<25} | {'N':<5} | {'Target':<12} | {'Eroare Medie (%)':<15} | {'Succes Rate'}")
    print("-" * 90)
    for test_file in test_files:
        target = get_target_from_file(test_file)
        n_val = extract_n(test_file)
        errors = []
        successes = 0
        for _ in range(RUNS_PER_TEST):
            result = subprocess.run([EXECUTABLE, str(test_file), ALGORITHM, "debug"], capture_output=True, text=True)
            # Match both 'Closest sum found:' and 'Exact sum found:'
            match = re.search(r"(?:Closest sum found:|Exact sum found:)\s*(-?\d+)", result.stdout)
            if match:
                found_sum = int(match.group(1))
                error = abs(found_sum - target)
                errors.append(error)
                if error == 0:
                    successes += 1
        avg_error = mean(errors) if errors else 0
        rel_error_pct = (avg_error / abs(target) * 100) if target else 0
        success_rate = (successes / RUNS_PER_TEST) * 100
        print(f"{test_file.name:<25} | {n_val:<5} | {target:<12} | {rel_error_pct:>14.2f}% | {success_rate:>10.0f}%")

if __name__ == "__main__":
    run_benchmark()