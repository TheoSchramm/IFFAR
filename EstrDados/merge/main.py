import random

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    metade = len(arr) // 2
    
    # Divide o vetor fazendo uso dos operadores de "slice"
    esquerda = arr[:metade]
    direita = arr[metade:]
    
    # Recursivamente divide os vetores laterais
    esquerda = merge_sort(esquerda)
    direita = merge_sort(direita)
    
    # Junta novamente as duas metades laterais
    return merge(esquerda, direita)


def merge(esquerda, direita):
    resultado = []
    # É criado duas variaveis que irão percorrer os vetor laterais
    i = j = 0

    # Compara os elementos da esquerda e da direta e anexa o menor elemento ao resultado
    while i < len(esquerda) and j < len(direita):
        if esquerda[i] <= direita[j]:
            resultado.append(esquerda[i])
            i += 1
        else:
            resultado.append(direita[j])
            j += 1
    
    # Anexa os elementos restantes
    resultado.extend(esquerda[i:])
    resultado.extend(direita[j:])
    print(f"Esquerda: {esquerda} | Direita: {direita} \nDeu merge -> {resultado} \n")
    return resultado

def main():
    vetor = random.sample(population=range(1,11), k=10)
    print(f"Vetor inicial: {vetor} \n")

    new_vetor = merge_sort(vetor)

if __name__ == "__main__":
    main()
