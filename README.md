# MontgomeryMultiplication
32 and 64 bit montgomery multiplication in C++

## Usage

`montctx32_t(x)` and `montctx64_t(x)` contains data of a modulus `x` needed for the montgomery optimization

`mont30_t` `mont31_t` `mont62_t` `mont63_t` can take care of corresponding bits of modulus. The latter two can only be used if `__int128` is supported. 

The modulus can be changed on the fly, with `montXX_t::setctx()`.
 
`operator` `+` `-` `*` and convertion to and from an int and I/O is implemented.
