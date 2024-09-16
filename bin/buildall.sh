declare -r ROOT_DIR=${TIPDIR:-$(git rev-parse --show-toplevel)}
cd ${ROOT_DIR}/build/
cmake .. >  ${ROOT_DIR}/build/.buildall
echo cmake done
make -s -j6 all > ${ROOT_DIR}/build/.buildall
${ROOT_DIR}/bin/runtests.sh
