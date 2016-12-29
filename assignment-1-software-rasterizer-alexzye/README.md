# Assignment 1: Software Rasterizer
## Alex Ye (aye01)


### Problems
I have a minor problem making the border of the triangles blend. As a result, you can see the borders of some of the triangles. It is pretty apparent in the teapot and sphere, but, you can notice that the triangles are relative to the depth of point.

### Interpolation
The two colors I used for the two color interpolation were red and green.


### Running

The project can be run by running the raster program with the following format:

./raster obj_file output x y color_mode

An example if your resource folder is in the root dircetory:

./raster ../resources/bunny.obj output 1000 500 1