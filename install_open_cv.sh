OPEN_CV_VERSION="${1:-4.9.0}"
ARCH=$( [[ "$(uname -m)" == "arm64" ]] && echo "arch -arm64" )

mkdir -p Open_CV/build
cd Open_CV
wget https://github.com/opencv/opencv/archive/$OPEN_CV_VERSION.zip
unzip "$OPEN_CV_VERSION.zip"
cd build
$ARCH cmake "../opencv-$OPEN_CV_VERSION" -DWITH_QT=OFF -DWITH_OPENGL=OFF -DFORCE_VTK=OFF -DWITH_TBB=OFF -DWITH_GDAL=OFF -DWITH_XINE=OFF -DBUILD_EXAMPLES=OFF -DBUILD_ZLIB=OFF -DBUILD_TESTS=OFF .
$ARCH make -j7
$ARCH sudo make install
