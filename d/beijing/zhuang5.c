#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "ׯ������");
    set("long", @LONG
����һ�������ͨ���������䡣���ߵ�������Ů�����֮������
������
LONG );
    set("exits", ([
	"east" : __DIR__"zhuang6",
	"west" : __DIR__"zhuang7",
	"north" : __DIR__"zhuang8",
	"south" : __DIR__"zhuang3",
    ]));
    set("objects", ([
	"/d/shenlong/npc/dizi": 2,
    ]));
    set("outdoors", "beijing");
    setup();
}
