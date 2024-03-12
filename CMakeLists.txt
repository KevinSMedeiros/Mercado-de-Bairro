cmake_minimum_required(VERSION 3.27)
project(mercadogit C)

set(CMAKE_C_STANDARD 11)

add_executable(mercadogit main.c
        cliente.c
        itensCompra.c
        produtos.c
        tempo.c
        vendas.c)
