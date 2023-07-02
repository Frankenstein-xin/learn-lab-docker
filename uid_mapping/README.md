# learn-lab-docker
## About this program
- This is a simple experimental program shows how the docker working underneath it's appearance, and this program also shows the functionality of C APIs of linux namespace and cgroup. 
- The accompanying commands shows how to reconf and build this program
  ```bash
  autoreconf --install --force
  mkdir build
  cd build
  ../configure CXXFLAGS="-g -O0"
  make
  ```