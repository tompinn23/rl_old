# rl

Rl is a new rougelike game.  
It will have feature like.
- Lua modding / extensibility.
- Advanced ASCII graphics.
- More.

## Building

To build rl you will need cmake 3.0, a c++17 compiler.
eg.
 - Visual Studio 2017
 - GCC 6+ ??
 - CLANG 3.9 or 4+

As well as some form of the filesystem library either boost or standard.  
To compile run the following commands.
```
mkdir build
cd build 
cmake ..
make or msbuild rl.sln or ninja
```

If using the Visual Studio Generator. Make sure you set 64bit by using  
-G"Visual Studio 15 2016 Win64"

If you really want 32 bit you need to replace the bearlibterminal.dll/.so with a 32bit version.

## License
rl is licensed under GPL-3.0  
A copy of the license is included with this repository.  
Or you can find a copy at [https://www.gnu.org/licenses/gpl-3.0.en.html](https://www.gnu.org/licenses/gpl-3.0.en.html)