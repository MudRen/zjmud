// Room: /d/pk/turen1.c

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
		"east"  : __DIR__"turen2",
		"south" : __DIR__"turen4",
		"southwest"  : __DIR__"turen3",
	]));
	set("no_learn", 1);

	setup();
}
