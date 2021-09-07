// /d/wizard/guest_room.c

#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "��ʦ�����");
	set("long", @LONG
������ʦ��͵ĵط���
LONG );

	set("objects", ([
		"/adm/npc/wizard" : 1,
		"/clone/misc/msgd" : 1,
	]));
	set("exits", ([
//		"up": __DIR__"wizard_room",
		"southeast": "/d/city/wumiao"
	]));

	set("no_fight", 1);

	create_door("southeast", "����", "northwest", DOOR_CLOSED);
	setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "up" && ! wizardp(me))
		return notify_fail("����ֻ����ʦ���ܽ�ȥ��\n");
	return ::valid_leave(me, dir);
}
