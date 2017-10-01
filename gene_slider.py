# gene_slider.py


def match_points(a, b):
    if (a == b):
        return 1
    return 0     

class Edge:
    def __init__(self, v, weigth):
        self.v = v
        self.weigth = weigth

class Vertex:
    def __init__(self, i, j):
        self.i = i
        self.j = j
        self.edges = []

    def add_edge(e):
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
                j += 1
            i += 1     

        while i < len(A):
            j = 0
            while j < len(B):
                if (i < len(A) - 1):
                    self.vertces[(i, j)].add_edge(Edge(self.vertices[(i + 1, j)], match_points(A[i], B[j])))
                    if (j < len(B) - 1):
                        self.vertces[(i, j)].add_edge(Edge(self.vertices[(i + 1, j + 1)], match_points(A[i], B[j])))




a = 'CCTGCTGCAGGATGTGCCG'
b = 'GATGTGCAGCCTGTAGG' 

print(Graph(a, b))



