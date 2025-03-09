## C Coding Style Conventions

Code element             | Convention            | Example
---                      | :---:                 | ---
Defines                  | UPPER_SNAKE_CASE      | `#define PLATFORM_DESKTOP`
Macros                   | UPPER_SNAKE_CASE      | `#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )`
Variables                | snake_case            | `int screen_width = 0;`, `float target_frame_time = 0.016f;`
Local variables          | snake_case            | `struct vec2 player_position = { 0 };`
Global variables         | g_snake_case          | `bool g_fullscreen = false;`
Constants                | snake_case            | `const int max_value = 8;`
Pointers                 | Type *pointer         | `int *array = NULL;`
float values             | always x.xf           | `float gravity = 10.0f`
Operators *              | value1 * value2       | `int product = value * 6;`
Operators /              | value1 / value2       | `int division = value / 4;`
Operators +              | value1 + value2       | `int sum = value + 10;`
Operators -              | value1 - value2       | `int diff = value - 5;`
Enum                     | snake_case            | `enum texture_format`
Enum members             | UPPER_SNAKE_CASE      | `PIXELFORMAT_UNCOMPRESSED_R8G8B8`
Struct                   | snake_case            | `struct vec2_f32`, `struct material`
Struct typedef           | snake_case_t          | `typedef struct texture { ... } texture_t;`
Function pointer typedef | snake_case_fn_t       | `typedef void ( *foo_fn_t )( void *, int );`
Struct members           | snake_case            | `texture.width`, `color.r`
Functions                | snake_case            | `init_window()`, `load_image_from_memory()`
Functions params         | snake_case            | `width`, `height`
Ternary Operator         | ( condition ) ? a : b | `printf( "Value is 0: %s", ( value == 0 ) ? "yes" : "no" );`

Other conventions:
 - All defined variables default modifier should be const
 - All defined variables are ALWAYS initialized
 - Avoid typedef-ing structures and enums
 - Four spaces are used, instead of TABS
 - Trailing spaces are always avoided
 - Type modifiers, "signed" and "unsigned", always go before "short" and "long" in a declaration
 - Type modifiers always go before the type
 - Type qualifiers always go before the type and/or type modifiers, obviously excluding type qualifiers for pointers which must go on the right of the pointer
 - Storage class specifiers are always specified before any type qualifiers, type modifiers, and/or type
 - Casts are seperated with a space:
```c
int foo = 10;
i32 val = ( i32 ) foo;
f32 bar = ( f32 ) ( foo / val );
```
 - Function prototypes and implementations with no parameters must put "void" as the parameter:
```c
extern void foo( void );
void foo( void )
{
    // do something
}
```
 - Function prototypes always explicitly state extern:
```c
// header.h
extern void foo( void );
extern void bar( int b );

// source.c
void foo( void )
{
    // do something
}

void bar( const int b )
{
    // do something else
}
```
 - Function prototypes should specify pointer parameters as const if the function does not modify data:
```c
extern void foo( const char *in, char *out ); // "in" will not be modified
extern void bar( char *data ); // "data" will be modified
```
 - Function implementations should specify all their parameters as const:
```c
// We don't specify "const" in the prototype because
// it is an implementation detail that is useless for
// the caller.
extern void bar( int a );
extern void foo( const char *in, char *out );

// Here we specify "const" because in the
// implementation, we will not modify "a" anywhere in
// the function. Note: this is valid C as both the
// prototype and the implementation still maintain
// the same signature.
void bar( const int a )
{
    // the value of a will not change through out this function
}

// The same will apply to pointers for example in this
// implementation we know now that "in" won't ever be reassigned
// throughout the function.
void foo( const char *const in, char *const out )
{
    // "in" will not be modified and the "in" pointer will not point to different memory
    // the "out" pointer will never point to different memory
}
```
 - All statements within parenthesis or brakets are padded **by a space**:
```c
char buffer[ 256 ] = { 0 };
snprintf( buffer, 256, "%s", "Hello, world!" );

if ( foo( bar ) )
{
    
}

printf( buffer );
```
 - Cases are flush with switch statements:
```c
switch ( value )
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
if ( condition ) value = 0;

while ( !window_should_close() )
{

}

for ( int i = 0; i < NUM_VALUES; i++ ) printf( "%i", i );

switch ( value )
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
if ( ( value > 1 ) && ( value < 50 ) && value_active )
{

}
```
 - Braces and curly brackets always open-close in aligned mode:
```c
void some_function( void )
{
   // TODO: Do something here!
}

struct foo_bar
{
    int a;
    int b;
    char buffer[ 256 ];
};
```

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
