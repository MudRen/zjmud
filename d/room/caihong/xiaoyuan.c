// xiaoyuan.c �ʺ��СԺ

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "СԺ");	     /* EXAMPLE */
//**    set("short", "ROOM_NAMEСԺ");
	set("long", @LONG
������һ�����ķ�����Ժ�ӣ�Ժǽ�����ú�ש���ɣ�����ߣ����Ƿ�
����ˬ���䡣Ժ�м��ù�ľ������Ȼ��һ��������Դ�ĸо�������Ժ��
��һ��ľ�š�
LONG );

	set("default_long", "������һ�����ķ�����Ժ�ӣ�Ժǽ������" /* EXAMPLE */
			    "��ש���ɣ�����ߣ����Ƿǳ���ˬ���䡣" /* EXAMPLE */
			    "Ժ�м��ù�ľ������Ȼ��һ��������Դ" /* EXAMPLE */
			    "�ĸо���Ժ��������Լ��ROOM_POSITION"  /* EXAMPLE */
			    "��Ժ�ӵı�����һ��ľ�š�");	   /* EXAMPLE */
								   /* EXAMPLE */
//**    set("room_key", "ROOM_KEY");
	setup();

	set("exits", ([
		"north"  : __DIR__"dating",     /* EXAMPLE */
		"out"    : "/d/room/xiaoyuan",
	]));

	set("outdoors", "OUTDOORS");
	set("no_sleep_room", 1);
	set("valid_startroom", 1);

//**    set("KEY_DOOR", ([
//**	    "exit" : "north",
//**	    "room" : __DIR__"dating",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_OWNER_ID", "ROOM_OWNER_ID");
//**    set("room_id", "ROOM_ID");
//**    set("room_position", "ROOM_POSITION");
}
