// Room: /d/mingjiao/donglu.c

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "����ɽ´");
    set("long", @LONG
������ǧ�����صĶ�´��������ľ�ߴ�ïʢ������ǵأ���
��������������������С·�����ǿ������δ�������߹�����Ϊ
������ɭ��
LONG );
    set("exits", ([
	"south" : __DIR__"shanjiao",
	"north" : __DIR__"youjing",
    ]));

    set("outdoors", "mingjiao");
    setup();
}

int valid_leave(object me, string dir)
{
	if (! userp(me) && dir == "north")
		return 0;

	return ::valid_leave(me, dir);
}
