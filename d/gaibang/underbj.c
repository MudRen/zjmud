// Room: /d/gaibang/underbj.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ֱ߹���");
	set("long", @LONG
���Ǳ�����һ��ƫƧ�ֱߵĹ�������ܶ����˸������
����ؤ������ռ�����ͭ�����ȡ�������ͨ��ؤ�������ͨ����
�����Ȼ�����ż����������ľ�ˣ���֪���Ǵ��Ķ�͵���ġ�
LONG );
	set("exits", ([
		"out"   : "/d/beijing/caroad_e1",
		"south" : __DIR__"bjandao2",
	]));
	set("objects", ([
		"/clone/npc/mu-ren" : 3,
	]));
	set("for_family", "ؤ��");
	setup();
}

