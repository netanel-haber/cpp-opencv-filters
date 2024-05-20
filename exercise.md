# Ramp Up - Foundations Exercise

### Purpose

- This exercise should allow you to practice the following skills:
    1. Planning of generic, extendable Clean Code using UMLs
    2. Writing of simple, templated C++ code
    3. Simulating memory hierarchies and their substantial performance impact

### Background

- [Explanation on convolutions](https://www.youtube.com/watch?v=KuXjwB4LzSA)
- Some [CV filters](https://medium.com/@shashikadilhani97/digital-image-processing-filters-832ec6d18a73)

### Task

- You will implement the following program:
    - Inputs:
        - Path to 2D (greyscale) PNG
        - Path to desired output PNG
        - Int representing a type of filter that must be applied to this image:
            - Median Filter. Use this image:
                
                ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/e3b38768-ebe2-46b9-8a6a-1730d505ac25/3ca998d8-3d8d-45a3-b1a7-f581f08640fb/Untitled.png)
                
            - Laplacian Filter  (use this image after grey scaling…)
                
                ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/e3b38768-ebe2-46b9-8a6a-1730d505ac25/d29c1033-d18e-40f0-81da-5c1aabee573f/Untitled.png)
                
            - Gaussian Blur Filter (use this image after grey scaling…)
                
                ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/e3b38768-ebe2-46b9-8a6a-1730d505ac25/d29c1033-d18e-40f0-81da-5c1aabee573f/Untitled.png)
                
    - Outputs:
        - None - Filtered image is saved to output path
- Steps:
    - First use OpenCV filters to see that the filters’ effects are as expected
    - Second use filters you implemented

### Constraints

- The filters must be templated to work with int, half, float and double types
- The operation of how the filter is applied (the convolution) must be declared per `Hardware` type. You should declare some interface which different hardwares can implement for the operation (we might just end up using more than 1 HW 😉)
- Compile with CMake

### Completion Criteria

- Output image must look “as expected” (based on the filter type) after execution