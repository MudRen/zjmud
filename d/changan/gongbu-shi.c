//Room: gongbu-tong.c

#include <ansi.h>
#include <room.h>

inherit PRODUCING_ROOM;

void create ()
{
	set ("short", "����ʯ��");
	set ("long", @LONG
���ǹ������ռ�ʯ�ϣ�ѡ�ϴ�ĥ�ĵط�����ѡ����ȫ������������
ʯ�ϣ����ű��࣬�����ǽ���ʹ�á�
LONG);
	set("exits",  ([ //sizeof() == 2
		"north" : __DIR__"gongbu",
	]));

	set("objects", ([
		__DIR__"npc/worker-wang" : 1,
	]));

	set("no_fight", 1);
	set("no_sleep_room", 1);

	set("product/perfect-stone", ([ "name" : "��ʯ",
					"rate" : 300,
					"max"  : 50000,
					"cost" : ({ "stone" }), ]));

	set("product/stone", ([ "name" : "ʯ��",
				     "max"  : 50000,
				     "rate" : 100, ]));

	setup();

	set_heart_beat(120);
	replace_program(PRODUCING_ROOM);
}
