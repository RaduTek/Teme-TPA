from typing import List


def modExp(base: int, pow: int, mod: int) -> int:
    result = 1
    while pow > 0:
        if pow % 2:
            result = (result * base) % mod
        base = (base * base) % mod
        pow /= 2

    return result


def modInv(base: int, mod: int) -> int:
    return modExp(base, mod - 2, mod)


def combinations_modinv(n: int, k: int, mod: int, factorials: List[int]) -> int:
    n_f = factorials[n % mod]
    k_f = factorials[k % mod]
    nk_f = factorials[(n - k) % mod]

    p = (k_f * nk_f) % mod
    return (n_f * modInv(p, mod)) % mod


def combinations_reg(n: int, k: int, mod: int, factorials: List[int]) -> int:
    n_f = factorials[n % mod]
    k_f = factorials[k % mod]
    nk_f = factorials[(n - k) % mod]

    p = (k_f * nk_f) % mod
    return (n_f / p) % mod


def combinations_factinv(
    n: int, k: int, mod: int, factorials: List[int], inverses: List[int]
) -> int:
    return (factorials[n] * inverses[k] % mod) * inverses[n - k] % mod


def precalc_fact_inv(mod: int) -> tuple[List[int], List[int]]:
    factorials = [1, 1]

    for i in range(2, mod + 1):
        factorials += [(factorials[i - 1] * i) % mod]

    inverses = [1] * (mod + 1)
    inverses[mod] = modInv(factorials[mod], mod)
    for i in range(mod - 1, 0, -1):
        inverses[i] = (inverses[i + 1] * (i + 1)) % mod

    return factorials, inverses


p = 13

a = 3
b = 3

factorials, inverses = precalc_fact_inv(p)

print(combinations_factinv(a, b, p, factorials, inverses))
