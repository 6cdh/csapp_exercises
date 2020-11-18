# CSAPP partial exercises

Only exercises of chapter 2 (Representing and Manipulating Information), chapter 5 (Optimizing Program Performance), and chapter 6 (The Memory Hierarchy) are available.

All code are tested on my laptop:

```shell
Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   39 bits physical, 48 bits virtual
CPU(s):                          8
Thread(s) per core:              2
Model name:                      Intel(R) Core(TM) i7-7700HQ CPU @ 2.80GHz
Virtualization:                  VT-x
L1d cache:                       128 KiB
L1i cache:                       128 KiB
L2 cache:                        1 MiB
L3 cache:                        6 MiB
```

## Clone

```shell
git clone https://github.com/6cdh/csapp_exercises.git
```

## Build

```shell
cd csapp_exercises
cmake -G Ninja -D CMAKE_BUILD_TYPE=Release -B build
cmake --build build

# Test
./build/test/csapp_test
```

## Known Issues

Test cases for `float_twice()`, `float_half()`, `float_f2i()`, and `float_i2f()` in chapter 2 will consume too long.

Feel free to correct my English, Code, and others. Thanks!
