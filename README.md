# Matriz de Adjacências

## Notas do professor

Aqui segue um arquivo [grafomatadjexercicio.h](https://github.com/eduardolfalcao/edii/blob/master/src/grafos/grafomatadjexercicio.h)
com a assinatura das funções que eu gostaria que vocês implementassem.

## Dependências

 - Gtest - 1.10.0-3 : Google Test -
   C++ testing utility based on the xUnit framework (like JUnit)

## instalar as dependências

Ubuntu ou outros derivados do Debian:

```shell
sudo apt install libgtest-dev 
```

Arch linux ou Derivados:

```shell
sudo pacman -S gtest
```
Caso você meu companheiro, companheira não tenha instalado
o kit básico de desenvolvimento,
também instale o **cmake**, **git**.

Ubuntu ou outros derivados do Debian:
```shell
sudo apt install build-essential git cmake 
```

Arch linux ou Derivados:

```shell
sudo pacman -S git base-devel cmake
```

### Como testar no linux

```shell
mkdir build
cd build
cmake ..
make 
./runUnitTests
```

### Windows
Faça dual boot.
