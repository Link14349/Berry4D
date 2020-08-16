# Berry4D  
This is a simple projection of four-dimensional objects into three-dimensional space, and then the projection objects are presented on the 2D screen.  
这是一个简单的将四维物体投影到三维空间中再将投影物体呈现在2D屏幕上的程序.

## Foundations of Mathematics 一些数学基础理论推导
### 1. Coordinate system 坐标系设定:
xyz space
```
y   z
^  ^
| /
|/--> x
```
xyw space
```
y   w
^  ^
| /
|/--> x
```
xzw space
```
w   z
^  ^
| /
|/--> x
```
yzw space
```
y   z
^  ^
| /
|/--> w
```
### 2. Projection 投影
#### 2.1 Camera Settings 相机设置
In camera coordinates, we set the camera to point in the positive direction of the w axis.  
在相机坐标中，我们设定相机指向w轴正方向.
The camera has three line of sight angles ` f_ x`, `f_ y`, `f_ z` is used to describe half of the viewing angle of the camera in the x, y, z axes.  
相机拥有三个视线角`f_x`, `f_y`, `f_z`用来描述相机在x, y, z轴方向上可观察范围角度的一半.
#### 2.2 Projection: Perspective Projection 投影: 透视投影
$$
\begin{cases}
x'=\frac{x}{w\tan f_a}\\
y'=\frac{y}{w\tan f_a}\\
z'=\frac{z}{w\tan f_a}
\end{cases}
$$
### 3. Rotation 旋转
We remember $R_t$ is the rotation matrix of $\theta$ that rotates clockwise about the t axis.  
我们记$R_t$为绕t轴顺时针旋转$\theta$的旋转矩阵  
$$
R_x=\left[\begin{array}{ccc}
1 & 0 & 0 & 0 \\
0 & \cos\theta & -\sin\theta & -\sin\theta \\
0 & \sin\theta & \cos\theta & \sin\theta \\
0 & \sin\theta & -\sin\theta & \cos\theta
\end{array}\right]
$$
$$
R_y=\left[\begin{array}{ccc}
\cos\theta & 0 & \sin\theta & \sin\theta \\
0 & 1 & 0 & 0 \\
-\sin\theta & 0 & \cos\theta & -\sin\theta \\
-\sin\theta & 0 & \sin\theta & \cos\theta
\end{array}\right]
$$
$$
R_z=\left[\begin{array}{ccc}
\cos\theta & -\sin\theta & 0 & -\sin\theta \\
\sin\theta & \cos\theta & 0 & \sin\theta \\
0 & 0 & 1 & 0 \\
\sin\theta & -\sin\theta & 0 & \cos\theta
\end{array}\right]
$$
$$
R_w=\left[\begin{array}{ccc}
\cos\theta & -\sin\theta & \sin\theta & 0 \\
\sin\theta & \cos\theta & -\sin\theta & 0 \\
-\sin\theta & \sin\theta & \cos\theta & 0 \\
0 & 0 & 0 & 1
\end{array}\right]
$$
**!!!: Note that the length of the column vector of this rotation matrix is greater than 1, which needs to be manually divided back, otherwise there will be amplification effect!**  
**!!!: 注意，这个旋转矩阵的列向量长度大于1需要手动除回去否则会有放大效应！**