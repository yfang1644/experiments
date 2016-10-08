#!/bin/sh


TROLLTECHDIR=/home/fang/reports
export QT2DIR=$TROLLTECHDIR/qt-2.3.2
export QTEDIR=$TROLLTECHDIR/qt-embedded-2.3.7
export QPEDIR=$TROLLTECHDIR/qtopia-free-1.7.0


# build qte
cd $QTEDIR
export QTDIR=$QTEDIR
export PATH=$QTDIR/bin:$PATH
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
cp $QPEDIR/src/qt/qconfig-qpe.h src/tools/
./configure -qconfig qpe -qvfb -depths 16,24,32 -system-jpeg -no-xft -gif -xplatform linux-arm-g++  -shared -thread
make sub-src

# build uic
cd $QT2DIR
export QTDIR=$QT2DIR
export PATH=$QTDIR/bin:$PATH
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
./configure -no-opengl -no-xft
make
make -C tools/qvfb
mv tools/qvfb/qvfb bin
cp bin/uic $QTEDIR/bin

# build qtopia
cd $QPEDIR
export QTDIR=$QTEDIR
export PATH=$QPEDIR/bin:$PATH
cd src
./configure  -platform linux-arm-g++
make
