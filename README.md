# Building
```
mkdir build
cd build
cmake .. && make
```

# Usage
1. Compile your homebrew sources to `.o` files
2. Run `vitalink nids.xml a.o b.o c.o ...` to produce `__stubs.S`
3. Compile `__stubs.S`
4. Link everything
5. Run `vitalink --fixup homebrew.elf`

An example is provided in the `sample` directory.


# Things to do/fix
* `.a` archives
* big-endian hosts
* exception tables
* imported variables
* segfault on invalid nids.xml