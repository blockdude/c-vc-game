Created By: Anthony Cobb  
Date Created: 2-17-22  

Game.

## TODO
* Fix structure for app to be more clear?
    - Should there only be one global app?
    - Should app manage states or should the programmer?
    - Rename to engine or program?
    - Should the event functions include passing a pointer of the
        app or should it just be void?
    - I kind of want to do something similar to http://gamedevgeek.com/tutorials/managing-game-states-in-c/

* Finish implimenting util data structures ( not important )
    - state machine
    - linkedlist
    - hashset
    - hashmap
    - quadtree
    - kdtree

* For kdtree I mainly want to just update it to make it clearer
    and finish implimenting the rest of the funcitonality

* Create a mesh_upload function that creates a vao and vbo for a
    mesh so that code is neater.

* Create a mesh_render function that renders the mesh after you
    have uploaded it to the gpu so you don't have to call glDraw
    directly.

* Fix frame rate inconsistencies.

* Move everything from lib to src.
