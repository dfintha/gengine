# gengine

This project is my learning project for the Computer Graphics subject.
Although this code was made after completing the subject, it provides a
testing platform for me to try new things in this field.

The code was written in the C++ language, and utilizes OpenGL through the
GLUT and GLEW libraries. Everything else was written by me.

Be advised: using parts of this code to solve Computer Graphics homeworks
may result in accusations of plagiarism. Use  on your own liability only, and
always indicate the source of parts that may have been used.

## Notes

If you are using Visual Studio, you might get lots of warnings because of the
automatic type conversions between numeric values, and you'll have to define
M\_PI yourself project-wide, as MSVC's cmath header does not contain it somehow.

## To-Dos
* Custom Pi class included everywhere, so it can be used in the main program.
* Command-line switch for NPR mode.
* Change geo::vector's underlying type to double.

## License

This software falls under the MIT License.

Copyright (c) 2018 Dénes Fintha

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
