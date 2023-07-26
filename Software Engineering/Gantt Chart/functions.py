def takeInputFromCSV(path):
    import pandas
    file = pandas.read_csv(path)
    table = []
    task, time, dependency = list(file['Task']), list(file['Time']), list(file['Dependency'])
    for i in range(len(file)):
        temp = [task[i].upper(), float(time[i])]
        if dependency[i] == 'None':
            temp.append(None)
        else:
            temp.append(dependency[i].upper().split(", "))
        table.append(temp)
    return table


def takeInputFromUser():
    x = "enter"
    table = []

    while x != "exit":
        temp = []
        temp.append(input("Enter The Task Name:\t").upper())
        temp.append(int(input(f"Enter The Time to Complete Task {temp[0]}:\t")))
        temp.append(input(f"Enter The Dependencies for {temp[0]}:\t"))
        if len(temp[2]) == 0:
            temp[2] = None
        else:
            temp[2] = temp[2].upper().split(", ")
        table.append(temp)
        x = input("Type 'EXIT' to Stop Giving Input (else hit ENTER):\t").lower()

    return table


def takeInput():
    if input("Want To Perform Bulk Operations:\t").upper()[0] == 'Y':
        path = input("Enter The Folder Location Where CSV Files are Stored (Exclude Quotation Marks):\t")
        processCSVFilesInFolder(path)
    elif input("Have Any CSV File to Give Input:\t").upper()[0] == 'Y':
        path = input("Enter The CSV File Path (Exclude Quotation Marks):\t")
        return takeInputFromCSV(path)
    else:
        return takeInputFromUser()


def convertToDictionary_2(table):
    dic = {}
    for t in table:
        dic[t[0]] = {
            'duration': t[1],
            'dependency': t[2]
        }
    return dic


def findHiddenDependency_3(dicTable: dict):
    class Dependency:
        def __init__(self):
            self.chain = set()

        def findChainDependencyOf(self, task, dicTable: dict):
            task_dep = dicTable[task]['dependency']
            if task_dep is None:
                return None
            for td in task_dep:
                self.chain.add(td)
                self.findChainDependencyOf(td, dicTable)
            return self.chain

    for k in dicTable.keys():
        d = Dependency()
        dicTable[k]['after'] = d.findChainDependencyOf(k, dicTable)
    return dicTable


def calculateTimeToStart_4(dicTable: dict):
    def getSumOfDependencies(dep: list, dic: dict):
        total = 0
        for d in dep:
            total += dic[d]['duration']
        return total

    for d in dicTable.keys():
        if dicTable[d]['after'] is None:
            dicTable[d]['time_to_start'] = 0
        else:
            dicTable[d]['time_to_start'] = getSumOfDependencies(dicTable[d]['after'], dicTable)
    return dicTable


def formatAsDataFrame_5(dicTable: dict):
    final = {
        'task': [],
        'duration': [],
        'time_to_start': []
    }
    for d in dicTable.keys():
        final['task'].append(d)
        final['duration'].append(dicTable[d]['duration'])
        final['time_to_start'].append(dicTable[d]['time_to_start'])

    return final


def processCSVFilesInFolder(path):
    import os
    import glob

    if not os.path.exists(path):
        print("Path Doesn't Exists. Try Again.")
        exit(0)

    csv_files = glob.glob(os.path.join(path, "*.csv"))
    for file in csv_files:
        file_name = file.split("\\")[-1]
        print(f"Processing {file_name} ... ", end="")
        table = takeInputFromCSV(file)
        df = generateDataFrames(table)
        plotAndSaveFigures(df, file_name)
        print("Done")
    print("All Tasks Are Completed ... Exiting System ...")
    exit(0)


def generateDataFrames(table):
    import pandas as pd
    return pd.DataFrame(
        formatAsDataFrame_5(
            calculateTimeToStart_4(
                findHiddenDependency_3(
                    convertToDictionary_2(table)
                )
            )
        )
    )


def plotAndSaveFigures(df, file_name):
    from matplotlib import pyplot as plt

    plt.barh(y=df['task'], width=df['duration'], left=df['time_to_start'], color='maroon')
    plt.title(f"Project Management Schedule on {file_name}", fontsize=15)
    plt.xlabel("<---- Time ---->")
    plt.ylabel("<---- Tasks ---->")
    plt.savefig(f"Graph_Outputs/{file_name.split('.csv')[-2]}.png")
