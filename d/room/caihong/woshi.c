// woshi.c �ʺ������

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "����");	     /* EXAMPLE */
//**    set("short", "ROOM_NAME����");
	set("long", @LONG
�������˵����ң���ʰ�þ����������ϴ�����һ�Ŵ󴲣�������һ��
���ӣ�����һ����ܡ�����������Ȼ���أ����ǿ���˵��������ȫ������
ȱ��ʲô������
LONG );

	set("default_long", "�������˵����ң���ʰ�þ����������ϴ�����"   /* EXAMPLE */
			    "һ�Ŵ󴲣�������һ�����ӣ�����һ����ܣ�"   /* EXAMPLE */
			    "�������һЩ�顣�������Ӳ��õ÷ǳ����أ�"   /* EXAMPLE */
			    "�����ݻ������������ס�");		   /* EXAMPLE */
									 /* EXAMPLE */
	setup();

	set("exits", ([
		"west" : __DIR__"dating",
	]));

	create_door("west", "ľ��", "east", DOOR_CLOSED);
//**
//**    set("sleep_room", 1);
//**    set("loving_room", 1);
	set("no_fight", 1);
	 set("no_clean_up",1);
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_position", "ROOM_POSITION");
}
int clean_up()
{
	return 0;
}