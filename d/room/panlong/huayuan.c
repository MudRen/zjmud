// hhuayuan.c �����ӻ�԰

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "��԰");
	set("long", @LONG
���������ӵĺ�԰������һЩ��������ĺ�����ɽ�󴨵��滨
��ݣ������ǳ���������ʱ��������ƣ���ˣ��͵�����������Ϣ����
�ͻ������������֣�������ͻ����У����������������ͨ������
���������ţ���������һƬ���֡�
LONG );

	set("default_long", "����ROOM_NAME�ĺ�԰������һЩROOM_OWNER"/* EXAMPLE */
			    "��������ĺ�����ɽ�󴨵��滨��ݣ�������" /* EXAMPLE */
			    "����ROOM_OWNER��ʱ��������ƣ���ˣ��͵���" /* EXAMPLE */
			    "��������Ϣ�����ͻ������������֣�������ͻ" /* EXAMPLE */
			    "����У����������������ͨ�����˾�����" /* EXAMPLE */
			    "���ţ���������һƬ���֡�");	       /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"south"  : __DIR__"houyuan",
		"east"   : __DIR__"zhulin",
		"west"   : __DIR__"jusuo",   /* EXAMPLE */
	]));

	set("outdoors", "OUTDOORS");
	set("sleep_room", 1);
//**    set("room_key", "ROOM_KEY");
	setup();

//**    set("KEY_DOOR", ([
//**	    "exit" : "west",
//**	    "room" : __DIR__"jusuo",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**    ::init();
	add_action("do_sit", "sit");
	this_player()->delete_temp("has_sit");
}

int do_sit(string arg)
{
	object me;

	me = this_player();
	if (me->query_temp("has_sit"))
	{
		message_vision("$N��������ҡ��ҡ���ò���⡣\n", me);
		return 1;
	}

	message_vision("$N���˵ĵط���������������ȥ���ɶ��ˡ�\n", me);
	me->set_temp("has_sit", 1);
	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query_temp("has_sit"))
	{
		message_vision("$N����������վ��������\n", me);
		me->delete_temp("has_sit");
	}

	return ::valid_leave(me, dir);
}
