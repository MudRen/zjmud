// jusuo.c �����Ӿ���

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "����");
	set("long", @LONG
�����������������Ϣ������ĵط���¥�Ͼ������˵����ң�������
���鷿��
LONG );

	set("default_long", "�����ROOM_NAME����ROOM_OWNER��Ϣ�������" /* EXAMPLE */
			    "�ط���¥�Ͼ������˵����ң����������鷿��");/* EXAMPLE */
									/* EXAMPLE */

	set("exits", ([
		"up"   : __DIR__"woshi",
		"west" : __DIR__"shufang",
		"east" : __DIR__"huayuan",  /* EXAMPLE */
	]));

	set("no_sleep_room", 1);
	setup();

//**    set("KEY_DOOR", ([
//**	    "exit" : "east",
//**	    "room" : __DIR__"huayuan",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
