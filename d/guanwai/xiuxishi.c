// Room: xiuxishi.c ��Ϣ��
// By Marz

inherit ROOM;

void init();
void close_men();
int do_open(string arg);
int do_close(string arg);
int valid_leave(object me, string dir);

void create()
{
	set("short", "��Ϣ��");
	set("long", @LONG
���Ǽ�������᷿�����Ŵ������ţ����ߺܻ谵������������
ֻ���м����һ����ʰ����������Ĵ󴲣����ž�������˯����
LONG );
	set("no_clean_up", 0);
	set("sleep_room", 1);
	set("no_fight", 1);
	setup();
}

void init()
{
	add_action("do_open", "open");
	add_action("do_close", "close");
}

void close_men()
{
	object room;

	if(!( room = find_object(__DIR__"jingxiu")) )
		room = load_object(__DIR__"jingxiu");
	if(objectp(room))
	{
		delete("exits/north");
			message("vision", "��֨֨ѽѽ���Լ������ˡ�\n", this_object());
		room->delete("exits/south");
		message("vision", "��֨֨ѽѽ���Լ������ˡ�\n", room);
	}
}

int do_close(string arg)
{
	object room;

	if(!( room = find_object(__DIR__"jingxiu")) )
		room = load_object(__DIR__"jingxiu");

	if (!arg || (arg != "men" && arg != "door"))
		return notify_fail("��Ҫ��ʲô��\n");

	if (!query("exits/north"))
		return notify_fail("���Ѿ��ǹ��ŵ��ˡ�\n");

	message_vision("$N������ŵİ��Ź����ˡ�\n", this_player());
	delete("exits/north");

	if(objectp(room))
	{
		room->delete("exits/south");
		message("vision", "�ű��˴�����������ˡ�\n", room);
	}

	return 1;
}

int do_open(string arg)
{
	object room;
	object me = this_player();

	if (!arg || (arg != "men" && arg != "door" && arg != "south"))
		return notify_fail("��Ҫ��ʲô��\n");

	if (query("exits/north"))
		return notify_fail("�����Ѿ��ǿ����ˡ�\n");

	if(!( room = find_object(__DIR__"jingxiu")) )
		room = load_object(__DIR__"jingxiu");

	if(objectp(room))
	{
		set("exits/north", __DIR__"jingxiu");
		message_vision("$N������ŵذ��Ŵ򿪡�\n", this_player());
		room->set("exits/south", __FILE__);

		if (me->query_temp("sleeped"))
		{
		message("vision", "֨��һ����"+me->query("name")+"��������ش���
����Ŵ��ˡ�\n",
		room);
		} else
		{
		message("vision", "���һ����"+me->query("name")+"��������Ŵ�
��һ���Ĳ��ͷ���\n",
			 room);
		}

		remove_call_out("close_men");
		call_out("close_men", 10);
	}

	return 1;
}


int valid_leave(object me, string dir)
{
	object room;

	if ( !::valid_leave(me, dir) )
		return 0;

	add_temp("person_inside", -1);
	if (query_temp("person_inside") <= 0)
		delete_temp("person_inside");

	return 1;
}
