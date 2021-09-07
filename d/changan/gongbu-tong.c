//Room: gongbu-tong.c

#include <ansi.h>
#include <room.h>

inherit PRODUCING_ROOM;

void create ()
{
	set ("short", "����ͭ��");
	set ("long", @LONG
���ǹ�����ұͭ���أ�ר�ż�ѡ����ȫ������������ͭ��ʯ��Ȼ��
�ܻ�ұ����ͭ���������ͭ������ȫ�����أ���Ȼһ����Ҫ��;������
������ҷ��еĻ��ҡ�
LONG);
	set("exits",  ([ //sizeof() == 2
		"south" : __DIR__"gongbu",
	]));

	set("objects", ([
		__DIR__"npc/worker-liu" : 1,
	]));

	set("no_fight", 1);
	set("no_sleep_room", 1);

	set("product/cuprum", ([ "name" : "��ͭ",
				 "rate" : 100,
				 "max"  : 10000,
				 "cost" : ({ "cuprum_ore" }), ]));

	set("product/cuprum_ore", ([ "name" : "ͭ��ʯ",
				     "max"  : 10000,
				     "rate" : 50, ]));

	setup();

	set_heart_beat(120);
}
