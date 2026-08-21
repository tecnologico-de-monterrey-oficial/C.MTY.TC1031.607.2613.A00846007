Ian Borde - A00846007

1. ¿En qué casos notaste que la versión recursiva fue más lenta o usó más memoria que la iterativa? ¿A qué se debió?
    Siento que el caso mas claro fue en la funcion de fibonacciRecursive, ya que cada llamada genera otras dos llamadas mas y luego esas generan cuatro y asi sigue, es como un triangulo que va hacia abajo que va creciendo expotencialmente (pow2), mientras que la version iterativa de la funcion hace exactamente n pasos. Para un n pequeño no se nota pero si subo el n a un numero mas grande, mi funcion recursiva tardaria mas porque recalcula los mismos subproblemas una y otra vez

2. Para la suma 1..n, sumFormula resuelve en un solo paso lo que a sumIterative y sumRecursive les toma n pasos. ¿Qué te dice esto sobre buscar una fórmula antes de escribir código?
    Que antes de programar hay que pensar que vamos a hacer primero y que es mejor buscar la logica detras antes de aplicarla, para que evitemos hacer mas trabajo de lo necesario haciendo prueba y error y aplicando la solucion

3. Si bacteriasRecursive tuviera que calcular n = 100,000 días, ¿qué problema esperarías encontrar y cómo lo resolverías?
    El problema que esperaba encontrar era un stack overflow, pero el programa si termino, porque 100,000 n si caben en el stack, pero el resultado que dio (1,254,653,458) no es correcto, lo que paso fue que hubo un overflow del int, que llega aproximadamente a 2,147,483,647, como las bacterias crecen aprox 2.44x al dia y ese limite se supera maximo a los 20 dias y despues se empieza a calcular mal, para resolver esto lo que pienso que se podria hacer es bajar el numero de n dias porque el ejercicio pide que sea truncado a enteros y por eso ocupamos el int, pero luego llegamos a este limite que hace que el programa no funcione

    https://learn.microsoft.com/es-es/cpp/cpp/integer-limits?view=msvc-170 -- Fuente donde saque el dato de 2,147,483,647 para el problema 3: INT_MAX Valor máximo de una variable de tipo int. *2147483647*