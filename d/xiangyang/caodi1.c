// Room: /d/xiangyang/caodi1.c
inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "�ݵ�");
	set("long", @LONG
������������Ĳݵء��ɹű���������������İ���ȫ��
���ˣ��ɹű��۳���ȥ����Ϊ��������������������š�
LONG );
	set("outdoors", "xiangyang");

	set("exits", ([
		"west"  : __DIR__"northgate2",
	]));
	set("objects", ([
		__DIR__"npc/tuolei"   : 1,
		__DIR__"npc/menggubing" : 2,
	]));
	setup();
}

