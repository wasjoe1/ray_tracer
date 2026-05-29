# 12_positionable_camera

## 12.1 camera viewing geometry

* changing the view port (what you can see) using field of view (visual angle edge to edge)

- previoulsy we locked viewport height at 2.0 `auto viewport_height = 2.0;`
    => camera is stuck with 1 type of lens; cant zoom in or out
- *fov* allows u to set angles to either increase viewport OR decrease viewport
    => wide angle blows up viewport window, whereas narrow angle shrinks viewport window
- viewport is ultimately still the boundary that decides the boundaries the rays hit
    BUT *fov* lets you increase or decrease the viewport
    => *fov* allows for zooming in or out

## 12.2 positioning & orienting camera

### general geometry

look from => where the camera looks from
look at (target point) => where the camera looks at
look in (direction vector) => direction where the camera should be facing

view up - defines which way is "up" for the camera's head

* to orientate the camera, we need the look from + look at OR look in + view up

### Camera orientation vectors

- vup (view up) - camera-relative up vector, defines which way is "up" for the camera's head
- v - unit vector pointing to camera up [different-from-vup]
- u - unit vector pointing to camera right
- w - unit vector pointing opposite the view direction
- camera center - is currently the origin

### up vector

author says:
"We can specify any up vector we want, as long as it's not parallel to the view direction.
Project this up vector onto the plane orthogonal to the view direction to get a
camera-relative up vector."

SO, only have *vup*, *lookfrom* & *lookat* / *lookin*
    => need to get __u, v & w__

- w = lookfrom - lookat
- u = cross(vup, w)         => we need to know camera right to know where to extend the area that we are shooting rays from
- v = cross(w,u)            => determine whats considered vertical relative to the camera

* cross product is used to find the perpendicular vectors of 2 vectors