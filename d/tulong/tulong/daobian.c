inherit ROOM;

void create()
{
	set("short","����ɽ����");
	set("long",@LONG
����ɽ��Ǯ�����ڵĶ���֮�У��Ǹ�����С����ɽʯ��ᾣ������˾ӡ���
�����˸��ٴ��죬����ʾ�⣬ֻ����������Ͼ�����һͷ��ӥ��˫����չ����
�����䡣�������֮��վ��һ�����ߡ�����ɽ�Ǹ�С����ɽʯ��ľ�޿ɹ�֮����
���Ͻ��и����壬Φ�ɸ��ʣ�ͣ����ʮ���Ҵ󴬣����Ǿ޾����ɳ��һ����
��������
LONG);
	set("exits",([
		"southdown":__DIR__"boat2",
		"east":__DIR__"gukou",
	    ]));

	set("objects",([
		 __DIR__"npc/jiaozhong1": 2,
		 __DIR__"npc/jiaozhong2": 2,
		 __DIR__"npc/bai": 1,
	    ]));

setup();
}

int valid_leave(object me,string dir)
{
	object ob;
	//if (!me->query_temp("dao") && dir=="east")
	//return notify_fail("һ���˻᳡��������֮�����������������ǵĴ�(break boat)�Է����⡣\n");

	//if (me->query_temp("dao") && dir=="east" && ob=present("bai guishou", this_object()))
	if (dir=="east" && ob=present("bai guishou", this_object()))
	{
	ob->ccommand("tnnd"+me->query("id"));
	ob->ccommand("slap3"+me->query("id"));
	message_vision("$N�ȵ���$n��ȥ���ɣ�\n",ob,me);
	ob->kill_ob(me);
	ob=present("jiao zhong", this_object());
	if (objectp(ob)) ob->kill_ob(me);
	ob=present("jiao zhong 2", this_object());
	if (objectp(ob)) ob->kill_ob(me);
	ob=present("jiao zhong 3", this_object());
	if (objectp(ob)) ob->kill_ob(me);
	ob=present("jiao zhong 4", this_object());
	if (objectp(ob)) ob->kill_ob(me);
	return notify_fail("�򶫵�·���׹�����ס�ˡ�\n"); }
	return 1;
}

