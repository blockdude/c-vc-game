## C Coding Style Conventions

Code element             | Convention        | Example
---                      | :---:             | ---
Defines                  | UPPER_SNAKE_CASE  | `#define PLATFORM_DESKTOP`
Macros                   | UPPER_SNAKE_CASE  | `#define MIN(a, b) (((a) < (b)) ? (a) : (b))`
Variables                | snake_case        | `int screen_width = 0;`, `float target_frame_time = 0.016f;`
Local variables          | snake_case        | `struct Vec2 player_position = { 0 };`
Global variables         | g_snake_case      | `bool g_fullscreen = false;`
Constants                | snake_case        | `const int max_value = 8;`
Pointers                 | Type *pointer     | `int *array = NULL;`
float values             | always x.xf       | `float gravity = 10.0f`
Operators *              | value1 * value2   | `int product = value * 6;`
Operators /              | value1 / value2   | `int division = value / 4;`
Operators +              | value1 + value2   | `int sum = value + 10;`
Operators -              | value1 - value2   | `int diff = value - 5;`
Enum                     | PascalCase        | `enum TextureFormat`
Enum members             | UPPER_SNAKE_CASE  | `PIXELFORMAT_UNCOMPRESSED_R8G8B8`
Struct                   | PascalCase        | `struct Vec2F32`, `struct Material`
Struct typedef           | PascalCase        | `typedef struct Texture { ... } Texture;`
Function pointer typedef | PascalCaseFn      | `typedef void (*FooFn)(void *, int);`
Struct members           | snake_case        | `texture.width`, `color.r`
Functions                | snake_case        | `init_window()`, `load_image_from_memory()`
Functions params         | snake_case        | `window_width`, `window_height`
Ternary Operator         | condition ? a : b | `printf("Value is 0: %s", value == 0 ? "yes" : "no");`

Other conventions:
 - All defined variables default modifier should be const
 - Avoid not initializing defined variables
 - Avoid typedef-ing structures and enums
 - Four spaces are used, instead of TABS
 - Trailing spaces are always avoided
 - Type modifiers, "signed" and "unsigned", always go before "short" and "long" in a declaration
 - Type modifiers always go before the type
 - Type qualifiers always go before the type and/or type modifiers, obviously excluding type qualifiers for pointers which must go on the right of the pointer
 - Storage class specifiers are always specified before any type qualifiers, type modifiers, and/or type
 - Try and follow const correctness
 - Casts should not be followed by a space:
```c
int foo = 10;
i32 val = (i32)foo;
f32 bar = (f32)(foo / val);
```
 - Function prototypes avoid explicitly stating extern:
```c
// header.h
void foo(void);
void bar(int b);

// source.c
void foo(void)
{
    // do something
}

void bar(int b)
{
    // do something else
}
```
 - Function prototypes and implementations with no parameters must put "void" as the parameter:
```c
void foo(void);
void foo(void)
{
    // do something
}
```
 - Function prototypes should specify pointer parameters as const if the function does not modify data (readonly):
```c
void foo(const char *in, char *out); // "in" will not be modified
void bar(char *data); // "data" will be modified
```
 - All statements within parenthesis or brakets should NOT have a space:
```c
char buffer[256] = { 0 };
snprintf(buffer, 256, "%s", "Hello, world!");

if (foo(bar))
{
    
}

printf(buffer);
```
 - All statements within curly braces should be padded **by a space**:
```c
char buffer[256] = { 0, 2, 4, 313, [42] = 200 };
```
 - Cases are flush with switch statements:
```c
switch (value)
{
case 0:
    foo();
    break;
case 1:
    bar();
    break;
case 2:
    {
        int a = 0;
        break;
    }
default:
    break;
}
```
 - Control flow statements are followed **by a space**:
```c
if (condition) value = 0;

while (!window_should_close())
{

}

for (int i = 0; i < NUM_VALUES; i++) printf("%i", i);

switch (value)
{
case 0:
    {

    } break;
case 2: break;
default: break;
}
```
 - All conditions are always between parenthesis, but not boolean values:
```c
if ((value > 1) && (value < 50) && value_active)
{

}
```
 - Braces and curly brackets always open-close in aligned mode:
```c
void some_function(void)
{
   // TODO: Do something here!
}

struct FooBar
{
    int a;
    int b;
    char buffer[256];
};
```

## C++ Coding Style Conventions

Code element             | Convention        | Example
---                      | :---:             | ---
Struct / Enum class      | PascalCase        | `struct Entity`, `enum struct ItemID : u16`
Enum members             | UPPER_SNAKE_CASE  | `ItemID::STONE`, `TileLayer::TERRAIN`
Functions / Methods      | snake_case        | `EntityPlayer::update()`
Private members          | _snake_case       | `_state`, `_items`, `_move`
Constants                | UPPER_SNAKE_CASE  | `COLOR_WHITE`, `TICKRATE`
Pointers                 | Type *name        | `Entity *target`
References               | Type &name        | `World &world`

Other conventions:
  - Never use the `class` keyword — always `struct`
  - `override` on all overridden virtual methods; don't repeat `virtual`
  - `const` methods when the function doesn't modify the object: `void draw() const`
  - `constexpr` preferred over `#define` for constants
  - Use `enum struct` (not `enum class`)
  - `explicit` on single-argument constructors to prevent implicit conversions
  - `nullptr` over `NULL` or `0` for null pointers
  - Default member initializers preferred over constructor init lists: `Vec2 _move = vec2_zero()`
  - RAII — avoid raw `new`/`delete`; use `std::unique_ptr`, containers, or stack allocation
  - Avoid `auto` — only use it for range-based for loops or when the type is complex and otherwise unreadable
  - No `using namespace std`; type aliases with `using` are acceptable
  - Include order: own header first (`""`), then standard library (`<>`), then external/vendored libraries (`<>`), then internal project headers (`""`).
    - Own header: the `.h` matching the current `.cc` — always first, always quotes
    - Standard library: `<memory>`, `<vector>`, `<cassert>`, `<string>`
    - External/vendored: `<SDL3/SDL.h>`, `<stb_image.h>`, `<vcp/vcp.h>`
    - Internal project: `"core/common.h"`, `"world/world.h"`, `"entity/entity.h"` — full path from the source root (`game/src/`), no `../` traversal
  - Include guards: same as C — `#ifndef` / `#define` / `#endif`
  - Access sections: `public:` / `protected:` / `private:` explicit where needed
  - Member ordering: `public` first, then `protected`, then `private`. Readers care about the API; implementation details go last
  - If a struct has no `private` or `protected` members, do not specify `public:` — it is implicit with `struct`
  - If a struct has `private` or `protected` members, it must begin with `public:`
  - `this->` required when accessing member variables or calling member functions inside methods
  - `= default` for explicitly-defaulted special member functions
  - Avoid runtime exceptions (try / catch / throw)

## Files and Directories Naming Conventions

  - Directories are named using `snake_case`: `resources/models`, `resources/fonts`
  - Files are named using `snake_case`: `main_title.png`, `cubicmap.png`, `sound.wav`

_NOTE: Spaces and special characters are always avoided in the files/dir naming!_

## Games/Examples Directories Organization Conventions

 - Resource files are organized by context and usage in the game. Loading requirements for data are also considered (grouping data when required).
 - Descriptive names are used for the files, just reading the name of the file it should be possible to know what is that file and where fits in the game.

```
resources/audio/fx/long_jump.wav
resources/audio/music/main_theme.ogg
resources/screens/logo/logo.png
resources/screens/title/title.png
resources/screens/gameplay/background.png
resources/characters/player.png
resources/characters/enemy_slime.png
resources/common/font_arial.ttf
resources/common/gui.png
```
_NOTE: Some resources require to be loaded all at once while other require to be loaded only at initialization (gui, font)._
