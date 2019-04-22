rm -rf build
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=/usr/local/Cellar/gcc/8.2.0/bin/g++-8 ..
make

