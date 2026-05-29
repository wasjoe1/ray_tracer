# 13_defocus_blur

## geometry

### terminologies

depth of field (photography term) / defocus blur (ray tracing term)

- focus distance - distance between the camera center & plane where everything is in perfect focus
- focal length - distnace betwee the camera center & image place
    * in our usage, we will set them to be the same => put pixl grid on the focus plane

* in physical camera
    - focus distance is controlled by the dist. between the lens & the film
        => hence u see lens move relative to the camera when changing focus
    - aperture is a hole to control how big the lens is effective
        => for real camera, if you need more light, u make the aperture bigger
        => the draw back is that when you make the aperture bigger to capture more light (i.e. in a dark env) you actually cause the image to be more blurry
* in virtual camera
    - we have perfect sensor & never need more light
        => only use an aperture when we want to defocus blur (only use it for the blur becoz we always have good light)


### blurry & sharp images

Object is at the Focus Distance (Sharp Image)

- object is at the exact focus distance
- lens bends all the rays starting from different parts of the big hole
    so that they meet at the exact same point on the object
- image from rays & object have exact same color, so the image is sharp.

Object is Too Close or Too Far (Blurry Image)

- the rays spread wide apart => They hit completely different parts of the object (or miss it entirely)
- When different colors are average together, the image smears and becomes blurry.

## code

sensor / -> lens -> aperture / focus plane
film
(inside)      |      (outside)
