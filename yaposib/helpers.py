import _yaposib
import exceptions

class YaposibVectorError(exceptions.Exception):
    def __init__(self):
        return
    def __str__(self):
        print("Error inserting element in vector. Twice the same index?")

def vec(listOfPairs):
    vec = _yaposib.CoinPackedVector()
    for pair in listOfPairs:
        try:
            vec.insert(pair[0], pair[1])
        except:
            raise YaposibVectorError
    return vec

def available_solvers():
    res = []
    for solver in ["Cbc", "Clp", "Cpx", "Dylp", "Fmp", "Glpk", "Grb",
            "Msk", "Osl", "Spx", "Sym", "Vol", "Xpr"]:
        try:
            prob = _yaposib.Problem(solver)
            res.append(solver)
        except:
            pass
    return res
