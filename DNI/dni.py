import msvcrt


def VerLetra(numero):
    letras=['T','R','W','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'] 
    return letras[numero%23]



def comprobarLetra():
    dni=input("\nIntroduce el DNI (con letra): ")

    letra=dni[8] # Guardamos la letra a una variable separada
    dni = dni[:-1] # Eliminamos el último caracter de la variable dni
    nif=int(dni) # Convertimos los números del string dni a tipo int
    
    if VerLetra(nif) != letra: # Comprobamos que nos devuelva la letra correcta
        print("La letra",letra, "del DNI no corresponde con el NIF\n\n",nif)
    else:
        print("El DNI",dni,letra,"es correcto\n\n")

    
def ObtenerLetra():
    nif=int(input("\nIntroduce el NIF: "))
    letra=VerLetra(nif)
    print("La letra correspondiente al NIF es",letra,"es decir, el DNI es",nif,letra)



print("Bienvenido al programa")
print("Este programa sirve para comprobar los DNI y/o obtener la letra correspondiente a un NIF\n")

on = True
while on == True:
    print("1. Comprobar un DNI\n 2. Obtener la letra del DNI\n 3. Cerrar el programa\n")
    option = int(input("Elija una opcion: ")) # Permitimos al usuario elegir que quiere hacer
    if option==1: # Comprobar letra
        comprobarLetra()
    elif option == 2: # Obtener letra
        ObtenerLetra()
    elif option == 3: # Cerrar programa
        print("El programa se cerrará\n\n")
        on = False
    else:
        print("\n\n\nError: Número no válido\n\n")

print("Presione una tecla para continuar...")
msvcrt.getch()