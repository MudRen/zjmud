// dating.c �ʺ�Ӵ���

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "����");	     /* EXAMPLE */
//**    set("short", "ROOM_NAME����");
	set("long", @LONG
����ǲʺ������ӭ�Ϳ��˵ĵط���������һЩ���Σ����������磬
�����й����������������������Ȼʲô��û��д�����������˵ķ��䡣
LONG );

	set("default_long", "�����ROOM_NAME����ROOM_OWNERӭ�Ϳ�"  /* EXAMPLE */
			    "�˵ĵط���������Щ���Σ�����������"   /* EXAMPLE */
			    "���硣����������ROOM_OWNER�ķ��䣬"   /* EXAMPLE */
			    "��һ��ľ�������š��ϱ��Ǵ��ţ���ȥ"   /* EXAMPLE */
			    "����Ժ�ӡ�");			 /* EXAMPLE */
								   /* EXAMPLE */
	setup();

	set("exits", ([
		"east"   : __DIR__"woshi",
		"north"  : __DIR__"houyuan",
		"south"  : __DIR__"xiaoyuan",   /* EXAMPLE */
	]));

	create_door("east", "ľ��", "west", DOOR_CLOSED);

	set("no_sleep_room", 1);

//**    set("KEY_DOOR", ([
//**	    "exit" : "south",
//**	    "room" : __DIR__"xiaoyuan",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_position", "ROOM_POSITION");
}
