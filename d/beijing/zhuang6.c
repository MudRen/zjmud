#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "ׯ������");
    set("long", @LONG
����һ�����ã����Ϲ����߰˸���λ������һ�������Ϲ�����һ
�����ˡ�һ�����紵��������ͻȻ���ˡ�
LONG );
    set("exits", ([
	"west" : __DIR__"zhuang5",
    ]));
    set("objects", ([
	"/d/shenlong/npc/dizi": 1,
    ]));
    set("outdoors", "beijing");
    setup();
}
