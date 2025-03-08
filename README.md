Created By: Anthony Cobb  
Date Created: 2-17-22  

VCPlatform. A small wrapper/framework library built around SDL used for personal app and game development.

## TODO
* Finish implementing util data structures ( not important )
    - state machine
    - linkedlist
    - quadtree
    - map
* Redo dynamic array list to be less macro heavy
* Cleanup kdtree to be more inlined with how I structure code now
    - For kdtree I mainly want to just update it to make it clearer
      and finish implimenting the rest of the funcitonality
* Make a simple 2d graphics library with SDL renderer and one for opengl
* Create a mesh_render function that renders the mesh after you
  have uploaded it to the gpu so you don't have to call glDraw
  directly.
* Unit tests for math and util
* Go through code and make everything const if we can
    - I want the default variable to be const from now on
