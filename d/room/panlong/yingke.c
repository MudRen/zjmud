// yingke.c ������ӭ����

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "ӭ����");	     /* EXAMPLE */
//**    set("short", "ROOM_NAMEӭ����");
	set("long", @LONG
�����������ӵ�����ӭ�Ӱ˷����͵ĵط����󷲿������ݼ����ˣ���
���������ﺮ���𻰣��˾���Ľ֮�顣����ͨ��һ�����ң���������ͬ��
��Ʒ����������֮����
LONG );

	set("default_long", "������ROOM_NAME������ROOM_OWNERӭ�Ӱ˷���" /* EXAMPLE */
			    "�͵ĵط����󷲿������ݼ�ROOM_OWNER���ٲ�"  /* EXAMPLE */
			    "�������ﺮ���𻰣��˾���Ľ֮�顣����ͨ��"  /* EXAMPLE */
			    "һ�����ң���������ͬ����Ʒ����������֮��"  /* EXAMPLE */
			    "��" );				     /* EXAMPLE */
									/* EXAMPLE */

	set("exits", ([
		"north"  : __DIR__"yishiting",
		"south"  : __DIR__"zoudao",
		"east"   : __DIR__"chashi",
	]));

	create_door("east", "ľ��", "west", DOOR_CLOSED);

//**    set("objects", ([
//**	    "/d/room/roomnpc/yahuan" : 2,
//**    ]));

	set("no_sleep_room", 1);
	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
