//      zoulang2.c ����
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������ѩɽ���ڵ����ȡ������е��İ����컨������
һЩ��֪��ȷ�к���ĵ�̣�ǽ�������Ǻ�ͨ�׵ķ𾭹�
�±ڻ��ˡ����ϵ��ż���󺣵�������
LONG );
	set("exits", ([
		"south"   : __DIR__"cedian2",
		"east"   : __DIR__"dating",
		"northeast" : __DIR__"zoulang3",
	]));
	set("item_desc", ([
		"����̡�" : "һЩ��֪������ĵ�̣�����۲�(kan)�·�������Щ��ͬ��\n"
		ZJOBACTS2"�۲�:kan\n",
	]));
	setup();
}

void init()
{
	add_action("do_watch", "kan");
}

int do_watch()
{
	object ob = this_player();
	int lvl = ob->query_skill("mingwang-jian", 1);

	if ((int)ob->query_skill("force") < 100)
	{
		write("����ڹ���򲻹����޷��������̵���ʲô��\n");
		return 1;
	}

	if ((int)ob->query_skill("mingwang-jian", 1) > 135)
	{
		write("��Ĳ�����������Ϊ�Ѿ���Խ���������ˡ�\n");
		return 1;
	}

	if ((int)ob->query_skill("mingwang-jian", 1) < 50)
	{
		write("��Ĳ�����������Ϊ̫ǳ���޷����������̡�\n");
		return 1;
	}

	if (! ob->can_improve_skill("mingwang-jian"))
	{
		write("���ʵս���鲻�㣬�޷�����������ݡ�\n");
		return 1;
	}

	if (ob->query("jing") < 40)
	{
		 write("��̫���ˣ������޷�����������ݡ�\n");
		 return 1;
	}

	message_vision("$N����ű���ͼ����Ħ���ã���������\n",ob);
	ob->improve_skill("mingwang-jian", 1 + random(ob->query("int")));
	ob->receive_damage("jing", 20 + random(20));
	return 1;
}
