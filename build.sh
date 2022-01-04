# ./build.sh clang linux 1

compiler="${1:-"clang"}";
os="${2:-"linux"}";
clean="${3:-0}";

. ./.env
CMAKE=${CMAKE:-"cmake"}
EMCMAKE=${CMAKE:-"emcmake"}
CTEST=${CTEST:-"ctest"}

proj="."
pwd
[[ "$compiler" = "clang" ]] && { echo "USING CLANG"; cCompiler="clang"; cppCompiler="clang++"; } || { echo "USING GCC"; cCompiler="gcc"; cppCompiler="g++"; }
[[ "$compiler" = "gcc" || "$compiler" = "clang" ]] && { pickCompiler="$CMAKE -D CMAKE_C_COMPILER=$cCompiler -D CMAKE_CXX_COMPILER=$cppCompiler"; } || { pickCompiler="$EMCMAKE cmake"; }
[[ $clean -eq 1 ]] && trash ./build
export VCPKG_FEATURE_FLAGS=versions
target="$os-$compiler"
[[ ! -d $proj/build/$os/$compiler/vcpkg_installed/x64-$os/include ]] && $CMAKE --preset=$target
{ $CMAKE --build --preset $target || exit 1; }; $CTEST --preset $target

