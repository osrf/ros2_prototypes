rm -fr build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
#cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
#cmake ..
make -j8
cd ..
