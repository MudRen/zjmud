inherit ROOM;

void create()
{
	set("short", "Ĳ����");
	set("long",@LONG
���Ǹ�ɮ�ǵľ���֮��������ȫ����ľ�Ƴɣ�����ľ����ľ�Ͼ���ȥ
Ƥ����Ȼ���ӣ���һ·������̻Ի͵ĵ��ý�Ȼ��ͬ��
LONG
	);
	set("exits", ([
		"north": __DIR__"banruotai",
	]));
	set("no_steal", 1);
	set("objects",([
		CLASS_D("tianlongsi") + "/kurong"   : 1,
		CLASS_D("tianlongsi") + "/benguan"  : 1,
		CLASS_D("tianlongsi") + "/benxiang" : 1,
		CLASS_D("tianlongsi") + "/bencan"   : 1,
		CLASS_D("tianlongsi") + "/benyin"   : 1,
	]));
	setup();
}

void init()
{
	add_action("do_quit", "quit");
	add_action("do_quit", "exit");
}

string long()
{
	if (mapp(query("exits")))
		return query("long");

	return query("long") + "    �������ڽ����ݺᣬ����"
	       "������ɱ����ͣ��\n";
}

int do_quit()
{
	object me;

	me = this_player();
	if (! mapp(query("exits")))
	{
		write("����û�г�·�����޷��뿪��\n");
		return 1;
	}

	return 0;
}
