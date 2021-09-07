// laofang.c

inherit ROOM;

void create()
{
	set("short", "�η�");
	set("long", @LONG
������һ�����������滹��ϡ��һ����(man)���ƺ����������ţ�
��������һ��������
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
	    "south" : __DIR__"didao7",
	]));

	set("item_desc", ([
		"man": "�������ͬϡ��һ�㣬˫Ŀ��ɢ��û��һ����ɡ��������ƺ�ֻʣ��
��һ���ɿݵ����ǣ�Ȼ��ȴ����һ��������������������ţ�Ҳ���
�԰������´�����\n",
	]));
	setup();
}

void init()
{
	add_action("do_move", "move");
	add_action("do_move", "ban");
}

int do_move(string arg)
{
	object me;
	object ob;

	if (arg != "man")
		return notify_fail("��Ҫ��ʲô��\n");

	me = this_player();
	if (me->query_temp("get_xxbook"))
		return notify_fail("��û��Ȥ�������������"
				   "���ˣ�����ֻ�����뿪���\n");

	if (query("get_book"))
	{
		write("������ǰȥ��ȴ�������˵�����������һ��ϸϸ��ȱ�ڣ����ҿ���
ȥǰ������������Ť�������㲻����Щ�Ի󣬲�֪����ʲô���أ�
���ԾͲ����������ˡ�\n");
		return 1;
	}

	write("����ϸ���˿����ͣ���������Ȼ�Ǿ����Ƴɣ�ȴ��һ��ϸϸ��ȱ�ڣ�
���ֶ���Ҳ����ס�ˣ��㲻����ȻʧЦ���漴���Ǹ�����һϢ����
����������������ͻȻ����ԭ�����Ͽ���һЩ�֣��㲻����Щ�ɻ�
���ǽ�������������׼�������о����漴�����룬����������̵�
��Ĩȥ��Ȼ����Ǹ������·ŵ����ϣ�������ᡣ\n");
	me->set_temp("get_xxbook", 1);
	set("get_book", 1);

	ob = new("/clone/book/xx-book");
	ob->move(me, 1);

	return 1;
}
