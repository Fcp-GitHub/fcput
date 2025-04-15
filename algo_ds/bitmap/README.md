# Bitmap
This is an implementation of a bitmap that keeps the memory footprint at a minimum. <br>
## What is a bitmap
A bitmap is just an array of bits, therefore each element can only be one of two values (0/false or 1/true, in C++).<br>
## How this implementation works
Since in C++ (and surely in most high-level languages) the size unit is the byte, the `Bitmap` class takes a non-type template parameter of type `std::size_t` (`Bits` in the implementation) and uses it to create an object of as less bytes as possible. It then proceeds to store each flag in individual bytes and manages them separately.<br>
## Notes on performance
This class was written in order to provide a reasonable data-size/performance ratio, without wasting whole bytes as storage of binary values as well as trying to provide the best assembly generation as possible (tested for x86 and x86-64 for now).
However, keep in mind that the primary focus was reducing the memory footprint using individual bits instead of simply employing `bool` values. Nowadays, working with individual bits can be less performant then working with one or more bytes at once, since it requires more (generally faster, but still) machine instructions to be used in comparison.<br>
## Notes on implementation
While developing a program, it can be useful to define the macro `FCP_ALGODS_BITMAP_DEBUG` before including this header file, in order to get some runtime error checking. More specifically, for now the following runtime error checking gets added by this macro:
- bound checking for the runtime version of the method `at()`.
- bound checking for the runtime version of the method `flip()`.
The compilation-time versions of the methods have bounds checking via `static_cast`s that ensure runtime performance, therefore they are always guaranteed, even when the aforementioned macro is not defined.<br>
Furthermore, the class allows for an arbitrary number of flags, it will adjust its size to the lowest amount of bytes that it can take. As an example:
```
sizeof(fcp::algods::Bitmap<5>())  == 1
sizeof(fcp::algods::Bitmap<24>()) == 3
```

# A simple example
```cpp
/*
 * Hypothetical game code
 */

/*
 * Other includes ... (namespace `game`)
 */

#include <algo_ds/bitmap.hpp>

#define IS_DEAD 0       // flag at index 0
#define IS_MONSTER 1    // flag at index 1
#define IS_FRIEND 2     // flag at index 2

int main(void)
{
    // Initialize all three flags to 0 (false)
    fcp::algods::Bitmap<3> flags(false);

    /* ... */

    if (game::is_monster())
    // Flip to 1 (true) the second flag (position known at compile time)
    flags.flip<IS_MONSTER>();
    // Could also be the following:
    // flags.flip(IS_MONSTER);

    /* ... */

    if (0 >= game::healthbar)
    // FLipto 1 (true) the second flag (position known at compile time)
    flags.flip<IS_DEAD>();
    // Could also be the following:
    // flags.flip(IS_DEAD);
    
    return 0;
}
```
