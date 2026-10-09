# CWE-416: Use After Free

Aplicación de consola en C que ejemplifica la vulnerabilidad **CWE-416 (Use After Free)**: el uso de un puntero a memoria que ya fue liberada con `free()`. Práctica guiada de la experiencia educativa de Programación Segura.

## Descripción

El programa gestiona una estructura `auth` reservada en el *heap* con un nombre y una bandera entera `auth`. La opción `login` solo concede acceso cuando `auth->auth` vale 1, pero ese valor nunca se asigna en el código, por lo que el acceso parece imposible.

La falla está en que al liberar la estructura con `reset` (`free(auth)`), el puntero no se anula y queda como *dangling pointer*. Al reutilizar ese mismo bloque de memoria con `service` (que reserva con `strdup` → `malloc`), los bytes escritos terminan invadiendo el campo `auth->auth`, dándole un valor distinto de cero y permitiendo el acceso.

## Estructura

```
cwe-416/
├── programa.c   # Código fuente
└── README.md
```

## Compilación

En Linux, con los flags que desactivan protecciones para poder depurar la práctica:

```bash
gcc programa.c -o programa.out -fno-stack-protector -z execstack -ggdb
```

## Uso

```bash
./programa.out
```

Opciones del menú:

| Opción          | Acción                                                          |
|-----------------|-----------------------------------------------------------------|
| `auth <nombre>` | Reserva la estructura y copia el nombre de usuario.             |
| `reset`         | Libera la memoria de `auth` con `free()`.                       |
| `service <str>` | Reserva memoria con `strdup()` para un servicio de red.         |
| `login`         | Concede acceso si `auth->auth` tiene valor.                     |

## Explotación (payload)

Secuencia de entradas que imprime `Bienvenido. Lo lograste!`:

```
auth admin
login
reset
service AAA
service BBB
service CCC
login
```

Al escribir `service CCC`, la tercera cadena ocupa el espacio liberado de `auth` y sus bytes caen sobre el campo entero `auth->auth`, que pasa a ser distinto de cero. El siguiente `login` concede el acceso.

## Mitigación

Anular el puntero tras liberarlo y validar antes de usarlo:

```c
free(auth);
auth = NULL;
```

> Práctica con fines educativos para comprender y mitigar la vulnerabilidad CWE-416.