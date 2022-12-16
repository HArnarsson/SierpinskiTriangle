# A Sierpinski Triangle Generator

This code generates a Sierpinski triangle using an algorithm based in choosing random points and draws them using SFML and C++.

The algorithm:

```
0 Create an equilateral triangle
1 Select a random point within the triangle
2 Select a random vertex on the triangle
3 Draw a point halfway between the most recently drawn point and the vertex selected
4 Go to 2
```
