XCCONFIG=ios/override.xcconfig


# Open3D

xcodebuild -project build/Open3D.xcodeproj -target install -configuration Release -xcconfig $XCCONFIG
mv build/lib/Release/Python/cpu/*.so build/lib/Release/Python/cpu/pybind.a

rm -rf build/lib/iOS
mv build/lib/Release build/lib/iOS

xcodebuild -project build/Open3D.xcodeproj -target pybind -configuration Release -sdk iphonesimulator -xcconfig $XCCONFIG
mv build/lib/Release/Python/cpu/*.so build/lib/Release/Python/cpu/pybind.a

cd build/lib/Release

inc=../../../ios/install/include

for a in *.a Python/cpu/*.a
do
  rm -rf $a.xcframework
  case $a in
    libOpen3D.a)
      xcodebuild -create-xcframework -library $a -headers $inc -library ../iOS/$a -headers $inc -output $a.xcframework ;;
    *)
      xcodebuild -create-xcframework -library $a -library ../iOS/$a -output $a.xcframework ;;
  esac
done

cd -


# JPEG

xcodebuild -project build/turbojpeg/src/ext_turbojpeg-build/libjpeg-turbo.xcodeproj -target turbojpeg-static -configuration Release -sdk iphoneos -xcconfig $XCCONFIG
xcodebuild -project build/turbojpeg/src/ext_turbojpeg-build/libjpeg-turbo.xcodeproj -target turbojpeg-static -configuration Release -sdk iphonesimulator -xcconfig $XCCONFIG

rm -rf build/turbojpeg/src/ext_turbojpeg-build/JPEG.xcframework

xcodebuild -create-xcframework \
  -library build/turbojpeg/src/ext_turbojpeg-build/Release-iphoneos/libturbojpeg.a \
  -library build/turbojpeg/src/ext_turbojpeg-build/Release-iphonesimulator/libturbojpeg.a \
  -output build/turbojpeg/src/ext_turbojpeg-build/JPEG.xcframework


# Faiss

xcodebuild -project build/faiss/src/ext_faiss-build/faiss.xcodeproj -target faiss -configuration Release -sdk iphoneos -xcconfig $XCCONFIG
xcodebuild -project build/faiss/src/ext_faiss-build/faiss.xcodeproj -target faiss -configuration Release -sdk iphonesimulator -xcconfig $XCCONFIG

rm -rf build/faiss/src/ext_faiss-build/Faiss.xcframework

xcodebuild -create-xcframework \
  -library build/faiss/src/ext_faiss-build/faiss/Release-iphoneos/libfaiss.a \
  -library build/faiss/src/ext_faiss-build/faiss/Release-iphonesimulator/libfaiss.a \
  -output build/faiss/src/ext_faiss-build/Faiss.xcframework


# TBB

xcodebuild -project build/tbb/src/ext_tbb-build/tbb.xcodeproj -target tbb_static -configuration Release -sdk iphoneos -xcconfig $XCCONFIG
xcodebuild -project build/tbb/src/ext_tbb-build/tbb.xcodeproj -target tbb_static -configuration Release -sdk iphonesimulator -xcconfig $XCCONFIG

rm -rf build/tbb/src/ext_tbb-build/TBB.xcframework

xcodebuild -create-xcframework \
  -library build/tbb/src/ext_tbb-build/Release-iphoneos/libtbb_static.a \
  -library build/tbb/src/ext_tbb-build/Release-iphonesimulator/libtbb_static.a \
  -output build/tbb/src/ext_tbb-build/TBB.xcframework


# Assimp

xcodebuild -project build/assimp/src/ext_assimp-build/Assimp.xcodeproj -target assimp -configuration Release -sdk iphoneos -xcconfig $XCCONFIG
xcodebuild -project build/assimp/src/ext_assimp-build/Assimp.xcodeproj -target assimp -configuration Release -sdk iphonesimulator -xcconfig $XCCONFIG

rm -rf build/assimp/lib/Assimp.xcframework

xcodebuild -create-xcframework \
  -library build/assimp/src/ext_assimp-build/code/Release-iphoneos/libassimp.a \
  -library build/assimp/src/ext_assimp-build/code/Release-iphonesimulator/libassimp.a \
  -output build/assimp/lib/Assimp.xcframework

rm -rf build/assimp/lib/IrrXML.xcframework

xcodebuild -create-xcframework \
  -library build/assimp/src/ext_assimp-build/contrib/irrXML/Release-iphoneos/libIrrXML.a \
  -library build/assimp/src/ext_assimp-build/contrib/irrXML/Release-iphonesimulator/libIrrXML.a \
  -output build/assimp/lib/IrrXML.xcframework
