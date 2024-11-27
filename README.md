# PPM Image Editor: A Custom Image Processing Application :camera: :computer:

<br>

## 📢Note📢
🎯Please, clone this repository before reading the description. Don't forget to like👍and share your thoughts😊.

<br>

## About
This repository demonstrates an image editing application developed as part of an academic assignment. The project includes the implementation of a generic 2D data representation class, extended to handle images in the PPM format. Core functionality involves reading and writing PPM files via a custom library, enabling efficient image storage and retrieval. Additionally, a suite of image processing filters is provided, allowing users to apply transformations parametrically by passing arguments at runtime. This project showcases fundamental concepts in data representation, file handling, and image manipulation.

## Filters
The application supports two different filter implementations. Each filter is represented using a different class.

### Linear Filter
**FilterLinear** class applies to each pixel $pp(xx, yy)$ of the input image (right operator) the following formula:

$pp′(xx, yy) = aa ∙ pp(xx, yy) + cc$

Where $pp′(xx, yy)$ represents the pixel in the coordinate $(x,y)$ of the image created and returned by operator and $a$, $c$ two fixed vector values. For example, if $aa = (-1, -1, -1)$ and
$cc = (1, 1, 1)$ the filter should produce the negative of the original image. Please note that values of $a$ and $c$ should be restricted to the interval [0,1] for each channel colour channel.

### Gramma Filter
**FilterGramma** implements the following operation:

$pp′(xx, yy) = pp(xx, yy)^v$

Where each colour channel of a pixel is raised to the exponent $v$. Typical values for $v$ range between 0,5 and 2,0.

## Execution
The following pattern displays the way the application is executed:

```filter -f [filter 1] [parameters] ... -f [filter k] [parameters] [parameters] [image file name]```

The ```-f``` specifier is followed by the name of the filter, which can be either ```linear``` or ```gamma```, and immediately after a series of arguments corresponding to the specialized parameters of each filter. The ```linear``` filter should be followed by 6 float numbers corresponding to to the coordinates of the and $a$, $c$ vectors. The ```gamma``` filter shall be followed by 1 parameter which corresponding to the exponent $v$.

The input image filename is always given last. If no filter is given, the application immediately terminates. If no file is specified or no filter name is given correctly, the application immediately terminates as well. The number of filters and their type is determined at runtime based on the parameters taken by the application from the command line. Also, a filter may be applied multiple times and with different parameters each time. The order of application of filters is from left to right. Three examples follow.

- ```filter -f gamma 2.0 -f linear -1 -1 -1 1 1 1 image01.ppm```
- ```filter -f gamma 2.0 -f gamma 0.5 image01.ppm```
- ```filter –f gamma 0.7 -f linear 1 0.8 0.3 0.1 0.1 0.3 –f gamma 1.2 image02.ppm```
