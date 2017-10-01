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
                self.vertices[(i, j)].path = [self.vertices[(0, 0)]]
                if (i < len(A) - 1):
                    self.vertices[(i, j)].add_edge(Edge(self.vertices[(i + 1, j)], match_points(A[i + 1], B[j]) + 1))
                    if (j < len(B) - 1):
                        self.vertices[(i, j)].add_edge(Edge(self.vertices[(i + 1, j + 1)], match_points(A[i + 1], B[j + 1])))       
                j += 1
            i += 1    

    def dijkstra_path(self):
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
                        u.path = v.path[:]
                        u.path.append(u)

    def shortest_path(self):
        path = [] 
        gapped_path = []
        ends = [x for x in self.vertices.values() if x.i == len(self.A) - 1]
        v = min(ends,key = lambda x: x.path_length)
        for i in v.path:
            path.append((i.i, i.j,self.A[i.i], self.B[i.j]))
        last_index = -1   
        path.reverse()
        for j in path:
            if j[1] == last_index:
                gapped_path.append((j[0], j[1], self.A[j[0]], '-'))
            else:
                gapped_path.append(j) 
            last_index = j[1]    
        gapped_path.reverse()     
        return gapped_path       

def print_nucleotide_seq(path):
    matches = 0
    for i in path:
        print(i[2], i[3])
        if i[2] == i[3]:
            matches += 1

    print('Total macthes: ', matches, 'from: ', len(path))        




a = 'CCTGCTGCAGGATGTGCCG'
b = 'GATGTGCAGCCTGTAGG' 

G = Graph(a, b)
G.dijkstra_path()
path = G.shortest_path()
print_nucleotide_seq(path)





