// zhuwu.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long",
		"���������ڲ������漸��û��ʲô���裬������һյ�ŵ�ȼ�ţ�ӳ��"
		"�Աߵ�һ������Ӱ�Ӳ�ס�Ļζ����������Ӳ��õü������أ�����"
		"���������͵������ˡ�");
	set("exits", ([
		"east" : __DIR__"zhuwu",
	]));
	setup();
	(CLASS_D("ultra") + "/shenni")->come_here();
}

string long()
{
	object ob;
	string msg;

	msg = query("long");
	if (! objectp(ob = present("nanhai shenni", this_object())))
		return sort_string(msg, 64, 4);

	if (! ob->is_fighting())
		msg += "һ�����������ȶ�����������ǰ�ŵ���˸����"
		       "��������������";
	else
		msg += "ֻ��һ��������" +
		       (ob->is_fighting(this_player()) ? "��" : "��") +
		       "��ս����������������ҡҡ��׹��";

	return sort_string(msg, 64, 4);
}

