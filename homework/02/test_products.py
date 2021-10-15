#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
from pathlib import Path


def test_mm():
    mat1 = sorted([_ for _ in Path().glob('*mat1.csv')])
    mat2 = sorted([_ for _ in Path().glob('*mat2.csv')])
    vec = sorted([_ for _ in Path().glob('*vec.csv')])
    mm_prod = sorted([_ for _ in Path().glob('*mm_prod.csv')])
    mv_prod = sorted([_ for _ in Path().glob('*mv_prod.csv')])
    for m1, m2, v, mm, mv in zip(mat1, mat2, vec, mm_prod, mv_prod):
        m1 = np.genfromtxt(m1, delimiter=',')
        m2 = np.genfromtxt(m2, delimiter=',')
        v = np.genfromtxt(v, delimiter=',')
        mm = np.genfromtxt(mm, delimiter=',')
        mv = np.genfromtxt(mv, delimiter=',')
        assert np.allclose(m1 @ m2, mm, atol=1.e-1)
        assert np.allclose(m1 @ v, mv, atol=1.e-1)


if __name__ == '__main__':
    test_mm()
