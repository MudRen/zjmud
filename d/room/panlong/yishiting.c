// yishiting.c ������������

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "������");
	set("long", @LONG
��������������˺���Ҫ������������֮���������в������Σ���
�������磬�����й�����������������ͨ����������
LONG );

	set("default_long", "�����ROOM_NAME����ROOM_OWNER����Ҫ����"  /* EXAMPLE */
			    "������������֮���������в������Σ�������" /* EXAMPLE */
			    "���磬�����й�����������������ͨ��������" /* EXAMPLE */
			    "��");				     /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"east"   : __DIR__"yanwu1",
		"west"   : __DIR__"yanwu2",
		"north"  : __DIR__"zhongting",
		"south"  : __DIR__"yingke",
	]));

	set("no_sleep_room", 1);
	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
