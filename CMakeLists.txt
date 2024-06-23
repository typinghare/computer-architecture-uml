cmake_minimum_required(VERSION 3.28)
project(computer_architecture_uml C)

set(CMAKE_C_STANDARD 11)

# Homework 3
add_executable(hw2
        hw2/framework.h
        hw2/framework.c
        hw2/main.c
)

# Homework 3
add_executable(hw3-ifib hw3/ifib.c)
add_executable(hw3-rfib-unoptimized hw3/rfib_unoptimized.c)
add_executable(hw3-rfib hw3/rfib.c)

# Homework 4
add_executable(hw4-masm hw4/masm.c)

# Homework 6
add_executable(hw6-linker hw6/linker.c)