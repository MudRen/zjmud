// yuanzi.c

inherit ROOM;

void init();
string look_gate();
int do_open(string);
int do_lock(string);

void create()
{
	set("short", "Ժ��");
	set("long",
	     "����һ����Ժ�ӣ���ɨ��һ����Ⱦ������װ����������񣬴���\n"
	 "���¡������������⡣������һ�䴢���ң�����(door)�ر��š�����\n"
	 "�ǡ�����ɽׯ���Ĵ������ϱ߾��Ǵ����ˡ�\n"
	);

	set("exits", ([
		"northup" : __DIR__"dating",
		"west" : __DIR__"wuqiku",
		"south" : __DIR__"damen",
	]));

	set("outdoors", "baituo");
	set("no_clean_up", 0);

	set("item_desc", ([
	    "door" : (: look_gate :),
	]));

	set_temp("lock",1);

	setup();
}

void init()
{
	add_action("do_open", "open");
	add_action("do_lock", "lock");

}

string look_gate()
{
	if (query_temp("lock") == 0)
		return "���ϵ����������ˡ�\n";

	return "�����ű�����������ס��\n";
}

int do_open(string arg)
{
	object me=this_player(), room;

	if(!arg || arg!="door")
		return notify_fail("��Ҫ��ʲô��\n");

	if( query_temp("lock") == 1 && !present("key", me) )
		return notify_fail("Կ�׶�û�У���ô���ţ�\n");

	if(!( room = find_object(__DIR__"storeroom")) )
		room = load_object(__DIR__"storeroom");

	if(!objectp(room))
		return notify_fail("ERROR:not found 'storeroom.c' \n");

	if(query_temp("lock") == 1 && present("key", me))
	{
		set_temp("lock", 0);
		message_vision("$N��Կ�ײ�����ף�ֻ��������ડ�һ���������ˡ�\n", me);
		message("vision", "���洫��һ������������ֻ��������ડ�һ���������ˡ�\n",
			room);
	}

	message_vision("$N�����ƿ��ţ����˽�ȥ�����ְ�������������\n",me);
	message("vision", "�������˽��������ְ��������ˡ�\n",room);
	me->move(room);
	return 1;
}

int do_lock(string arg)
{
	object me=this_player();
	object room;

	if(!arg ||  arg!="door")
		return notify_fail("��Ҫ��ʲô��\n");
	if( !present("key",me))
		return notify_fail("Կ�׶�û�У���ô���ţ�\n");
	if(!( room = find_object(__DIR__"storeroom")) )
		room = load_object(__DIR__"storeroom");
	if(!objectp(room))
		return notify_fail("ERROR:not found 'storeroom.c' \n");

	if(query_temp("lock") == 1)
		return notify_fail("���Ѿ������ˡ�\n");
	set_temp("lock",1);
	message_vision("$N��Կ�ײ�����ף�ֻ��������ડ�һ�����������ϡ�\n",me);
	message("vision", "���洫��һ����������������ֻ��������ડ�һ�������������ˡ�\n",
		room);

	return 1;
}
