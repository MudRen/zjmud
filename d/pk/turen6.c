// Room: /d/pk/turen6.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "���˳�" NOR);
	set("long", @LONG
������ɭ�ֲ������ϵ����ǲ�֫��ʬ���޴����ǰ���ɫ��Ѫ�Ρ�������
������������־��裬��֪��������ͻ�ܳ�һ����Ӱ��
LONG
	);
	set("exits", ([
		"south" : __DIR__"turen10",
		"west"  : __DIR__"turen5",
		"northwest" : __DIR__"turen2",
	]));
	set("no_learn", 1);

	setup();
}
