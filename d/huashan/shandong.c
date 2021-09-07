// shandong.c

inherit ROOM;

void create()
{
	set("short", "ɽ��");
	set("long",
		"������һ�������ɽ�������ڵ��ٲ����������������������׾�"
		"���Ե�͸��ˮ������������������첢��������");
	set("exits", ([ /* sizeof() == 2 */
		"out" : __DIR__"shanhongpb",
	]));

	setup();
	(CLASS_D("ultra") + "/dugu")->come_here();
}

string long()
{
	object ob;
	string msg;

	msg = query("long");
	if (! objectp(ob = present("dugu qiubai", this_object())))
		return sort_string(msg, 64, 4);

	if (! ob->is_fighting())
		msg += "ֻ��һ�����ڵ��ϣ����б���һ���񽣣����˸�"
		       "ȥ�Ŀ���Ҳ��֪�����о�ʲô��\n";
	else
		msg += "ֻ��һ��������" +
		       (ob->is_fighting(this_player()) ? "��" : "��") +
		       "��ս����ʩչ������Ȼ��ŵ������������Ƿ�����˼��\n";

	return sort_string(msg, 64, 4);
}

