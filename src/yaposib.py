from _yaposib import *

def vec(listOfPairs):
    vec = CoinPackedVector()
    for pair in listOfPairs:
        vec.insert(pair[0], pair[1])
    return vec

def available_solvers():
    res = []
    for solver in ["Cbc", "Clp", "Cpx", "Dylp", "Fmp", "Glpk", "Grb",
            "Msk", "Osl", "Spx", "Sym", "Vol", "Xpr"]:
        try:
            prob = Problem(solver)
            res.append(solver)
        except:
            pass
    return res

def test():
    import test_suite
    test_suite.main()

if __name__ == "__main__":
    test()
