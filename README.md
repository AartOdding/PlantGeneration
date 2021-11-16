# Node based Plant Generation
Tool for the procedural generation of plants. Complex and beautiful plants can be created by chaining together nodes that perform simple instructions. This design is very well suited to the recursive nature of plants. Plants can also be saved to and loaded from .plant files.
![Image of Node Editor](resources/images/Capture.PNG)
Examples of some plants that have been created using this tool.
![Example of Plants](resources/images/Plants.jpg)
## Building
Make sure you have cmake installed.
First clone this project and its submodules recursively:
```
git clone --recurse-submodules https://github.com/AartOdding/PlantGeneration.git
```
Create and enter /build directory:
```
cd PlantGeneration
mkdir build
cd build
```
Run cmake to generate the build files:
```
cmake ..
```
For windows user just open and build the generated solution file, on other systems you can build the project using cmake as well:
```
cmake --build .
```
