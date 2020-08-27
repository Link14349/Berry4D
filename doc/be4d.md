# .be4d file format
This is a file format for storing 4D graphics and 3D graphics.
这是一个用于存储4d图形以及3d图形的文件格式

## 3D format
```
magic-code[4 bytes]: 62 65 34 66 # Used to verify if this is a .be4d file format
version[1 byte]: 01 # Indicate the version of the file format
file-format[1 byte]: 03 # Indicates that this is a 3D model file
plane-address[4 bytes]: .. .. .. .. # Used to indicate the starting address of the planes storage area
spare-space[8 bytes]: .. .. .. .. .. .. .. .. # Spare
points[.. bytes]: { # Used to store all 3D points
    x[4 bytes]: .. .. .. .. # x component(float)
    y[4 bytes]: .. .. .. .. # y component(float)
    z[4 bytes]: .. .. .. .. # z component(float)
}...
planes[.. bytes]: { # Used to store all 3D triangles
    point1[4 bytes]: .. .. .. .. # The id of the first point(uint32_t)
    point2[4 bytes]: .. .. .. .. # The id of the second point(uint32_t)
    point3[4 bytes]: .. .. .. .. # The id of the third point(uint32_t)
}
```
## 4D format
```
magic-code[4 bytes]: 62 65 34 66 # Used to verify if this is a .be4d file format
version[1 byte]: 01 # Indicate the version of the file format
file-format[1 byte]: 04 # Indicates that this is a 4D model file
body-address[4 bytes]: .. .. .. .. # Used to indicate the starting address of the bodies storage area
spare-space[8 bytes]: .. .. .. .. .. .. .. .. # Spare
points[.. bytes]: { # Used to store all 4D points
    x[4 bytes]: .. .. .. .. # x component(float)
    y[4 bytes]: .. .. .. .. # y component(float)
    z[4 bytes]: .. .. .. .. # z component(float)
    w[4 bytes]: .. .. .. .. # w component(float)
}...
planes[.. bytes]: { # Used to store all 4D bodies
    point1[4 bytes]: .. .. .. .. # The id of the first point(uint32_t)
    point2[4 bytes]: .. .. .. .. # The id of the second point(uint32_t)
    point3[4 bytes]: .. .. .. .. # The id of the third point(uint32_t)
    point4[4 bytes]: .. .. .. .. # The id of the fourth point(uint32_t)
}
```