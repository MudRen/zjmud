//Room: qunyuys8.c

inherit ROOM;

void close_path();

void create()
{
	set("short", "Ⱥ��¥����");
	set("long", @LONG
һ�����ҡ����з���һ�Ŵ󴲣����������廨�Ľ�������ͷ������
�������£��������������һ��Ϸˮԧ�죬��ɫ���ã����������
�ϵ���һ�����򣬺�������һ��������һֻ��ױ���ӡ���ǰ����������
����Ь��һ���еģ�һ��Ů�ģ����Ŷ��á���ϸ������ᷢ���������
�Ĵ���Щ���졣
LONG);
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"qunyulou3",
	]));
	set("objects", ([
		__DIR__"npc/dashou" : 4,
	]) );
	set("item_desc", ([
		"bed": "���Ŵ��ƺ������ƿ�(push)��\n",
		"��" : "���Ŵ��ƺ������ƿ�(push)��\n",
		"��" : "���Ŵ��ƺ������ƿ�(push)��\n"
	]) );

	setup();
}
void init()
{
	add_action("do_push", "push");
}

void close_path()
{
	if (! query("exits/enter")) return;
	message("vision","���ֻ��˻�������ס�˰���\n",
		this_object());
	delete("exits/enter");
}

int do_push(string arg)
{
	object me;
	me = this_player();
	if (! arg || arg == "" ) return 0;
	if (arg == "bed" || arg == "��" || arg == "��")
	{
		write("�������ƿ�һ�Ŵ󴲣�");
		if ((int) me->query_str() >= 30)
		{
			write("����¶����һ������\n");
			if (! query("exits/enter"))
			{
     				set("exits/enter", __DIR__"qunyums");
				call_out("close_path", 5);
			}
			return 1;	
		} else
		write("���������ƺ���İ��񣬵�û���ƿ���\n");
		return 1;
	}
	return notify_fail("��Ҫ�ƿ�ʲô��\n");
}

int valid_leave(object me, string dir)
{
	object ob;
	if (dir == "enter" &&
	    objectp(ob = present("da shou", this_object())) &&
	    living(ob))
	{
		message_vision("$N��$n������������Ⱥ��¥��˽��"
		       "�ط������˲�Ҫ��ȥ��\n", ob, me);
		write("��⣡�������ˣ�\n");
		ob->kill_ob(me);
		me->fight_ob(ob);       
		return -1;
	}

	return 1;
}
