David Friedman
#998881687

All shapes drawn with scanline fill algorithm.

Scanline fill not restricted to triangles.
Scanline fill takes two arguments, array and num points+1. Last element in array must be same as first.
Scanline fill fails on some concave angles due to not fully implemented checking of verticies, but works for cases required in this homework.

list is custom linked list made for scanline fill.
graphics is a set of custom drawing commands used to draw the scene (including the scanline fill algorithm)