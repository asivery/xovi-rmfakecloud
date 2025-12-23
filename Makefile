CC += -D_GNU_SOURCE -fPIC
CXX += -D_GNU_SOURCE -fPIC
CXXFLAGS += $(shell pkg-config --cflags --libs Qt6Network Qt6WebSockets)
CFLAGS += $(shell pkg-config --cflags --libs Qt6Network Qt6WebSockets)
VPATH = src

ifeq ($(OECORE_TARGET_ARCH), aarch64)
RMFCX_ARCH=aarch64
else ifeq ($(OECORE_TARGET_ARCH), arm)
RMFCX_ARCH=arm32
else
$(error Bad build target. Source the toolchain environment)
endif
all: rmfakecloud_ns rmfakecloud_ws rmfakecloud_ts

objects_networkaccess = networkaccess-part.o xovi-networkaccess.o
rmfakecloud_ns : $(objects_networkaccess)
	${CC} ${CFLAGS} -shared -o rmfakecloud_ns.so $(objects_networkaccess)
xovi-networkaccess.cpp xovi-networkaccess.h	&: rmfakecloud-networkaccess.xovi
	python3 ${XOVI_REPO}/util/xovigen.py -a ${RMFCX_ARCH}  -o xovi-networkaccess.cpp -H xovi-networkaccess.h rmfakecloud-networkaccess.xovi
networkaccess-part.o	: xovi-networkaccess.h src/networkaccess-part.cpp src/commons.cpp

objects_websocket = websocket-part.o xovi-websocket.o
rmfakecloud_ws : $(objects_websocket)
	${CC} ${CFLAGS} -shared -o rmfakecloud_ws.so $(objects_websocket)
xovi-websocket.cpp xovi-websocket.h	&: rmfakecloud-websocket.xovi
	python3 ${XOVI_REPO}/util/xovigen.py -a ${RMFCX_ARCH}  -o xovi-websocket.cpp -H xovi-websocket.h rmfakecloud-websocket.xovi
websocket-part.o	: xovi-websocket.h src/websocket-part.cpp src/commons.cpp

objects_tokenstore = tokenstore-part.o xovi-tokenstore.o
rmfakecloud_ts : $(objects_tokenstore)
	${CC} ${CFLAGS} -shared -o rmfakecloud_ts.so $(objects_tokenstore)
xovi-tokenstore.cpp xovi-tokenstore.h	&: rmfakecloud-tokenstore.xovi
	python3 ${XOVI_REPO}/util/xovigen.py -a ${RMFCX_ARCH}  -o xovi-tokenstore.cpp -H xovi-tokenstore.h rmfakecloud-tokenstore.xovi
tokenstore-part.o	: xovi-tokenstore.h src/tokenstore-part.cpp



.PHONY  : clean
clean :
	rm -f rmfakecloud_ns.so rmfakecloud_ws.so rmfakecloud_ts.so $(objects_networkaccess) $(objects_websocket) $(objects_tokenstore) xovi-*.cpp xovi-*.h
