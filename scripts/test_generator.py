import random
from dataclasses import dataclass
from typing import Optional, List

TEST_PATH = "tests/"

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
            self.target = sum(random.sample(S, self.soultion_count))
        else:
            S = [random.randint(self.min_val, self.max_val) for _ in range(self.n - 1)]
            my_sum = sum(random.sample(S, self.soultion_count - 1))
            S.append(self.target - my_sum)
        self.values = S

    def save(self):
        with open(f"{TEST_PATH}{self.name}.in", "w") as f:
            f.write(f"{self.n} {self.target}\n")
            f.write(" ".join(map(str, self.values)) + "\n")

test_suites = [
    TestConfig("small_pos", n=20, min_val=1, max_val=100, soultion_count=5),

    TestConfig("small_neg", n=20, min_val=-100, max_val=100, soultion_count=10),

    TestConfig("target_zero", n=25, min_val=-1000, max_val=1000, soultion_count=8, target=0),
    
    
    
    TestConfig("mitm_limit_pos", n=40, min_val=1, max_val=10**6, soultion_count=20),
    TestConfig("mitm_limit_neg", n=40, min_val=-10**5, max_val=10**5, soultion_count=21),
    
    
    TestConfig("dp_heavy_n", n=30, min_val=-1000, max_val=1000, soultion_count=10),
    TestConfig("dp_max_n", n=20, min_val=-100, max_val=100, soultion_count=7),
    
    TestConfig("sa_hard_exact", n=40, min_val=-10**6, max_val=10**6, soultion_count=16),
    TestConfig("sa_random_large", n=40, min_val=-10**4, max_val=10**4, soultion_count=24),
    
    TestConfig("no_solution_huge", n=40, min_val=10**5, max_val=10**6, soultion_count=10, target=1)
]

for test in test_suites:
    
    test.generate()
    test.save()
