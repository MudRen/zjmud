// lianwu.c ���������䳡

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "���䳡");
	set("long", @LONG
�˴����������ӵ����䳡�����ڽ������书���򲻿ɻķϡ�
LONG );

	set("default_long", "�˴�����ROOM_NAME�����䳡�����ڽ������书"/* EXAMPLE */
			    "���򲻿ɻķϡ�");			 /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"west" : __DIR__"houyuan",
	]));

//**    set("objects", ([
//**	    "/clone/npc/mu-ren" : 4,
//**    ]));

	set("outdoors", "OUTDOORS");
	set("no_sleep_room", 1);

	setup();
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
