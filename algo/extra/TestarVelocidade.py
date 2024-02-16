import os
import random
import math

dijkstra_nlog = "dijkstra_par.cpp"
dijkstra_lento = "dijkstra_quadratico.cpp"
bellmanford = "bellman_ford.cpp"

os.system("g++ " + dijkstra_nlog + " -o a" )
os.system("g++ " + dijkstra_lento+ " -o b" )
os.system("g++ " + bellmanford   + " -o c" )

N = 727

lista = []

for _ in range(1000):
    temp = [0, 0, 0]
    os.system("echo > in.txt 3 " + str(random.randint(0,N-1)) + " " + str(random.randint(0,N-1)))
    
    os.system("a 1 < in.txt > out.txt")
    with open("out.txt", 'r') as f:
        temp[0] = f.read()
        # print(temp[0] + "<----")  
            
    
    os.system("b 1 < in.txt > out.txt")
    with open("out.txt", 'r') as f:
        temp[1] = f.read()


    os.system("c 1 < in.txt > out.txt")
    with open("out.txt", 'r') as f:
        temp[2] = f.read()

    lista.append(temp) 

sum_a = 0
sum_b = 0
sum_c = 0

for s, t, u in lista:
    sum_a += float(s[:-2])
    sum_b += float(t[:-2])
    sum_c += float(u[:-2])
    print( "Dijkstra n log:      " + s[:-2])
    print( "Dijkstra quadratico: " + t[:-2])
    print( "Bellman-Ford:        " + u[:-2])
    print("-------------------------------")

ln = len(lista)

media_a = (sum_a/ln)
media_b = (sum_b/ln)
media_c = (sum_c/ln)

print("\n\nMedias\n")
print( "Dijkstra n log:      " + str(media_a))
print( "Dijkstra quadratico: " + str(media_b))
print( "Bellman-Ford:        " + str(media_c))

sum_a = 0
sum_b = 0
sum_c = 0

for s, t, u in lista:
    sum_a += (float(s[:-2]) - media_a ) * (float(s[:-2]) - media_a )
    sum_b += (float(t[:-2]) - media_b ) * (float(t[:-2]) - media_b )
    sum_c += (float(u[:-2]) - media_c ) * (float(u[:-2]) - media_c )

dp_a = math.sqrt(sum_a / ln)
dp_b = math.sqrt(sum_b / ln)
dp_c = math.sqrt(sum_c / ln)

print("\n\nDesvio Padrao\n")
print( "Dijkstra n log:      " + str(dp_a))
print( "Dijkstra quadratico: " + str(dp_b))
print( "Bellman-Ford:        " + str(dp_c))