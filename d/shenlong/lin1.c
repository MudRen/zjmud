// lin1.c

inherit ROOM;

string* npcs = ({
	"/clone/beast/jinshe",
	"/clone/beast/qingshe",
	"/clone/beast/jinshe",
	"/clone/beast/qingshe",
	"/clone/beast/fushe",
});
 
void create()
{
	set("short", "��ľ��");
	set("long",@LONG
����һƬ��ľ�֡���û���뵽����һ���µ��Ͼ���������һƬ��
ľ��(bush)�����ɸе��ǳ��Ծ���ǰ�����û��·�����ܵ������г�
�����Ӳݡ�
LONG);

	set("exits", ([
	    "south" : __DIR__"haitan",
	]));

	set("item_desc", ([
	    "bush" : "��Ƭ��ľ��̫���ˣ�Ҫ���ȥ����ֻ�п���һ��·��(kan)��\n",
	]));

	set("objects", ([
		"/clone/beast/dushe" : 1 + random(2),
		npcs[random(sizeof(npcs))] : 1,
		npcs[random(sizeof(npcs))] : 1,
		npcs[random(sizeof(npcs))] : 1,
	]));

	set("resource/snake", ({ "/clone/beast/jinshe",
				 "/clone/beast/dushe",
				 "/clone/beast/fushe",
				 "/clone/beast/wubushe",
				 "/clone/beast/qingshe", }));

	set("outdoors", "shenlong");
	setup();
}

void init()
{
	add_action("do_kan", "kan");
}

int do_kan(string arg)
{
	object weapon;
	object me;

	if (arg != "bush")
		return notify_fail("��Ҫ��ʲô��\n" ) ;

	me = this_player();
	if (! objectp(weapon = me->query_temp("weapon")))
		return notify_fail("�����������²��аɣ�\n");

	if (weapon->query("skill_type") != "blade" &&
	    weapon->query("skill_type") != "sword")
		return notify_fail(weapon->name() + "Ҳ��������������\n");

	message_vision("$N������У����Ź�ľ�Ծ���һ���ҿ���\n", me);

	if (me->query("neili") > 100)
	{
		set("exits/north", __DIR__"lin2");
		message_vision("$N�۵��������������ڿ���һ��С·��\n", me);
		me->add("neili", -50);
		remove_call_out("close");
		call_out("close", 20);
	} else	
	{
		message_vision("$N�۵�����������Ҳû����һ��·����\n", me);
		me->set("neili", 0);
	}
	return 1;
}

void close()
{
	message("vision", "��ľ�Խ�����£�����������ָֻ���ԭ״��\n",
		this_object());
	delete("exits/north");
}
