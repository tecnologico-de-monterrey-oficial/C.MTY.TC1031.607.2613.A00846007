Ian Armando Borde Escobar - A00846007

1. ¿Qué ventaja concreta notaste al usar templates en tu clase Lista, comparado con haberla hecho solo para un tipo de dato (por ejemplo, solo enteros)? Da un ejemplo de tu propio código.
    Con la clase lista pude usar la misma clase para guardar enteros y strings sin tener que escribir el codigo dos veces, por ejemplo en mi .cpp hice:
        List<int> list;
        list.insert(5);
        list.insert(10);
        list.insert(15);

        List<string> things;
        things.insert("Laptop");
        things.insert("bottle");
    Ambas usan el mismo List.h, el mismo insert, print, getMax, entre otros. Si no hubiera usado los templates, hubiera tenido que crear una clase ListaInt y luego otra ListaString, haciendo que haga el doble de trabajo de manera innecesaria 

2. ¿Qué parte de la actividad —ya sea el uso de templates o el reto de insertAt/removeAt— te costó más trabajo entender o depurar? ¿Qué hiciste para resolverlo?
    Lo que mas me costo fue entender el concepto de templates en si, ya que no lo habia visto, tenia lo que vimos en clase pero luego cuando me toco ver lo que seguia me perdi, para resolver este problema lo que hice fue buscar en internet, preguntar a Copilot para ver que era lo que me faltaba, y luego ya despues de estar buscando pude terminar la actividad

3. Si tuvieras que explicarle a un compañero qué es un template en C++ usando tus propias palabras, sin tecnicismos, ¿qué le dirías?
    Que es una manera de reciclar muchas funciones que normalmente tendrias que estar colocando individualmente para cada cosa, por ejemplo si tuvieras dos filas, una fila de personas de mayoria de edad y otro de menores tendrias que hacer funciones para cada uno pero con los templates te quitas esa compliacion de encima y haces el proceso mas facil reciclando