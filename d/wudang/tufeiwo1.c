// tufeiwo1.c ����С·
inherit ROOM;

void create()
{
	set("short", "����С·");
	set("long", @LONG
������һ��Ƨ��������С·�ϣ���������ɭɭ�����֡�ֻ������ǰ�󣬵���
��������ǵص������֡���ʮ�ɸߵĴ���������һ�飬��ʵ��֦Ҷ��һ�����ɡ
��������գ��������ڵ�˿��Ҳ�ޡ���˵���ﾭ�������˳�û�����ɾ���������
�и�Сɽ��(dong)��
LONG );
	set("outdoors", "wudang");
	set("no_sleep_room", 1);
	set("exits", ([
		"south"     : __DIR__"tufeiwo2",
		"northdown" : __DIR__"wdroad10",
	]));
	set("item_desc", ([
		"��ɽ����" : "����һ�������С�������治֪����Щʲô�Ź֡�\n"
		ZJOBACTS2"�궴:enter dong\n",
	]));
	set("objects", ([
		__DIR__"npc/tufei2" : 2
	]));
	setup();
}

void init()
{
	add_action("do_enter", "enter");
	add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
	object me;

	me = this_player();

	if (! arg || arg == "")
		return 0;

	if (arg == "dong")
	{
		if (me->is_busy())
			return notify_fail("������æ���ء�\n");

		if (me->query("family/family_name") == "ؤ��")
		{
			message("vision",
				me->name() + "����ؤ�����ǹ���һ�������������˽�ȥ��\n",
				environment(me), ({me}) );
			me->move("/d/gaibang/underwd");
			message("vision",
				me->name() + "�Ӷ������˽�����\n",
				environment(me), ({me}) );
			return 1;
		} else 
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n");
	}
}
