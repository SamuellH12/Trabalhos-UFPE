import os
import random

dijkstra_nlog = "dijkstra_par.cpp"
dijkstra_lento = "dijkstra_quadratico.cpp"
bellmanford = "bellmanford"

os.system("g++ " + dijkstra_nlog + " -o a" )
os.system("g++ " + dijkstra_lento+ " -o b" )
# os.system("g++ " + bellmanford   + " -o c" )

N = 727

lista = []

for _ in range(10):
    temp = [0, 0, 0]
    os.system("echo > in.txt 3 " + str(random.randint(0,N-1)) + " " + str(random.randint(0,N-1)))
    
    os.system("a 1 < in.txt > out.txt")
    with open("out.txt", 'r') as f:
        temp[0] = f.read()
        # print(temp[0] + "<----")  
            
    
    os.system("b 1 < in.txt > out.txt")
    with open("out.txt", 'r') as f:
        temp[1] = f.read()


    # os.system("./c < in.txt")
    # with open("out.txt", 'r') as f:
    #     temp[2] = f.read()

    lista.append(temp) 

sum_a = 0
sum_b = 0
sum_c = 0

for s, t, u in lista:
    print( "Dijkstra n log:      " + s[:-2])
    print( "Dijkstra quadratico: " + t[:-2])
    print("-------------------------------")

    sum_a += float(s[:-2])
    sum_b += float(t[:-2])

print("\n\nMedias\n")
print( "Dijkstra n log:      " + str((sum_a/len(lista))))
print( "Dijkstra quadratico: " + str((sum_b/len(lista))))