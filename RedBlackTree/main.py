def levenshtein_distance(s1, s2):
    m, n = len(s1), len(s2)
    
    # Inicializar una matriz (m+1)x(n+1) con ceros
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    # Llenar la primera fila y la primera columna con valores incrementales
    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j
    
    # Calcular la distancia de Levenshtein
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i - 1] != s2[j - 1]:
                dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i][j - 1] + 1, dp[i - 1][j] + 1)
            else:
                dp[i][j] = dp[i - 1][j - 1]
    
    print(dp)
    return dp[m][n]

# Ejemplo de uso
s1 = "hello"
s2 = "kelm"
distance = levenshtein_distance(s1, s2)
print(f"La distancia de Levenshtein entre '{s1}' y '{s2}' es {distance}")
