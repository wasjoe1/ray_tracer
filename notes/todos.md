TODO

DOING

DONE
- chapter 14: final render
    => copy over the code
    => clean code
    => write README, learnings & whats next for me (refer to the section `missing concepts in this text book` in the readme)
- chapter 13: defocus blur
- chapter 12: positionable camera
- chapter 11: dielectrics
    - refraction => arbitrary refraction
    - snells law => proper refraction
    - total internal reflection => critical angle
    - schlick appoximation => reflectivity varies with angle
    - hollow glass (just a render)
- chapter 10: diffuse metal
- chapter 9: diffuse materials
- chapter 8: antialiasing
- chapter 7: camera class abstraction
    - public & private members ŵ initialize() & render()
- chapter 6: surface normals & multiple objects
    => shade using normal vectors (map the normal vectors to colors)
    => simplify ray-sphere intersection code (the b in discriminant => i did not do this section)
    => front face vs back face (if back face, flip the normal vector)
    => hittable, hittable_list
    => cpp new features: shared_ptr & make_shared => allocates object & control block in 1 operation
    => common constants & utility function => "God header file"
    => interval class: for both color & ray tracing
- chapter 5: finish up the sphere portion
    * current issues/ missing features:
    => missing shading, reflection rays & more than 1 object
    => negative t vals work fine (meaning if the circle is behind the camera this will say it still intersects) => bad!! since we are only suppose to see objects IF they are infront of the camera
- initial TODOS:
    - read book to understsand structure + content & create plan for execution
    - create simple readme
    - download latest version of book (.zip file) for offline reference
    - download cppreference.com archive for offline reference
