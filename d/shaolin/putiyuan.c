// Room: /d/shaolin/putiyuan.c
// by Doing Lu 10/10/2K

// ���⣺ȡ�׽
// �ơ�һ�����ǡ�
// xian һ
// xian ��
// xian �� 3 (��Ϊ���ж�����Ƶ�����)
// xian ��
// Ȼ��look hole���Կ����飬get book from hole���ɡ�

#define BOOK	    "/clone/book/yijinjing"

inherit ROOM;

string look_hole();
string look_jing();
int do_xian(string arg);
int do_get(string arg);
void close_hole();

void create()
{
	set("short", "����Ժ");

	set("long", @LONG
�����������µ�����Ժ�����ϲ���������ͭ�񣬷���֮ǰ��
��һ�����磬������װ��һ�漫���ͭ�������þ��⾻��������
�������Ӱ���˳�����ͭ��(jing)�������ľ侭�ʣ�����ǰ����
��յ�͵ƣ���Ƶĵƹ�֮�£���ϡ�������ǣ���һ����Ϊ������
�λ���Ӱ����¶����磬�������ǹۡ���
LONG );
	set("exits", ([
		"southdown" : __DIR__"guangchang4",
	]));

	set("item_desc", ([
		"ͭ��" : (: look_jing :),
		"jing" : (: look_jing :),
		"hole" : (: look_hole :)
	]));

	set("objects", ([
		CLASS_D("shaolin") + "/xuan-ji" : 1
	]));

	set("valid_startroom", 1);
	set("book_count", 1);
	set("status", 0);
	setup();
}

void init()
{
	add_action("do_get", "get");
	add_action("do_xian", "xian");
}

string look_jing()
{
	object me;

	me = this_player();
	if (me->query("score") < 1000)
		return "�㿴�˰��죬ֻ�����Լ���Ӱ�ӣ�û����ʲô��\n";

	if (me->query("score") < 5000)
		return "����������Եľ����ƺ���Щ��ͬ��\n";

	return "�㷢�������Եľ��ʹ���ͱ𴦲�һ�����ѵ�������(xian)����\n";
}

string look_hole()
{
	string msg;
	object ob;

	if (query("status") != 4)
		return "������ʲô����ץ����ô��\n";

	if (objectp(ob = find_object(BOOK)) &&
	    environment(ob) || query("book_count") < 1)
		return "����ͭ�������һ��С��������տ���Ҳ��ʲôҲû�С�\n"; 

	return "����ͭ�������һ��С�����������һ�����Ƶľɾ���(book)��\n";
}

int do_xian(string arg)
{
	int n;
	int right;
	object ob;

	if (! arg)
		return notify_fail("��Ҫ��ʲô�֣�\n");

	if (objectp(ob = present("xuanji dashi", this_object())) &&
	    living(ob))
		return notify_fail("����һ��ɨ�˹����������"
				   "����Ҫ���㿴�������ĸ��Ҷ���\n");

	if (arg == "��")
		return notify_fail("��Ҫ����һ���磿\n");

	if (sscanf(arg, "%s %d", arg, n) != 2) n = 1;
	if (sizeof(arg) != 2)
		return notify_fail("������û�������ѽ��\n");

	if (strsrch("һ����Ϊ�����λ���Ӱ��¶����統�����ǹ�", arg) == -1)
		return notify_fail("������û�������ѽ��\n");

	if (arg != "��" && n != 1 || n > 4)
		return notify_fail("������û����û��ġ�" +
				   arg + "����ѽ��\n");

	message_vision("$N����һ��" + (n > 1 ? "��" + chinese_number(n) + "��" : "") +
		       "��" + arg + "���֡�\n", this_player());

	right = 0;
	switch (query("status"))
	{
	case 1:
		if (arg == "��") right = 2;
		break;
	case 2:
		if (arg == "��" && n == 3) right = 3;
		break;
	case 3:
		if (arg == "��") right = 4;
		break;
	}

	// ֻҪ�ơ�һ���ͻ�ԭ
	if (arg == "һ") right = 1;
	set("status", right);
	message("vision", "��������������һ���������ƺ�"
			  "��ʲô���ش����ˡ�\n", this_object());
	if (right == 4)
	{
		message_vision("$N����ָ��û���뿪���棬ֻ�����������죬ͭ����"
			       "����������¶��һ��С��(hole)��\n",
			       this_player());
		call_out("close_hole", 8);
	}
	return 1;
}

int do_get(string arg)
{
	object me;
	object ob;

	me = this_player();

	if (! arg)
		return 0;

	if (arg != "book from hole" &&
	    arg != "book in hole" &&
	    arg != "jing from hole" &&
	    arg != "jing in hole")
		return 0;

	if (query("status") != 4)
		return 0;

	// �Ѿ������ر����������Ѿ�������
	if (objectp(ob = find_object(BOOK)) &&
	    environment(ob) || query("book_count") < 1)
	{
		write("������������ͷ�����ﲢû��ʲô��ѽ��\n");
		return 1;
	}

	set("book_count", 0);
	ob = load_object(BOOK);
	if (! objectp(ob))
	{
		write("ϵͳ���ֹ��� - �Ҳ���Ӧ����������ؼ��� :)\n");
		return 1;
	}

	message_vision("$N��С���н��Ǳ�����ȡ�����Ž����ڡ�\n", me);
	ob->move(me, 1);
	CHANNEL_D->do_channel(this_object(), "rumor",
			      me->name(1) + "������������һ���׽��");
	return 1;
}

void close_hole()
{
	set("status", 0);
	message("vision", "һ������������ͭ���ֻ��������¡�\n",
		this_object());
}
