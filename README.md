# Parallel Matrix Multiplication

This small repository compares the performance of multiple threads vs just one thread for multiplication of matrices.

## Showcase

This showcase compares the naive approach of having a thread for each row-column combination.
For example, if there are two 30x30 matrices mutliplied, 30 threads are created.

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

On an eight thread machine and a matrix size `sz = 2000` the result is the following:

```bash
multiplication serial:
exec. time: 52.474451

multiplication parallel:
exec. time: 10.248091
cpu uptime: 74.833354
```

For matrix size `sz = 4000`:

```bash
multiplication serial:
exec. time: 552.366112

multiplication parallel:
exec. time: 106.235075
cpu uptime: 769.289494
```

### Seminaive approach

Somehow, the 'seminaive' approach is slower than the 'naive' approach. Here the 'naive' approach is to create a thread for each row, while the seminaive approach creates only a specified number of threads. this is specified using `NUM_THREADS`.

