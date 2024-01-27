# Parallel Matrix Multiplication

This small repository compares the performance of multiple threads vs just one thread for multiplication of matrices.

## Showcase

### Two core machine with four threads

On a four thread machine and a matrix size `sz = 2000` the result is the following:

``` bash
$ ./matrix 
multiplication serial: 
exec. time: 66.051907

multiplication parallel: 
exec. time: 28.444849
cpu uptime: 109.417870

```

Here you can observe, that using the four threads is overall faster. But the overhead of creating several threads leads to a higher cpu uptime.

### Eight core machine



