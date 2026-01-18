
import random
from dataclasses import dataclass, asdict
from typing import Optional, List
import json
import os

TEST_PATH = "tests/"
JSON_PATH = "bench_results/"

random.seed(42)


@dataclass
class TestConfig:
    name: str
    n: int
    min_val: int
    max_val: int
    soultion_count: int
    target: Optional[int] = None  # If None, we generate one
    values: List[int] = None

    def generate(self):
        if self.target is None:
            S = [random.randint(self.min_val, self.max_val) for _ in range(self.n)]
            t = sum(random.sample(S, self.soultion_count))
            self.target = abs(t) if t <= 0 else t
        else:
            # Always enforce positive target
            t = self.target if self.target > 0 else abs(self.target) + 1
            S = [random.randint(self.min_val, self.max_val) for _ in range(self.n - 1)]
            my_sum = sum(random.sample(S, self.soultion_count - 1))
            S.append(t - my_sum)
            self.target = t
        self.values = S


    def save(self):
        # Save .in file
        with open(f"{TEST_PATH}{self.name}.in", "w") as f:
            f.write(f"{self.n} {self.target}\n")
            f.write(" ".join(map(str, self.values)) + "\n")
        # Save .json file for plotting/analysis
        os.makedirs(JSON_PATH, exist_ok=True)
        data = {
            "name": self.name,
            "n": self.n,
            "min_val": self.min_val,
            "max_val": self.max_val,
            "solution_count": self.soultion_count,
            "target": self.target,
            "values": self.values
        }
        with open(f"{JSON_PATH}{self.name}.json", "w") as jf:
            json.dump(data, jf, indent=2)


test_suites = []

# --- CATEGORIA 1: Baseline & MITM Stress (10 teste) ---
# Focus: N crește de la 20 la 42. MITM ar trebui să domine, apoi să "gâfâie".
for i in range(0, 10):
    n_val = 20 + (i * 2) # N: 20, 22, ..., 38
    test_suites.append(
        TestConfig(f"mitm_bench_{n_val}", n=n_val, min_val=-1000, max_val=1000, soultion_count=n_val//2)
    )

# --- CATEGORIA 2: DP & T-Range Stress (10 teste) ---
# Focus: N fix (30), dar Target-ul crește. Demonstrează natura pseudo-polinomială a DP.
for i in range(1, 11):
    magnitude = 10**i if i < 7 else 10**6 # T până la 10^6 conform cerinței tale
    test_suites.append(
        TestConfig(f"dp_magnitude_{magnitude}", n=30, min_val=-magnitude, max_val=magnitude, soultion_count=15)
    )

# --- CATEGORIA 3: High-N & SA Zone (10 teste) ---
# Focus: N crește de la 100 la 1000. MITM moare, DP moare dacă T e mare, SA supraviețuiește.
for i in range(1, 11):
    n_val = i * 100 # N: 100, 200, ..., 1000
    # Alternăm între target generat și target fix (0)
    t_val = 0 if i % 2 == 0 else None 
    test_suites.append(
        TestConfig(f"high_n_{n_val}", n=n_val, min_val=-1000, max_val=1000, soultion_count=n_val//4, target=t_val)
    )
    
# --- CATEGORIA 4: Hard SA Tests (n < 1000, mix of with/without solution) ---
for i in range(1, 6):
    n_val = 200 + i * 150  # N: 350, 500, 650, 800, 950
    if n_val >= 1000:
        continue
    min_val = -10**6
    max_val = 10**6
    if i % 2 == 1:
        # With guaranteed solution
        test_suites.append(
            TestConfig(f"hard_sa_{n_val}_sol", n=n_val, min_val=min_val, max_val=max_val, soultion_count=n_val//3, target=None)
        )
    else:
        # Random positive target, possibly unreachable
        target = random.randint(1, n_val * max_val)
        test_suites.append(
            TestConfig(f"hard_sa_{n_val}_nosol", n=n_val, min_val=min_val, max_val=max_val, soultion_count=n_val//3, target=target)
        )

# Rulare generare
for test in test_suites:
    test.generate()
    test.save()
