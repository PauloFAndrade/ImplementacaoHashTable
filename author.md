# Identificação Pessoal

Preencha os dados abaixo para identificar a autoria do trabalho.

- Nome: *Paulo Vitor Fernandes Andrade*
- Email: *paulovitorfandrade2002@gmail.com*
- Turma: *DIM0119*

# Descrição do Projeto

Nesse projeto criei uma classe própria simulando o comportamento de uma Hash table utilizando o encadeamento externo como método de tratamento de colisões. Fiz a implementação de vários métodos, seja ele de acesso, modificação e etc.

# Como Compilar e Executar

## Compilar
    ##### Usando cmake
    ```
    cd source
	cmake -S . -B build
	cmake --build build
    ```

## Executar Os Testes
    Utilize os seguintes comandos para executar a bancada de testes. obs: esteja na pasta source.
    ```
    cd build
    ./run_tests
    ```

## Executar O Driver
    Utilize os seguintes comandos para executar o driver. obs: esteja na pasta source.
    ```
    cd build
    ./driver_hash
    ```

# Indique quais métodos das classes abaixo foram implementados

## Implementação do Hash Table

**Special members (14 credits)**
- [X] Regular constructor (2 credits)
- [X] Destructor (2 credits)
- [x] Copy constructor (3 credits)
- [X] Constructor from initialize list (3 credits)
- [X] Assignment operator `operator=(list)` (2 credits)
- [X] Assignment operator `operator=(initializer list)` (2 credits)

**Other methods (101 credits)**
- [X] `insert()` (12 credits)
- [X] `erase()` (12 credits)
- [X] `retrieve()` (12 credits)
- [X] `clear()` (8 credits)
- [X] `empty()` (3 credits);
- [X] `size()` (3 credits);
- [X] `operator<<()` (8 credits)
- [X] `at()` (11 credits)
- [X] `operator[]()` (11 credits)
- [X] `count()` (6 credits)
- [X] `rehash()` (15 credits);

--------
&copy; DIMAp/UFRN 2021.
