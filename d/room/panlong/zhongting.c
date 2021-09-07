// zhongting.c ��������ͥ

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
//**    object ob;

	set("short", "��ͥ");	     /* EXAMPLE */
//**    set("short", "ROOM_NAME��ͥ");
	set("long", @LONG
����������֮������ͥ�����Ա��ǿ��˾�ס���᷿������ͨ����
��԰�����˾�����ǰ��������������һֱͨ����Ժ��
LONG );

	set("default_long", "����ROOM_NAME֮������ͥ�����Ա��ǿ��˾�"  /* EXAMPLE */
			    "ס���᷿������ͨ����԰�����˾�����ǰ��" /* EXAMPLE */
			    "������������һֱͨ����Ժ��");	     /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"north"  : __DIR__"houyuan",
		"south"  : __DIR__"yishiting",
		"east"   : __DIR__"zuoxiang",
		"west"   : __DIR__"youxiang",
	]));

	set("outdoors", "OUTDOORS");

//**    set("objects", ([
//**	    "/d/room/roomnpc/shouwei" : 1,
//**    ]));

	create_door("east", "ľ��", "west", DOOR_CLOSED);
	create_door("west", "ľ��", "east", DOOR_CLOSED);

	set("no_sleep_room", 1);
	setup();

//**    ob = present("shou wei", this_object());
//**    ob->set("coagents", ({
//**	    ([ "startroom" : __DIR__"zuowei",
//**	       "id"	: "shou wei 1" ]),
//**	    ([ "startroom" : __DIR__"zuowei",
//**	       "id"	: "shou wei 2" ]),
//**	    ([ "startroom" : __DIR__"youwei",
//**	       "id"	: "shou wei 2" ]),
//**	    ([ "startroom" : __DIR__"youwei",
//**	       "id"	: "shou wei 1" ]),
//**    }));

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

int valid_leave(object me, string dir)
{
	object ob;

	ob = present("shou wei", this_object());
	if (dir != "north" || ! objectp(ob) || ! living(ob))
		return ::valid_leave(me, dir);

	if (ob->is_owner(me))
	{
		message_vision("$N������$n�������������\n", ob, me);
		return ::valid_leave(me, dir);
	}

	if (present(query("room_owner_id") + " pass", me))
	{
		message_vision("$N��$n��������Ȼ�����˵����ͣ�������ɡ���\n",
			       ob, me);
		return ::valid_leave(me, dir);
	}

	message_vision("$N������ס$n���������Բ���û��" +
		       query("room_owner") + "�����ͣ��������Դ��룡��\n", ob, me);
	return 0;
}
