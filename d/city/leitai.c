// Room: /city/leitai.c
// Date: Feb.27 1998 by Java
// Update by Doing

#include <ansi.h>

inherit ROOM;
string look_tiaofu();

void create()
{
	set("short", "��̨");
	set("long", @LONG
����һ�����ɼ�������̨����׳��ʵ��ľ������һƬƽ̨���Ľǵ�֧����
�߹����ĸ�����������Ĺ��ڶ�������ؿ���̨�ϵ�������䡣
��������һ������(tiaofu)������д��һЩ������
LONG );
	set("outdoors", "city");
	set("item_desc", ([
		"tiaofu" : (: look_tiaofu :),
	]));

	set("exits", ([
		"eastdown"  : __DIR__"wudao1",
		"westdown"  : __DIR__"wudao2",
		"southdown" : __DIR__"wudao3",
		"northdown" : __DIR__"wudao4",
	]));

	set("no_roar", 1);

	set("objects", ([
		"/adm/npc/referee": 1,
	]));
	setup();
}

void init()
{
	add_action("do_lclose", "lclose");
	add_action("do_lopen", "lopen");
	add_action("do_invite", "invite");
	add_action("do_kickout", "kickout");
}

string look_tiaofu()
{
	object ob;

	ob = query("close_by");
	if (! objectp(ob))
		return "����̨�������ɿ��ţ�������Ȥ���б�"
		       "�䣬ʧ�������������Ų�����\n\n"
		       "ע����ʦ����" HIY "lopen" NOR "/"
		       HIY "lclose" NOR "����Źر���̨��\n";

	return "����̨���ڱ�" + ob->name(1) + "��ʱ�رգ�"
	       "��֯���䣬�����˵���Ҫ������\n"
	       "��ʦ����" HIY "invite" NOR "��������������̨��"
	       "����̨��ʹ��" HIY "pass" NOR "����\n"
	       "ָ��ĳ����̨���䣬��" HIY "kickout" NOR
	       "��ĳ����̨��\n";
}

int refuse(object ob)
{
	if (! wizardp(ob) && query("close_by"))
		return 1;

	return 0;
}

int do_lclose(string arg)
{
	object me;

	me = this_player();
	if (wiz_level(me) < 3)
		return notify_fail("��û���ʸ�ر���̨��\n");

	if (arg != "here")
		return notify_fail("�����Ҫ�ر���̨��������(lclose here)��\n");

	if (objectp(query("close_by")))
		return notify_fail("�����̨�Ѿ���" +
				   query("close_by")->name(1) +
				   "�ر����ڱ����ˡ�\n");

	set("close_by", me);
	message("vision", HIW "������ʢ�᡿" + me->name(1) +
		"�ر�����̨����ʼ���б���ʢ�ᡣ"NOR"\n",
		all_interactive());
	return 1;
}

int do_lopen(string arg)
{
	object me;

	me = this_player();
	if (wiz_level(me) < 3)
		return notify_fail("��û���ʸ����̨��\n");

	if (! objectp(query("close_by")))
		return notify_fail("�����̨Ŀǰ��û�б��رա�\n");

	if (arg != "here")
		return notify_fail("�����Ҫ����̨��������(lopen here)��\n");

	delete("close_by");
	message("vision", HIW "������ʢ�᡿" + me->name(1) +
		"�����˱��䣬���¿�������̨��"NOR"\n", all_interactive());
	return 1;
}

object *broadcast_to()
{
	if (! objectp(query("close_by")))
		return 0;

	return ({ find_object(__DIR__"wudao1"),
		  find_object(__DIR__"wudao2"),
		  find_object(__DIR__"wudao3"),
		  find_object(__DIR__"wudao4"), });
}

int do_invite(string arg)
{
	object me;
	object ob;

	me = this_player();
	if (! wizardp(me))
		return notify_fail("�㲻����ʦ��û���ʸ������˼�������\n");

	if (! query("close_by"))
		return notify_fail("������̨��û�йرգ������ص�������ˡ�\n");

	if (! arg ||
	    ! objectp(ob = find_player(arg)))
		return notify_fail("������˭������\n");

	if (environment(ob) == this_object())
		return notify_fail("�ţ����ڲ����Ѿ���������ô��\n");

	if (wizardp(ob))
		return notify_fail("�˼��Լ��������Լ�����������������ġ�\n");

	if (! living(ob))
		return notify_fail("�ô����Ū���˼Ұɣ�\n");

	message("vision", HIW + me->name() + "һ����Х��" + ob->name() +
			  "���㻹�����������"NOR"\n", all_interactive());
	message_vision("ֻ��$N����ææ�����˿�ȥ��\n", ob);
	message("vision", "ֻ��һ�����ڣ�" + ob->name() + "Ӧ��Ծ��̨�����ý�֮����\n",
		this_object());
	ob->move(this_object());
	return 1;
}

int do_kickout(string arg)
{
	object me;
	object ob;

	me = this_player();
	if (! wizardp(me))
		return notify_fail("�㲻����ʦ��û���ʸ����˼���ȥ��\n");

	if (! arg ||
	    ! objectp(ob = present(arg, this_object())))
	{
		write("������˭��ȥ��\n");
		return 1;
	}

	if (! ob->is_character())
	{
		write("�㿴����ˣ��ǲ����ǻ��ˣ�\n");
		return 1;
	}

	if (! playerp(ob))
	{
		write("��ֻ���������ȥ��\n");
		return 1;
	}

	if (wiz_level(ob) > wiz_level(me))
	{
		write("���һ�£����ߵ����塣\n");
		return 1;
	}

	message_vision("$N���һ��������һ�Ž�$n�ߵù��๾�����̨ȥ��\n",
		       me, ob);
	if (ob->is_fighting())
		ob->remove_all_enemy(1);
	ob->move(__DIR__"wudao4");
	message("vision", "��̨����һ�����ֹ���ֻ��" + ob->name() +
			  "���๾��Ĺ���������������һ�����һ����ġ�\n",
		environment(ob), ({ ob }));
	return 1;
}
