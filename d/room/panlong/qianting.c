// qianting.c ������ǰͥ

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	object ob;

	set("short", "ǰͥ");	     /* EXAMPLE */
//**    set("short", "ROOM_NAMEǰͥ");
	set("long", @LONG
�����ƺ��ǳ�����������ʱ��ʱ����������������ĽС�Ժ�в�����
ľ��Ȼ������֮�ƣ����·ǳ���
LONG );

	set("default_long", "�����ƺ��ǳ�������������ʲô���죬����ʱ��" /* EXAMPLE */
			    "ʱ����������������ĽС�Ժ�в�����ľ��Ȼ��" /* EXAMPLE */
			    "����֮�ƣ����·ǳ���");		     /* EXAMPLE */
									 /* EXAMPLE */

	set("exits", ([
		"south"  : __DIR__"dayuan",
		"east"   : __DIR__"zuowei",
		"west"   : __DIR__"youwei",
	]));

//**    set("objects", ([
//**	    "/d/room/roomnpc/laopu" : 1,
//**    ]));

	set("outdoors", "OUTDOORS");
	set("no_sleep_room", 1);
	set("gate", "close");
	setup();

//**    ob = present("saodi laopu", this_object());
//**    ob->set("coagents", ({
//**	    ([ "startroom" : __DIR__"zuowei",
//**	       "id"	: "shou wei 2" ]),
//**	    ([ "startroom" : __DIR__"zuowei",
//**	       "id"	: "shou wei 1" ]),
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

void init()
{
	add_action("do_push", "push");
	add_action("do_close", "close");
}

int do_push()
{
	object ob;
	object me;
	object room;

	if (query("gate") == "open")
		return notify_fail("���ſ����أ��㻹��ʲô��\n");

	me = this_player();
	ob = present("saodi laopu", this_object());
	if (me && (! ob || ! living(ob) || ob->is_owner_permit(me)))
	{
		message_vision("$N����һ�ƴ��ţ����������š�֨ѽѽ���Ŀ��ˡ�\n",
			       me);
	} else
	if (me && ! ob->is_owner(me))
	{
		message_vision("$N������ס$n���Ϳ������������Բ�����λ" +
			       RANK_D->query_respect(me) + "�������"
			       "�ɣ���\n", ob, me);
		return 1;
	} else
	if (ob && living(ob))
	{
		message_vision("$n��æ����ǰ������$N���������˺α���"
			"�ͣ������ɣ���\n$n����ǰȥ�����������š�֨ѽ"
			"ѽ�����ƿ��ˡ�\n", me, ob);
	} else
	{
		message("vision",  "���š�֨ѽѽ���ı��˴��ˡ�\n",
			this_object());
	}

	room = get_object(__DIR__"zoudao");
	message("vision", "���š�֨ѽѽ���ı����ƿ��ˡ�\n", room);
	set("gate", "open");
	set("exits/north", __DIR__"zoudao");
	room->set("exits/south", __FILE__);
	room->set("gate", "open");
	remove_call_out("do_close");
	call_out("do_close", 10, 0, 1);
	return 1;
}

int do_close(string arg, int n)
{
	object ob;
	object me;
	object room;

	if (query("gate") == "close")
		return notify_fail("���Ź����أ��㻹�ٹ�һ�飿\n");

	me = this_player();
	ob = present("saodi laopu", this_object());
	if (! n && me && (! ob || ! living(ob)))
	{
		message_vision("$N����һ�����ţ����������š�֨ѽѽ���Ĺ����ˡ�\n",
			       me);
	} else
	if (! n && me && ! ob->is_owner(me))
	{
		message_vision("$N����ǰȥ���������ϴ��š�\n", me);
	} else
	if (! n && me && ob->is_owner(me))
	{
		message_vision("$n��æ����ǰ������$N���������˺α�"
			"���ͣ������ɣ���\n$n����ǰȥ���������ϴ��š�\n",
			me, ob);
	} else
	if (ob && living(ob))
	{
		message("vision", ob->name() + "����ǰȥ���������ϴ��š�\n",
			this_object());
	} else
	{
		message("vision", "���š�֨ѽѽ���ı��˹����ˡ�\n",
			this_object());
	}

	room = get_object(__DIR__"zoudao");
	message("vision", "���š�֨ѽѽ���ı��˹����ˡ�\n", room);
	set("gate", "close");
	delete("exits/north");
	room->delete("exits/south");
	room->set("gate", "close");
	return 1;
}

string long()
{
	string msg;
	msg = "    ";
	if (present("lao jiaren"))
		msg += "һ�ϼ��������Ļ�����ɨ�ѣ���ɨ����Ҷ��";

	if (query("gate") != "open")
		msg += "����ȥ����һ�ȴ��Ž����Ĺر��š�";
	else
		msg += "���ų�����ԶԶ��ȥ����Ȼ�ɼ�ӭ������";

	return query("long") + sort_string(msg, 60, 0);
}

int valid_leave(object me, string dir)
{
	object ob;

	ob = present("saodi laopu", this_object());
	if (dir != "north" || ! objectp(ob) || ! living(ob))
		return ::valid_leave(me, dir);

	if (ob->is_owner(me))
	{
		message_vision("$N������$n�������������\n", ob, me);
		return ::valid_leave(me, dir);
	}

	if (ob->is_owner_permit(me))
	{
		message_vision("$N��$n��������Ȼ�����˵����ѣ������޷�����\n",
			       ob, me);
		return ::valid_leave(me, dir);
	}

	message_vision("$N������ס$n������������Ī�룡��\n", ob, me);
	return 0;
}
