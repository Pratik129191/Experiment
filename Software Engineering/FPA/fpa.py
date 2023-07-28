def isRatio(inp: str):
    if ':' in inp:
        return True
    return False


def convertInRatio(inp: str):
    if inp.upper()[0] == 'S':
        return "1:0:0"
    if inp.upper()[0] == 'A':
        return "0:1:0"
    if inp.upper()[0] == 'C':
        return "0:0:1"
    return "0:0:0"


def convertIfContainsPercentage(inp: str):
    if '%' in inp:
        return float(inp[:-1]) / 100
    return float(inp)


def distributeFactorsByRatio(inp: str, factor):
    inp = [int(i) for i in inp.split(':')]
    inp = [((i * factor) / sum(inp)) for i in inp]
    return inp


def processAccordingToRatio(inp: str, factor):
    if isRatio(inp):
        return distributeFactorsByRatio(inp, factor)
    else:
        return distributeFactorsByRatio(convertInRatio(inp), factor)


def takeInputAndProcess():
    final = {
        'simple': {
            'wf': 0.5
        },
        'average': {
            'wf': 1.0
        },
        'complex': {
            'wf': 1.5
        },
        'chars': {}
    }
    x = "ENTER"
    while x.upper() != 'EXIT':
        func_name = input("Enter The Function Point Name:\t").upper()
        func_val = int(input(f"Value For {func_name} FP:\t"))
        ratio = input(f"Ratio For {func_name} FP:\t")
        temp = processAccordingToRatio(ratio, func_val)
        final['simple'][func_name] = temp[0]
        final['average'][func_name] = temp[1]
        final['complex'][func_name] = temp[1]
        x = input("Type 'EXIT' to Stop Giving Input (Else Hit Enter):\t")

    for i in range(int(input("How Many Types of Characteristics are There:\t"))):
        name = input("Enter The Characteristic's Name:\t")
        final['chars'][name] = convertIfContainsPercentage(input(f"Value of {name} is:\t"))

    return final


def calculateTotalPoints(final: dict):
    final['simple']['total'] = sum(list(final['simple'].values())) - final['simple']['wf']
    final['simple']['total_wf'] = final['simple']['total'] * final['simple']['wf']
    final['average']['total'] = sum(list(final['average'].values())) - final['average']['wf']
    final['average']['total_wf'] = final['average']['total'] * final['average']['wf']
    final['complex']['total'] = sum(list(final['complex'].values())) - final['complex']['wf']
    final['complex']['total_wf'] = final['average']['total'] * final['complex']['wf']


def calculateUFP(final: dict):
    final['UFP'] = (
            final['simple']['total_wf'] +
            final['complex']['total_wf'] +
            final['average']['total_wf']
    )


def calculateTDI(final: dict):
    final['TDI'] = sum(final['chars'].values())


def calculateVAF(final: dict):
    final['VAF'] = (final['TDI'] * 0.01) + 0.65


def calculateAFP(final: dict):
    final['AFP'] = final['VAF'] * final['UFP']


table = takeInputAndProcess()
calculateTotalPoints(final=table)
calculateUFP(final=table)
calculateTDI(final=table)
calculateVAF(final=table)
calculateAFP(final=table)

print(f"UFP is:\t{table['UFP']}")
print(f"TDI is:\t{table['TDI']}")
print(f"VAF is:\t{table['VAF']}")
print(f"AFP is:\t{table['AFP']}")
