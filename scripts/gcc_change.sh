echo "1: change to gcc4.4; 2: change to gcc4.6"
read nn
if [ $nn = 1 ];then
    sudo update-alternatives --install /usr/bin/gfortran gfortran /usr/bin/gfortran-4.4 12
    sudo update-alternatives --install /usr/bin/gfortran gfortran /usr/bin/gfortran-4.6 10
    sudo update-alternatives --install /usr/bin/cpp cpp /usr/bin/cpp-4.4 12
    sudo update-alternatives --install /usr/bin/cpp cpp /usr/bin/cpp-4.6 10
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.4 12
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 10
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.4 12
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.6 10
else
    sudo update-alternatives --install /usr/bin/gfortran gfortran /usr/bin/gfortran-4.4 10
    sudo update-alternatives --install /usr/bin/gfortran gfortran /usr/bin/gfortran-4.6 12
    sudo update-alternatives --install /usr/bin/cpp cpp /usr/bin/cpp-4.4 10
    sudo update-alternatives --install /usr/bin/cpp cpp /usr/bin/cpp-4.6 12
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.4 10
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 12
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.4 10
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.6 12
fi
update-alternatives --display gcc
update-alternatives --display g++
update-alternatives --display gfortran
update-alternatives --display cpp
