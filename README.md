![Render](./rt.png)

# Ray Tracer

Path tracer in C++ following Peter Shirley's "Ray Tracing in One Weekend" series.

- Indirect lighting (objects illuminate each other)
- Anti-aliasing via random sampling
- Materials: lambertian diffuse, metals, glass/dielectrics
- Adjustable camera position and focus depth

## Math

Each pixel fires multiple rays with slight random offsets for anti-aliasing. Rays bounce around the scene accumulating color until they hit a light source or max out on bounces.

Dielectrics (glass) were the trickiest - had to implement Schlick's approximation for reflectance at grazing angles, otherwise glass looked wrong at the edges.

Renders to PPM format. The image above took about 2 minutes at 1200x800 with 500 samples per pixel.

Based on: https://github.com/RayTracing/raytracing.github.io/
