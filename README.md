# Ray Tracer

This ray-tracer, is a basic path tracing program that implements indirect lighting, anti-aliasing, different materials (dielectrics, metals, lambertians), adjustable camera focus, and a positional camera to create basic, but impressive images.

![Sample Render](./rt.png)

**Inspired by** the *Ray Tracing* book series by Peter Shirley, Trevor David Black, and Steve Hollasch:  
<https://github.com/RayTracing/raytracing.github.io/>

---

## Directory Structure

The organization of this repository is meant to be simple and self-evident at a glance:

- `Core/` — contains all source code  
  - `Core/Inc/` — final source for each book in the series
  - `Core/Src/` — final source for each book in the series  

---

## Source Code

### Programming Language

This project is written in C++. The language and features were chosen for broad accessibility rather than peak performance or optimization.

---

## Quickstart

```bash
# Clone the repo
git clone https://github.com/carwho/Ray-tracing.git
cd Ray-tracing

# Build
g++ -std=c++17 main.cc -o raytracer

# Render
./raytracer > output.ppm

# View (requires Python + matplotlib)
python3 ppm_viewer.py
