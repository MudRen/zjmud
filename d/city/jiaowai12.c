// Room: /d/city/jiaowai12.c
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
	"south" : __DIR__"jiaowai10",
	"west"  : __DIR__"jiaowai13",
    ]));
    set("objects", ([
	"/clone/beast/dushe" : 2,
	__DIR__"obj/shuzhi": 1,
    ]));

    set("resource/snake", ({
	 "/clone/beast/jinshe",
	 "/clone/beast/dushe" }));

    setup();
}