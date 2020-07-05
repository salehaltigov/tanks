#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 30;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина 


sf::String TileMap[HEIGHT_MAP] = {
	"     00000000000000000000000000000000000",
	"       000          f    s             0",
	"       000     0    00000000000000     0",
	" 00 s  000    h0    0            0     0",
	" 00    000000000    0       h    0     0",
	" 00                 f            0     0",
	" 0000000000000000   f            0     0",
	" 00        0        s            0     0",
	" 00 hhhhhh 0        f0000000000000     0",
	" 00        0        f0          h      0",
	" 00        0        f0          fffffff0",
	"           0  fffffff0          fffffff0",
	" 00ffffffff0        f0          f0000000",
	" 00ffffffff0     h  f0          f0     0",
	" 00ffffffff0         0          f0     0",
	" 00ffffffff0ffffffff 0     s    f0     0",
	" 00ffffffff0         0          f0     0",
	" 00ffffffff0         0          f0     0",
	" 00ffffffff0    fff  0  fffffffff0     0",
	" 00ffffffff0                    f0     0",
	" 00ffffffff0 s                  f0     0",
	" 00ffffffff0                    f0     0",
	" 00ffffffff00000000000000000000000     0",
	" 00fffffffffffffffffffffffffffffff     0",
	" 00fffffffffffffffffffffffffffffff     0",
	" 00ffffffffffffffffffffffffff   00000000",
	" 00ffffffffffffffffffffffffff   0s     0",//point
	" 00ffffffffffffffffffffffffff   0f     0",//enemy
	" 00ffffffffffffffffffffffffff   0h     0",//health
	" 000000000000000000000000000000000000000",
};