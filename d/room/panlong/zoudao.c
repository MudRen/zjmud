// yingke.c ������ӭ����

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "�ߵ�");
	set("long", @LONG
�������������ʹ��ŵ�һ���ߵ������Զ���ľ��ǽ�壬ǰ�����
ӭ������
LONG );

	set("default_long", "�������������ʹ��ŵ�һ���ߵ������Զ���ľ" /* EXAMPLE */
			    "��ǽ�壬ǰ�����ӭ������" );	      /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"north"  : __DIR__"yingke",
		"south"  : __DIR__"qianting",
	]));

	set("gate", "close");

//**    set("objects", ([
//**	    "/d/room/roomnpc/yahuan" : 1,
//**    ]));

	set("no_sleep_room", 1);
	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
	add_action("do_push", "push");
	add_action("do_close", "close");
}

int do_push(string arg)
{
	object me;
	object room;

	if (query("gate") == "open")
		return notify_fail("���ſ����أ��㻹��ʲô��\n");

	me = this_player();
	message_vision("$N���������ƴ��ţ��������š�֨ѽѽ���ı����ƿ��ˡ�\n", me);
    
	room = get_object(__DIR__"qianting");
	message("vision", "���š�֨ѽѽ���ı����ƿ��ˡ�\n", room);
	set("gate", "open");
	set("exits/south", __DIR__"qianting");
	room->set("exits/north", __FILE__);
	room->set("gate", "open");
	remove_call_out("do_close");
	call_out("do_close", 10, 0, 1);
	return 1;
}

int do_close(string arg, int n)
{
	object me;
	object room;

	if (query("gate") == "close")
		return notify_fail("���Ź����أ��㻹�ٹ�һ�飿\n");

	if (! n)
	{
		me = this_player();
		message("vision", me->name() + "����ǰȥ���������ϴ��š�\n",
			this_object());
	} else
	{
		message("vision", "���š�֨ѽѽ���ı��˹����ˡ�\n",
			this_object());
	}

	room = get_object(__DIR__"qianting");
	message("vision", "���š�֨ѽѽ���ı��˹����ˡ�\n", room);
	set("gate", "close");
	delete("exits/south");
	room->set("gate", "close");
	room->delete("exits/north");
	return 1;
}

