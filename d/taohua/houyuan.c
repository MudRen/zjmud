// /d/taohua/houyuan.c

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��Ժ");
	set("long", @LONG
����ɽׯ�ĺ�Ժ��Ժ�����һ�����Ψһһ��ɽ�壺��ָ�塣�����һ�ɽׯ
��ɽ������������ɡ��ϱ�������¶��С�����һ����ĵ��������������ǳ�æ
µ��������������ʪ������һЩ���ӱ������ס����˶��С�
LONG );
	set("outdoors", "taohua");
	set("exits", ([
		"north" :__DIR__"dating",
		"west"  :__DIR__"xiaowu",
		"east"  :__DIR__"siguoshi" ,
		"southeast" : __DIR__"wuchang1",
		"southwest" : __DIR__"wuchang2",
		"south" : __DIR__"wuchang3",
	]));

	set("objects", ([
		__DIR__"obj/shizi" : 1,
	]));
	setup();
}
