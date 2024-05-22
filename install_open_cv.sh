OPEN_CV_VERSION="${1:-4.9.0}"

mkdir -p Open_CV/build
cd Open_CV
wget https://github.com/opencv/opencv/archive/$OPEN_CV_VERSION.zip
unzip "$OPEN_CV_VERSION.zip"
cd build
cmake "../opencv-$OPEN_CV_VERSION" -DWITH_QT=OFF -DWITH_OPENGL=OFF -DFORCE_VTK=OFF -DWITH_TBB=OFF -DWITH_GDAL=OFF -DWITH_XINE=OFF -DBUILD_EXAMPLES=OFF -DBUILD_ZLIB=OFF -DBUILD_TESTS=OFF .
make -j7
sudo make install
