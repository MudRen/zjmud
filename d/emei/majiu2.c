//Room: majiu2.c ���

#include <room.h>
inherit TRANS_ROOM;

void create()
{
	set("short","���");
	set("long",@LONG
���ǲ���ߵ���ǣ����깩Ӧ���ʲ��ϡ���˵�˵���紾�ӣ�����ǻ��
��ǣ����Ǻ����տ���������ι�����㣬��ϴˢ�ø�Ǭ������һֱ�ź򵽿���
��·������жѷ������Ѳ��ϣ�������һ����ۡ�
    ��������µ���ľ���϶���һ����ľ�ơ�
LONG);
	set("outdoors", "emei");
	set("no_fight", 1);
	set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,

	]));
	set("exits",([ /* sizeof() == 1 */
		"south"    : __DIR__"huayanding",
	]));
	setup();
	replace_program(TRANS_ROOM);
}
