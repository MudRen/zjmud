#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "����");
    set("long", @LONG
���������������ȣ��Ĵ��ڳ����ġ�
LONG );
    set("exits", ([
	"north" : __DIR__"zhuang9",
	"south" : __DIR__"zhuang5",
    ]));
    set("objects", ([
	"/d/shenlong/npc/dizi": 1,
    ]));
    set("outdoors", "beijing");
    setup();
}
