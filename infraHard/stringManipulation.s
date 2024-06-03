#  5a questão
.data
entrada: .space 256
resp: .space 1024

.text

la $s0, entrada 		# guarda o inicio da string em s0
add $t0, $s0, $zero 	# copia o inicio da string em t0 pra poder manipular

# Lê uma string da entrada
li $v0, 8               # Seta o serviço de ler uma string (8)
add $a0, $s0, $zero     # passa o endereço como argumento
li $a1, 256             # passa o tamanho maximo como argumento
syscall

la $s1, resp 		    # guarda o inicio do array em s1
add $t1, $s1, $zero 	# copia o inicio do array em t1 pra poder manipular

li $t8, 'A'
li $t9, 'Z'

#itera pela string
forBegin: 
    lb $t2, ($t0)           # carrega o caractere atual da string em t2
    beq $t2, $zero, forEnd  # testa se é o fim da string se for, encerra o for
    #######
    
    sub $t3, $t2, $t8      # t3 = t2 - A
    bltz $t3, forContinue  # se t2 for menor que A (t2-'A'<0) então ignora o caractere

    sub $t3, $t2, $t9      # t3 = t2 - z
    bgtz $t3, forContinue  # se t2 for maior que Z (t2-'Z'>0) então ignora o caractere

        #se o caractere esta no intervalo [A, Z]
        sb $t2, ($t1)  # Adiciona o caractere no final do array
        addi $t1, $t1, 1  # incrementa o final do array

    #######
    forContinue:
    addi $t0, $t0, 1        # incrementa o iterador
    j forBegin
forEnd:

sb $zero, ($t1) #sinaliza o fim da string

# Imprime a string final
li $v0, 4            # Seta o serviço de printar string (4)
add $a0, $s1, $zero  # Passa a string como argumento
syscall