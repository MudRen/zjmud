// Room: /d/city/jiaowai5.c
// Jan. 8.1998 by Venus
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "����");
    set("long", @LONG
���ݽ����ï�����֣���ɭ�ɲ���̧ͷ�������ա�����Ҳ
�����������������ĵط��������߳��ε����
LONG );
    set("exits", ([
	"east"  : __DIR__"jiaowai4",
	"west"  : __DIR__"jiaowai6",
    ]));
    set("objects", ([
	__DIR__"obj/shuzhi": 2,
	"/clone/beast/dushe" : 1,
    ]));

    set("resource/snake", ({
	 "/clone/beast/jinshe",
	 "/clone/beast/dushe" }));

    setup();
}
