set -euxo pipefail

python3 ../xovi/util/xovigen.py -o xovi.c -H xovi.h rmfakecloud.xovi
python3 ../xovi/util/xovigen.py -o websocket-xovi.c -H websocket-xovi.h websocket.xovi
$CC -shared -fPIC main.cpp xovi.c `pkg-config --cflags --libs Qt6Network` -o rmfakecloud.so
$CC -shared -fPIC websocket.cpp websocket-xovi.c `pkg-config --cflags --libs Qt6Network Qt6WebSockets` -o rmfakecloud-websocket.so
