# 8a questão
.data
array: .space 1024
msg1: .asciiz "Digite o tamanho do array\n"
msg2: .asciiz "Digite o array\n"
msg3: .asciiz "Digite o numero buscado\n"


.text
j main   #Comeca o codigo na main

# a0 = Array*, L = a1, R = a2, a3 = N
# v0 = bool encontrou, v1 = idx
BuscaBinaria:
    add $t0, $a1, $a2   # t0 = L+R  #Calcula o meio
    sra $t0, $t0, 1     # t0 = t0/2

    sll $t4, $t0, 2     # mutiplica t0 por 4 pra pegar o endereco
    add $t1, $a0, $t4   # calcula o endereco do array
    lw $t1, ($t1)       # carrega o valor em t1

    bgt $t1, $a3, Maior
    blt $t1, $a3, Menor

    # Encontrou -> t1 == a3 
    li $v0, 1           # Marca v0 como 1 pq encontrou
    add $v1, $t0, $zero # Coloca M em v1
    jr $ra               # retorna
    
    Maior:
        add  $t2, $a1, $zero # Novo L = L
        addi $t3, $a2, -1    # Novo R = M - 1
        j BuscaProximo
    Menor:
        addi $t2, $a1, +1    # Novo L = M + 1
        add  $t3, $a2, $zero # Novo R = R

    BuscaProximo:
        ble $t2, $t3, chamaRec  # Se Novo L <= Novo R chama rec
        li $v0, 0               # Se não, então a busca acabou e não encontramos o N
        jr $ra

        chamaRec:
            addi $sp, $sp, -4   # Reserva 1 posição na stack
            sw $ra, 0($sp)      # Salva o ra na stack

            add $a1, $t2, $zero # Passa o novo L como parâmetro
            add $a2, $t3, $zero # Passa o novo R como parâmetro

            jal BuscaBinaria    # Chama a buscaBinária pro novo intervalo

    lw $ra, 0($sp)     # Restaura o valor de ra
    addi $sp, $sp, 4   # Remove o topo da stack

jr $ra  # Retorna pra quem chamou a função


main:

# Imprime a msg1 | Digite o tamanho do array
li $v0, 4       # Seta o serviço de printar string (4)
la $a0, msg1    # Passa a string como argumento
syscall

li $v0, 5           # Seta o serviço de ler int (5)
syscall
add $s0, $v0, $zero # Salva o int em s0 (Tamanho do array)



# Imprime a msg2 | Digite o array
li $v0, 4       # Seta o serviço de printar string (4)
la $a0, msg2    # Passa a string como argumento
syscall


la  $s1, array      # Salva o begin do array em s1
add $t1, $s1, $zero # Salva o begin do array em t1

li $t0, 0   # Seta t0 como contador = 0
forBegin:   # For pra ler o array da entrada
    beq $t0, $s0, forEnd

    li $v0, 5           # Seta o serviço de ler int (5)
    syscall
    sw $v0, ($t1)         # Salva o int em t1 (ponteiro pro fim do array)

    addi $t1, $t1, 4    # Incrementa t1 pra receber o proximo numero
    addi $t0, $t0, 1    # Incrementa o contador (t0)
    j forBegin
forEnd:


# Imprime a msg3 | Digite o numero buscado
li $v0, 4       # Seta o serviço de printar string (4)
la $a0, msg3    # Passa a string como argumento
syscall


li $v0, 5           # Seta o serviço de ler int (5)
syscall
add $s3, $v0, $zero # Salva o item buscado em s3


# Chama a busca binária
add  $a0, $s1, $zero  # Passa o ponteiro do array como argumento
li   $a1, 0           # Passa L como argumento
addi $a2, $s0, -1     # Passa R como argumento
add  $a3, $s3, $zero  # Passa N como argumento

jal BuscaBinaria  # Chama a Busca Binária

add $s4, $v0, $zero #salva em s4 se encontrou ou não

li $v0, 1           # Seta o serviço de printar int (1)
add $a0, $s4, $zero # Passa s4 (se encontrou ou não) como argumento
syscall

beqz $s4, exit # se não encontrou, encerra o programa

li $v0, 11           # Seta o serviço de printar char (11)
li $a0, '\n'        # Passa \n como argumento
# sll $a0, $a0, 24
syscall

li $v0, 1           # Seta o serviço de printar int (1)
add $a0, $v1, $zero # Passa v1 (indice) como argumento
syscall


exit:
