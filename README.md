

A C++17 engine for differential operators with polynomial coefficients: exact operator algebra, plus numerical solving and monodromy in the complex plane. Not fully functional 




> Dx*x
x*Dx + 1
> monodromy x^2*Dx^2 + x*Dx + x^2 - 1/9
  eigenvalues: -0.5 - 0.866025i,  -0.5 + 0.866025i
  local exponents (mod 1): 2/3,  1/3
Build

Requires a C++17 compiler and CMake 3.16+.



The project is inspired by the algebraic analysis of Sato, Kashiwara and Kawai, in particular the book “Foundations of Algebraic Analysis” by Kashiwara, Kawai and Kimura. "Holonomic" refers to systems of differential equations whose characteristic variety is as small as possible. Their solutions (Airy, Bessel, hypergeometric functions and many more) are determined by finitely many numbers, which is what makes them computable. This engine is not yet finished and useable as I continue to work through understanding the book.
