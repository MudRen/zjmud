
inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", "������ɽ�е�һƬ���֣���ľ�м�����һЩҰ��������"
		    "�����ľ��ס�����⡣һ��޴��ʯͷ�������ԡ�");
	set("exits", ([
		"eastdown" : __DIR__"shanlu2",
	]));
 	set("outdoors", "beijing");
	setup();
	(CLASS_D("ultra") + "/kuihua")->come_here();
}

string long()
{
	object ob;
	string msg;

	msg = query("long");
	if (! objectp(ob = present("kuihua taijian", this_object())))
		return sort_string(msg, 64, 4);

	if (! ob->is_fighting())
		msg += "��һ�������˿���ʯ�ϣ��ճյ�����Զ����һ������"
		       "�ģ�Ҳ��֪���������﾿�����˶�á�";
	else
		msg += "ֻ��һ���������ι��أ����˼������磬������" +
		       (ob->is_fighting(this_player()) ? "��" : "��") +
		       "��ս��";

	return sort_string(msg, 64, 4);
}

