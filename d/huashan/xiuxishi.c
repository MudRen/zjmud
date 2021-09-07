// Room: xiuxishi.c

inherit ROOM;

void init();
void close_men();
int do_open(string);
int do_close(string);

void create()
{
	set("short", "��ɽС��");
	set("long", @LONG
���Ǽ�������᷿�����Ŵ������ţ����ߺܻ谵������������
ֻ���м����һ����ʰ����������Ĵ󴲣����ž�������˯����
LONG );

	set("sleep_room", 1);
	set("no_fight", 1);

	setup();
}

void init()
{
	object me = this_player();
	add_action("do_open", "open");
	add_action("do_close", "close");

	if (me->query_temp("xunshan")) me->set_temp("xunshan/yunu", 1);
}

void close_men()
{
	object room;

	if(!( room = find_object(__DIR__"xiaolu2")) )
		room = load_object(__DIR__"xiaolu2");

	if(objectp(room) && query("exits/west"))
	{
		delete("exits/west");
		message("vision", "������ѽѽ���Լ������ˡ�\n", this_object());
		room->delete("exits/east");
		message("vision", "������ѽѽ���Լ������ˡ�\n", room);
	}
}

int do_close(string arg)
{
	object room;

	if (!arg || (arg != "men" && arg != "door"))
		return notify_fail("��Ҫ��ʲô��\n");

	if (!query("exits/west"))
		return notify_fail("���Ѿ��ǹ��ŵ��ˡ�\n");

	message_vision("$Nһ���֣����Ź����ˡ�\n", this_player());

	if(!( room = find_object(__DIR__"xiaolu2")) )
		room = load_object(__DIR__"xiaolu2");

	if(objectp(room))
	{
		message("vision", "�ű��˴���������ˡ�\n", room);
		delete("exits/west");
		room->delete("exits/east");
	}

	return 1;
}

int do_open(string arg)
{
	object room;
	object me = this_player();

	if (!arg || (arg != "men" && arg != "door" && arg != "west"))
		return notify_fail("��Ҫ��ʲô��\n");

	if (query("exits/west"))
		return notify_fail("�����Ѿ��ǿ����ˡ�\n");

	if(!( room = find_object(__DIR__"xiaolu2")) )
		room = load_object(__DIR__"xiaolu2");
	if(objectp(room))
	{
		set("exits/west", __DIR__"xiaolu2");
		message_vision("$N������ŵذ��Ŵ򿪡�\n", this_player());
		room->set("exits/east", __FILE__);
		
		if (me->query_temp("sleeped"))
		{
		message("vision", "֨��һ����"+me->query("name") +
				  "��������ش�������Ŵ��ˡ�\n",
		room);
		} else 
		{
		message("vision", "���һ����"+me->query("name") +
				  "��������Ŵ򿪣�һ���Ĳ��ͷ���\n",
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
	if ((int)query_temp("person_inside") <= 0)
		delete_temp("person_inside");	
	
	return 1;
}
