// chashi.c �����Ӳ���

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "����");
	set("long", @LONG
����һ������С�ɵĲ��ң������Եþ��¡�������һ�輸��
LONG );

	set("default_long", "��һ������С�ɵĲ��ң������Եþ��¡���" /* EXAMPLE */
			    "����һ�輸��������������������Ů������" /* EXAMPLE */
			    "�������˵ķԸ�(tea)��" );	       /* EXAMPLE */
								     /* EXAMPLE */

	set("exits", ([
		"west"  : __DIR__"yingke",
	]));

//**    set("objects", ([
//**	    "/d/room/roomnpc/teagirl" : 2,
//**    ]));

	create_door("west", "ľ��", "east", DOOR_CLOSED);

	set("no_sleep_room", 1);
	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
