# Ray Tracing in One Weekend in C

This project is my implementation of the fantastic ray tracing project [Ray
Tracing on One
Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html "Link to
book") by Peter Shirley. The original ray tracer (and it's extensions) are
implemented in C++ but I wanted to write a ray tracer in plain C just for fun.
Writing linear algebra operations in a readable way is without OOP and operator overloading is pain in the *#s.

## Installation

Clone repository

``` shell
git clone https://github.com/malmgrek/RayTracingInOneWeekend.c
```

Build with CMake (from the project directory root), make, and run:

``` shell
cmake -B build && (cd build && make) && ./build/inOneWeekend --bar > test.ppm
```

Optionally show image:

``` shell
feh test.ppm
```

<p align="center"> <img src="https://raw.githubusercontent.com/malmgrek/RayTracingInOneWeekend.c/master/resources/images/example.png"
  </p>

Measure execution time:

``` shell
time ./build/inOneWeekendC > /dev/null
```

