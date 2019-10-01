#include <Kokkos_Core.hpp>

int main(int argc, char** argv) {
  Kokkos::initialize(argc, argv);
  const auto N = atoi(argv[1]);
  printf("N %d\n", N);
  Kokkos::View<double*> foo("foo",N);
  Kokkos::Profiling::pushRegion("computeFooRegion");
  Kokkos::parallel_for("computeFoo",N,KOKKOS_LAMBDA(const int& i) {
    foo(i) = (i*i*i)/(i+1);
  });
  Kokkos::Profiling::popRegion();
  Kokkos::finalize();
  return 0;
}
