# 11_dielectrics

dielectric - transparent/ translucent, non-conducting materials that cause light to split at their geometric boundaries
(in the context of computer graphics geometry)

* reflected ray - hits surface then bounce off in new direction
* refracted ray - ray bends as it transitions from a material's surrounding into the material itself
    * bending of the ray is determined by the refractive index
    * embedded materials (i.e. glass ball in water) => effective refractive index of object = (object refractive index) / (surrounding material refractive index)
        => i.e. glass ball effective refractive index = 1.125 = RI of glass (1.5) / RI of water (1.333)

## 11.1 refraction

* rought implementation was to add some offset using the surface's normal
    i.e. `vec3 temporary_refracted_direction = r.direction() - some_fake_offset * rec.normal;`
    => hence there will be higher refraction (different than original direction) at the sides than in the middle
    => (edge) the rays at the side will bounce off and exit the sphere on the opposite side, causing the black ring
    => (middle) whereas the middle portion has minor offsets, causing the ray to go through
* glass balls need to flip the background 180

## 11.2 snell's law

* actually implement proper refraction => snell's law
    * snell's law => 𝜂⋅sin𝜃=𝜂′⋅sin𝜃′
    * use refractive index for the surrounding material & material we are going into
    * then use the ray R & normal vector, to get the R' perpendicular component
    * and finally deduce the R' parallel component (basically use the x component & deduce the y component)

## 11.3 total internal reflection

* critical angle reflection is not implemented => middle of glass sphere is not supposed to be solid white
    why this white portion happens
    - code doesnt have a check to intercept impossible refractions (critical angle)
    - negative calculation is done, calculation strips away the vertical depth component of the vector, making it a flattened horizontal ray
    - it exits parallel to the ground plane (Y=0) where its right in the middle of the blue & white ground
* apply this to ensure critical angle condition is implemented
    - if cant refract => reflect
    - else => refract

## 11.4 schlick approximation

* real glass has reflectivity that varies with angle => we contain that approx. in `reflectance` function

## 11.5 modeling a hollow glass sphere

* create glass sphere in glass sphere