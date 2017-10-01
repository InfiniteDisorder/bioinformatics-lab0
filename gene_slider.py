# gene_slider.py

POINTS_FOR_MATCH = 5

def count_match_points(a, b):
    if a == b:
        return POINTS_FOR_MATCH
    return 0    

def build_match_matrix(A, B):
    matrix = []
    a_len = len(A)
    b_len = len(B)
    i = 0
    while i < a_len:
        matrix.append([])
        j = 0
        while j < b_len:
            matrix[i].append((A[i], B[j],count_match_points(A[i], B[j])))
            j += 1
        i += 1    
    return matrix


a = 'CCTGCTGCAGGATGTGCCG'
b = 'GATGTGCAGCCTGTAGG' 

print(build_match_matrix(a,b)) 


