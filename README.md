# helloKokkos3Profiling
example of Kokkos3 GPU profiling

The following instructions assume that Kokkos 3 (`cmake-promotion` branch) was
installed with CMake and the kokkos-tools `nvprof-connector` library
`kp_nvprof_connector.so` was compiled.

# build on summit

```
module swap xl gcc/7.4.0
module load cuda/10.1.168
module load cmake
export CMAKE_PREFIX_PATH=/path/to/kokkos/install:$CMAKE_PREFIX_PATH
mkdir build
cd !$
cmake /path/to/helloKokkos3Profiling/ -DCMAKE_CXX_COMPILER=/path/to/kokkos/bin/nvcc_wrapper
make 
```

# run on summit

create a run script `run.sh`:

```
#!/bin/bash
module swap xl gcc/7.4.0
module load cuda/10.1.168
kkt=/path/to/kokkos-tools/nvprof-connector/kp_nvprof_connector.so
export KOKKOS_PROFILE_LIBRARY=$kkt
#run on one process using one gpu
jsrun --tasks_per_rs 1 --nrs 1 --gpu_per_rs 1 --cpu_per_rs 1 \
   nvprof -m achieved_occupancy /path/to/hello/binary $((1024*1024))
```

make it executable:

```
chmod +x run.sh
```

submit the job:

```
bsub -W 5 -nnodes 1 -P yourProjectId < ./run.sh
```

# expected output

see `profilingOutput.txt`


Running under `nvprof` with no metrics collected, and the nvprof-connector
kokkos-tools library set in the environment, will produce output with the
named kokkos kernels listed under the NVTX heading.  'regions' created
with `Kokkos::Profiling::pushRegion(...)/popRegion()` will not be listed.
When metrics are collected the nvprof output will not contain the named kokkos kernels.
