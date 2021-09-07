inherit ROOM;

void create()
{
	set("short", "��Ů��");
	set("long", @LONG
��Ů���﹩��ĵ�������λ��Ů������಻ͬ��˵�����������ܿ���
��ֻһ������ʯ�����д�ʯ����һ�����ݣ�������ˮ��̣�������Ů
��ϴ���裬��ˮ���겻�ɡ���Ů�������һ��ɽ��(cliff)�����Ƕ��͡�
LONG
	);
	set("outdoors", "huashan");
	set("exits", ([
		"west" : __DIR__"yunu",
	]));
	set("item_desc", ([
		"cliff" : "��Ů���µ�ɽ�º��Ƕ��ͣ��ƺ�������һ��С·��\n",
	]));

	set("resource/water", 1);
	setup();
}
void init()
{
	add_action("do_jump", "jump");
}

int do_jump(string arg)
{
	object me = this_player();
	int n = me->query("dex");

	if (!arg || arg != "cliff")
	{
		write("���������������\n");
		return 1;
	}
	message_vision("$N������һ������������ɽ����ȥ��\n", me);
	if (n < 30)
	{
		message("vision", me->name() + "�ҽ���һ����������ɽ�¡�\n", me);
		me->move(__DIR__"kuihua_2");
		message("vision", me->name() + "һ���ҽУ��������ɽ��������ˤ��������\n", me);
		me->unconcious(); 
	}
	else
	{
		message("vision", me->name() + "���ý������������µס�\n", me);
		me->move(__DIR__"kuihua_2");
		message("vision", me->name() + "�������ɽ�����������������\n", me);
	}
	return 1;
}
