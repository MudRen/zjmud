// Room: /d/pk/turen7.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "ɥ����" NOR);
	set("long", @LONG
������ɭ�ֲ������ϵ����ǲ�֫��ʬ���޴����ǰ���ɫ��Ѫ�Ρ�������
������������־��裬��֪��������ͻ�ܳ�һ����Ӱ��
LONG
	);
	set("exits", ([
		"east"  : __DIR__"turen8",
		"southeast" : __DIR__"turen11",
		"north" : __DIR__"turen3",
	]));
	set("no_learn", 1);

	setup();
}
