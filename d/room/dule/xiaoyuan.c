// xiaoyuan.c ���־�СԺ

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "СԺ");	     /* EXAMPLE */
//**    set("short", "ROOM_NAMEСԺ");
	set("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һЩ��
��ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡�
LONG );

//**    set("room_key", "ROOM_KEY");
	setup();

	set("exits", ([
		"north"  : __DIR__"dulewu",     /* EXAMPLE */
		"out"    : "/d/room/xiaoyuan",
	]));

	set("outdoors", "OUTDOORS");
	set("no_sleep_room", 1);
	set("valid_startroom", 1);

//**    set("KEY_DOOR", ([
//**	    "exit" : "north",
//**	    "room" : __DIR__"dulewu",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_position", "ROOM_POSITION");
}
