// Room: nanyan3.c ���ҹ��Թ�
// Oct. 6 1997

#include <ansi.h>
#include <room.h>

inherit ROOM;
void create()
{
	object ob1,ob2;
	set("short", "�����Թ�");
	set("long", @LONG
���������ҹ����������У��߹ҵ���ֵ������յ�����͸��������Χ��
����ҹ�����������˸�ķ����⣬��ʲôҲ������������ֻ����һ���ˡ���
���»���������ȫ��䱸��û�����ܰ����㡣
LONG
	);
	set("exits", ([
	    "east"      : __DIR__"nanyan1",
	    "south"     : __DIR__"nanyan2",
	    "west"      : __DIR__"nanyan3",
	    "north"     : __DIR__"nanyan4",
	    "southeast" : __DIR__"nanyan1",
	    "southwest" : __DIR__"nanyan2",
	    "northeast" : __DIR__"nanyan0",
	    "northwest" : __DIR__"nanyan4",
	]));
	set("objects", ([
		__DIR__"obj/table" : 1,
		"/clone/misc/corpse" : 1,
	]) );
	setup();
}
