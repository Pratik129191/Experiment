def takeInput():
    module = {
        'input': {},
        'output': {},
        'hk': {}
    }
    x = 'ENTER'
    while x.upper() != 'EXIT':
        temp = []
        name = input("Enter The Module Name:\t")
        module['input'][name] = float(input("Enter The INPUT Value:\t"))
        module['output'][name] = float(input("Enter The OUTPUT Value:\t"))
        module['hk'][name] = (module['input'][name] * module['output'][name]) ** 2
        x = input("Type 'EXIT' To Stop Giving Input (Else hit Enter):\t")
    return module


module = takeInput()
print(f"HK value for whole program is:\t{sum(module['hk'].values())}")
