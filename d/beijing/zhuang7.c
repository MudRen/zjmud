#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "ׯ������");
    set("long", @LONG
����һ�����ã����Ϲ����߰˸���λ������һ�������Ϲ�����һ
�����ˡ�
LONG );
    set("exits", ([
	"east" : __DIR__"zhuang5",
    ]));
    set("objects", ([
	"/d/shenlong/npc/dizi": 1,
    ]));
    set("outdoors", "beijing");
    setup();
}
