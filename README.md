## Ejercicios Apuntadores y Polimorfismo

# Para el desarrollo de estos ejercicios se debe usar la estructura de proyecto siguiente:
[Disponible aquí](cpp_template_with_styles.zip)

# Crear un repositorio llamado Pointer_Polimorf
Crear un repositorio basado en la estructura del proyecto y ahí vas a desarrollar tus ejercicios.
> Al final, tu proyecto deben tener los siguiente:
> * archivo.h
> * archivo.cpp
> * main.cpp
> * Testing_Ejercicio_no1.cpp (Repetir para cada ejercicio)
> * Salida_ejercicio_no1.cpp (Repetir para cada ejercicio)


# Ejercicios Detallados: Clase `MatrixOp` con Apuntadores y Polimorfismo

A continuación se presenta un lista de ejercicios, incluyendo para cada atributo y método qué representa, qué se espera de su implementación y cómo encaja en el conjunto. Sigue esta guía paso a paso con detenimiento.


## Estructura obligatoria del proyecto

```

matrixOpProject/
├── include/
│   └── MatrixOp.h       ← Declaraciones de clases
├── src/
│   ├── MatrixOp.cpp     ← Implementaciones
│   └── main.cpp         ← Programa de demostración
├── tests/
│   └── test\_MatrixOp.cpp← Pruebas de humo
├── .gitignore
└── README.md

````

Cada archivo debe comenzar con un bloque Doxygen-style:

```cpp
/**
 * @file NombreDelArchivo
 * @brief Breve descripción del contenido.
 * @date YYYY-MM-DD
 * @author ...
 */
````

---

## Bloque A: Apuntadores

### Ejercicio A1 – Memoria dinámica y atributos básicos (5.2)

1. **¿Qué es `rows_` y `cols_`?**

   * Enteros que almacenan número de filas y columnas.
   * Se usan para validar índices y calcular desplazamientos en el buffer.

2. **¿Qué es `double *data_`?**

   * Apuntador que referencia un arreglo contiguo de `rows_*cols_` valores.
   * Cada posición `(i,j)` de la matriz corresponde al índice lineal `k = i*cols_ + j`.

3. **Tareas a implementar:**

   * **Constructor** `MatrixOp(int rows, int cols)`

     * Reserva memoria: `data_ = new double[rows*cols]`.
     * Inicializa `rows_`, `cols_`.
   * **Destructor** `~MatrixOp()`

     * Libera memoria: `delete[] data_;`.
   * **Setter** `void set(int i, int j, double v)`

     * Calcula `k = i*cols_ + j`, asigna `data_[k] = v`.
     * Debe validar que `0 ≤ i < rows_` y `0 ≤ j < cols_`; en caso contrario lanzar `std::out_of_range`.
   * **Getter** `double get(int i, int j) const`

     * Calcula `k = i*cols_ + j`, devuelve `data_[k]`.
     * Mismas validaciones de índices.

---

### Ejercicio A2 – Suma de matrices por puntero (5.1)

1. **Método a declarar**

   ```cpp
   void add(const MatrixOp *other, MatrixOp *result) const;
   ```
2. **¿Qué se pide?**

   * `other` y `result` son punteros a instancias existentes.
   * El objeto `this` y `other` deben tener **idénticas dimensiones**.
   * Recorrer con un solo índice `k` desde `0` hasta `rows_*cols_-1`, sumando:

     ```cpp
     result->data_[k] = this->data_[k] + other->data_[k];
     ```
   * En `main.cpp`, construye `A`, `B` y `C` (resultado), invoca `A.add(&B, &C)` y muestra valores de `C`.

---

### Ejercicio A3 – Aplicar operaciones genéricas con punteros a función (5.3)

1. **Declaración en `MatrixOp.h`:**

   ```cpp
   using OpFunc = double(*)(double, double);
   void apply(const MatrixOp *A,
              const MatrixOp *B,
              MatrixOp *out,
              OpFunc op) const;
   ```
2. **Descripción detallada:**

   * `OpFunc` es un puntero a función que toma dos `double` y devuelve un `double`.
   * `apply` recorre índice `k` y hace:

     ```cpp
     out->data_[k] = op(A->data_[k], B->data_[k]);
     ```
3. **Funciones auxiliares:**

   * `double sub(double a,double b);` → `return a - b;`
   * `double mul(double a,double b);` → `return a * b;`
4. **Instrucción en `main.cpp`:**

   * Llame `apply(&A, &B, &C, sub)` y luego `apply(&A, &B, &D, mul)`.
   * Imprima matrices `C` y `D`.

---

### Ejercicio A4 – Recorrido con puntero a miembro (5.4)

1. **Declaración en `MatrixOp.h`:**

   ```cpp
   void forEachDiagonal(void (MatrixOp::*fn)(int i, int j)) const;
   void printAt(int i, int j) const;
   ```
2. **Función `printAt`:**

   * Imprime `get(i,j)` seguido de espacio.
3. **Implementación de `forEachDiagonal`:**

   * Itera `i` de `0` a `min(rows_,cols_)-1` y llama

     ```cpp
     (this->*fn)(i, i);
     ```
4. **En `main.cpp`:**

   * Cree `MatrixOp M`, asígnele valores, y ejecute

     ```cpp
     M.forEachDiagonal(&MatrixOp::printAt);
     ```
   * Debe listar la diagonal principal.

---


## Bloque B (Polimorfismo) – Instrucciones Detalladas

En este bloque pondremos en práctica tres formas de polimorfismo en C++: sobrecarga de operadores, funciones plantilla (templates) y herencia con métodos virtuales. Cada ejercicio incluye:

- **Objetivo**: Qué deseamos lograr.  
- **Declaraciones**: Qué firmas y clases debes añadir al archivo `include/MatrixOp.h`.  
- **Implementación**: Cómo debe funcionar cada método, paso a paso.  
- **Uso en `main.cpp`**: Ejemplos concretos de llamadas y salidas esperadas.

---

### Ejercicio B1 – Sobrecarga de operadores (2.1)

**Objetivo**  
Permitir usar las expresiones `C = A + B;` y `D = A - B;` para matrices, donde `A`, `B`, `C`, `D` son instancias de `MatrixOp`.

#### 1. Declaración en `include/MatrixOp.h`

Dentro de la clase `MatrixOp`, añade al `public`:

```cpp
// Suma elemento a elemento: devuelve una nueva matriz
MatrixOp operator+(const MatrixOp &other) const;

// Resta elemento a elemento: devuelve una nueva matriz
MatrixOp operator-(const MatrixOp &other) const;
````

#### 2. Requisitos de implementación en `src/MatrixOp.cpp`

1. Ambas matrices (`*this` y `other`) **deben tener las mismas dimensiones** (`rows_`, `cols_`).

   * Si no coinciden, lanza `std::invalid_argument("Dimensiones incompatibles")`.

2. Crea un objeto `MatrixOp result(rows_, cols_)`.

3. Recorre todos los elementos con índice lineal `k` de `0` a `rows_*cols_-1`:

   ```cpp
   result.data_[k] = this->data_[k] + other.data_[k];   // para suma
   result.data_[k] = this->data_[k] - other.data_[k];   // para resta
   ```

4. Devuelve `result` por valor.

#### 3. Uso en `src/main.cpp`

```cpp
MatrixOp A(2,2), B(2,2);
// … inicializa A y B con valores …
MatrixOp C = A + B;
MatrixOp D = A - B;

// Mostrar resultados
std::cout << "C[0,0] = " << C.get(0,0) << "\n";
std::cout << "D[1,1] = " << D.get(1,1) << "\n";
```

*Salida esperada (ejemplo):*

```
C[0,0] = 3.0
D[1,1] = -1.0
```

---

### Ejercicio B2 – Función plantilla genérica (2.2)

**Objetivo**
Implementar una función `maxValue<T>()` que, dada una matriz subyacente (`data_`) y su tamaño, devuelva el mayor elemento de cualquier tipo `T`.

#### 1. Declaración en `include/MatrixOp.h` (fuera de la clase)

```cpp
/**
 * @brief Devuelve el valor máximo en un arreglo contiguo de longitud n.
 * @tparam T Tipo de dato (double, int, etc.)
 * @param arr Puntero al primer elemento del arreglo
 * @param n   Número de elementos
 * @return    El máximo entre arr[0] … arr[n-1]
 */
template<typename T>
T maxValue(const T *arr, int n);
```

#### 2. Definición en `include/MatrixOp.hpp` (o al final de `MatrixOp.h`)


#### 3. Uso en `src/main.cpp`

```cpp
MatrixOp M(3,3);
// … inicializar M con valores diversos …
double maxElem = maxValue<double>(M.data_, M.rows_ * M.cols_);
std::cout << "Máximo elemento de M: " << maxElem << "\n";
```

> **Nota:** Para acceder a `data_`, puedes:
>
> * Proporcionar un método `const double* data() const { return data_; }` y `int size() const { return rows_*cols_; }`.

*Salida esperada (ejemplo):*

```
Máximo elemento de M: 42.5
```

---

### Ejercicio B3 – Herencia y métodos virtuales (3.1)

**Objetivo**
Crear una interfaz `IMatrix` con método virtual puro `determinant()`, e implementar ese método en `MatrixOp`.

#### 1. Declaración en `include/MatrixOp.h`

Antes de la definición de `MatrixOp`, añade:

```cpp
/**
 * @brief Interfaz abstracta para operaciones avanzadas de matriz.
 */
class IMatrix {
public:
    virtual ~IMatrix() = default;
    virtual double determinant() const = 0;
};
```

Y modifica la clase:

```cpp
class MatrixOp : public IMatrix {
    // …
    double determinant() const override;
};
```

#### 2. Implementación en `src/MatrixOp.cpp`

1. En matrices de **2×2**, usa fórmula directa:

   ```cpp
   // |a b| 
   // |c d| = a*d - b*c
   return get(0,0)*get(1,1) - get(0,1)*get(1,0);
   ```
2. En matrices de **3×3**, aplica la regla de Sarrus.
3. Para otros tamaños, lanza `std::logic_error("Implementar para 2×2 o 3×3")`.

#### 3. Uso en `src/main.cpp`

```cpp
IMatrix *mat = new MatrixOp(2,2);
// … asignar valores a mat vía dynamic_cast o método propio …
std::cout << "Determinante: " << mat->determinant() << "\n";
delete mat;
```

*Salida esperada (ejemplo):*

```
Determinante: -7.0
```

---

**Ejercicio Final: Diagrama de clases**
Dado el código resultante de la clase MatrixOp, generar un diagrama de clases en Mermaid o UML que muestre:

MatrixOpBase (abstracta) ← MatrixOp

Métodos virtuales y sobrescritos

Sobrecarga de operadores en MatrixOp

Relaciones de uso con punteros a función y a miembro

Publicar el diagrama en el readme.md de tu repositorio de solución Pointer_Polimorf.

> **Recomendación final:**
> * Ejecuta un test de humo tras cada ejercicio para asegurar que la funcionalidad es la esperada.
> * Recuerdar usar el proyecto base siguiente:
[Disponible aquí](cpp_template_with_styles.zip)
