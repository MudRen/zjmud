// senlin7.c
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "��ľ԰");
	set("long", @LONG
������÷ׯ�İ�ľ԰����һ�ߵ���������ߵ���һ�������޾�
��Сɭ��һ��������������������������������кܶ�в�������
�ֵ�������ľ�����������У�ֻ�����Ƭ���־��������һ�飬����
��ȥ�źá�
LONG
	);

	set("exits", ([
		"east" : __DIR__"senlin"+(random(8)+1),
		"south" : __DIR__"senlin"+(random(8)+1),
		"west" : __DIR__"senlin"+(random(8)+1),
		"north" : __DIR__"senlin"+(random(8)+1),
	]));
	set("outdoors", "meizhuang");
	setup();
}

