// youxiang.c ���������᷿

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "���᷿");
	set("long", @LONG
���������ӵ����᷿���ǿ��˾�ס�ĵط���
LONG );

	set("default_long", "����ROOM_NAME�����᷿���ǿ��˾�ס�ĵط�����" /* EXAMPLE */
			    "Ȼ�����ݻ���ȴҲ���õ÷ǳ����ʡ�һ�Ŵ���" /* EXAMPLE */
			    "��ɾ���û�ж������ƣ�����������ʵ��ʹ" /* EXAMPLE */
			    "���ڹ���ǡ���ô���" );		    /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"east" : __DIR__"zhongting",
	]));

	set("sleep_room", 1);
	set("no_fight", 1);

	create_door("east", "ľ��", "west", DOOR_CLOSED);

	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
