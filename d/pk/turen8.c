// Room: /d/pk/turen8.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "������" NOR);
	set("long", @LONG
������ɭ�ֲ������ϵ����ǲ�֫��ʬ���޴����ǰ���ɫ��Ѫ�Ρ�������
������������־��裬��֪��������ͻ�ܳ�һ����Ӱ��
LONG
	);
	set("exits", ([
		"east"  : __DIR__"turen9",
		"south" : __DIR__"turen11",
		"west"  : __DIR__"turen7",
		"north" : __DIR__"turen4",
	]));
	set("no_learn", 1);

	setup();
}
