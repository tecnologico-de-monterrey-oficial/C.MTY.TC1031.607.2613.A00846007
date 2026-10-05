Act2.1-LinkedList
Ian Armando Borde Escobar - A00846007

Prompts:

ayudame a tener la estructura completa de archivos para esta tarea, no lo hagas todo nada mas explicame una estructura sugerida y que va en cada archivo
ya tengo las funciones para agregar al principio y al final, me ayudas a revisar el orden en que cambio los apuntadores y dónde debo incrementar size?
mi función insert agrega después del índice, pero la tabla de la actividad dice que inserta en el índice, me explicas la diferencia y qué índices debo aceptar en cada caso?
estoy trabajando en operator= y sé que necesito copiar los nodos, no solo head, me ayudas a entender como manejo la memoria que ya tenía la lista y la asignación de una lista a sí misma?
ya estoy terminando la tarea, puedes checar que haya cumplido con todo antes de hacer las pruebas?
puedes hacer en mi vs code las pruebas de cada una de las opciones del menu y puedes hacer un pdf llamado tests.pdf

¿Qué parte del código te propuso la IA que aceptaste tal cual y por qué era correcta?
Una parte que acepte tal cual fue la sobrecarga del operador [], porque al regresar una referencia puedo leer un dato con lista[0] y también cambiarlo con lista[0] = 25, ademas antes de acceder al nodo revisa que el índice exista y si no existe lanza std::out_of_range, entonces no intenta acceder a una posición inválida

¿Qué parte modificaste y cómo verificaste que tu cambio era mejor?
La parte que modifique fue la actualización de size al agregar un elemento al principio, porque antes agregaba el nodo pero no aumentaba el tamaño de la lista. En la versión actual push_front llama a addFirst, que ya hace ese incremento, en la prueba se agregaron dos elementos al principio de una lista vacía y se verificó que el tamaño fuera 2 y que se pudiera consultar el índice 1 asi es como se comprobo que el tamaño coincide con los elementos que tiene la lista

¿Dónde se equivocó la IA (si ocurrió) y cómo lo detectaste?
No detecte errores entonces la IA no se equivoco en las dudas que tenia

¿Qué harías diferente si no tuvieras Copilot/ChatGPT?
Si no tuviera IA para este trabajo, tendria que buscar informacion en otros lugares, como en foros en internet, libros academicos, experiencia de mis profesores, experiencia de mis familiares en la misma area que yo estudi y tambien preguntaria a mis compañeros a ver si alguien mas entendio