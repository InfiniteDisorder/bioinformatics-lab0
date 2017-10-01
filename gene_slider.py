# gene_slider.py


def match_points(a, b):
    if (a == b):
        return 0
    return 1

class Edge:
    def __init__(self, v, weigth):
        self.v = v
        self.weigth = weigth

class Vertex:
    def __init__(self, i, j):
        self.i = i
        self.j = j
        self.edges = []
        self.path_length = 0
        self.path =  []
        self.visited = False

    def add_edge(self, e):
        self.edges.append(e)
        return self    

class Graph:
    def __init__(self, A, B):
        self.A = A
        self.B = B
        self.vertices = {}
        i = 0
        while i < len(A):
            j = 0
            while j < len(B):
                self.vertices[(i, j)] = Vertex(i, j) 
                self.vertices[(i, j)].path_length = float("inf") 
                j += 1
            i += 1     

        i = 0
        while i < len(A):
            j = 0
            while j < len(B):
                if (i < len(A) - 1):
                    self.vertices[(i, j)].add_edge(Edge(self.vertices[(i + 1, j)], match_points(A[i], B[j])))
                    if (j < len(B) - 1):
                        self.vertices[(i, j)].add_edge(Edge(self.vertices[(i + 1, j + 1)], match_points(A[i], B[j])))       
                j += 1
            i += 1    

    def shortest_path(self):
        not_visited = [x for x in self.vertices.values() if x.visited == False] 
        a = self.vertices[(0,0)]
        a.path_length = 0.0

        while len(not_visited) != 0:
            v = min(not_visited,key =  lambda x: x.path_length)
            v.visited = True
            not_visited = [x for x in self.vertices.values() if x.visited == False] 
            for e in v.edges:
                u = e.v
                if not u.visited:
                    if u.path_length > v.path_length + e.weigth:
                        u.path_length = v.path_length + e.weigth
                        print(v.path, v.i, v.j)
                        u.path = v.path[:]
                        u.path.append(u)

    def print_paths(self):
        v = self.vertices[len(self.A) - 1, len(self.B) - 1]
        print(v.path_length)
        for i in v.path:
            print(v.i, v.j, self.A[v.i], self.B[v.j])


a = 'CCTGCTGCAGGATGTGCCG'
b = 'GATGTGCAGCCTGTAGG' 

G = Graph(a, b)
G.shortest_path()
G.print_paths()



