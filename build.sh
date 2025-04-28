set -euxo pipefail

python3 ../xovi/util/xovigen.py -o xovi.c -H xovi.h rmfakecloud.xovi
$CC -shared -fPIC main.cpp xovi.c `pkg-config --cflags --libs Qt6Network` -o rmfakecloud.so