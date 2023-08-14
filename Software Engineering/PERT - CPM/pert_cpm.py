from collections import defaultdict


class Graph:
    def __init__(self):
        self.adjacency = defaultdict(list)
        self.edges = defaultdict(dict)
        self.vertices = []

    def add_edge(self, start, end, to, tm, tp, te):
        self.adjacency[start].append(end)
        self.edges[(start, end)]['to'] = to
        self.edges[(start, end)]['tm'] = tm
        self.edges[(start, end)]['tp'] = tp
        self.edges[(start, end)]['te'] = te

        if start not in self.vertices:
            self.vertices.append(start)
        if end not in self.vertices:
            self.vertices.append(end)

    def getAllPathsUtil(self, src, dst, visited: dict, store: list, path: list):
        visited[src] = True
        path.append(src)

        if src == dst:
            store.append(tuple(path))
        else:
            for i in self.adjacency[src]:
                if not visited[i]:
                    self.getAllPathsUtil(i, dst, visited, store, path)

        path.pop()
        visited[src] = False

    def getAllPathsByEdge(self, paths: list[tuple]):
        store = []
        for m in paths:
            temp = []
            for i in range(len(m) - 1):
                temp.append((m[i], m[i+1]))
            store.append(temp)
        return store

    def getAllPaths(self, src, dst):
        visited = {}
        for v in self.vertices:
            visited[v] = False

        store = []
        self.getAllPathsUtil(src, dst, visited, store, [])
        return store

    def calculatePathCost(self, path: list[tuple]):
        total = 0
        for p in path:
            total += self.edges[p]['te']
        return total

    def draw(self):
        import networkx as nx
        from matplotlib import pyplot as plt
        g = nx.DiGraph()
        g.add_edges_from(list(self.edges.keys()))
        nx.draw_circular(g, with_labels=True, node_color='CYAN', node_size=1200)
        plt.show()


g = Graph()
x = "ENTER"
while x != "EXIT":
    task = tuple(input("Enter The Activity (Use Comma Space like (X, Y)):\t").split(", "))
    to = float(input(f"Enter The T(O) value of {task}:\t"))
    tm = float(input(f"Enter The T(M) value of {task}:\t"))
    tp = float(input(f"Enter The T(P) value of {task}:\t"))
    te = (to + (4 * tm) + tp) / 6
    g.add_edge(task[0], task[1], to, tm, tp, te)
    x = input("Type 'EXIT' to Stop Giving Input (Else Hit Enter):\t").upper()

store = g.getAllPaths('1', '5')
e_stores = g.getAllPathsByEdge(store)
cost = []
for e in e_stores:
    cost.append(round(g.calculatePathCost(e), 4))


pos = cost.index(max(cost))
print(f"Critical Path is:\t{store[pos]} \nIt's Cost is:\t{cost[pos]}\nDo You Want to See PERT Graph:\t", end="")
if input().upper()[0] == 'Y':
    g.draw()
print("Great !!!\nExiting System ...")

