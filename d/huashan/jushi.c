// jushi.c

inherit ROOM;
#include <ansi.h>;
void create()
{
	set("short", "����");
	set("long", @LONG
�����������˵����ң��������ڽ������˳ơ���Ů������Ϊ�˼��й�
�������ľ���ȴ�൱���أ�����֮�⣬����(window)���и���ױ̨(tai)��
ǽ�Ϲ���һ�ڱ���(sword)�� ��Ƥ�̿ڿ������Ƿ�����
LONG );
	set("exits", ([ /* sizeof() == 1 */
	    "east" : __DIR__"changlang",
	]));

	set("objects", ([
	    CLASS_D("huashan") + "/yue-wife" :1,
	]));

	set("item_desc", ([
		"window" : "�����������Ͽ�ˡ�������ȥ�������������Ŀѣ��\n",
		"sword"  : "�����ϴ�ǰ������ʱ���ص���Ȫ����\n",
		"tai"    : "����һ�ź�����ױ̨���뿪�ĳ���б���ż����ʻ���\n"
	]));

	setup();
}
void init()
{
	add_action("do_move", "push");
	add_action("do_move", "move");
	add_action("do_pick", "pick");
	add_action("do_pick", "zhai");
}

int do_move(string arg)
{
	object yue;
	object paper, me = this_player();

	if (arg != "tai")
		return 0;

	yue = present("yue wife", environment(me));
	if (! objectp(yue) || ! living(yue))
		return 0;

	if (me->query("family/master_id") != yue->query("id"))
	{
		write("�����˺ȵ�����λ" +
		      RANK_D->query_respect(me) +
		      "���㲻����㷭�˼Ҷ�����\n");
		return 1;
	}

	if (me->query("combat_exp") < 20000)
	{
		write("�����˿��˿��㣬��ü��������úø���"
		      "����ȥ��Ϲ��ʲô����\n");
		return 1;
	}

	if (! query("had_yunu"))
	{
		message_vision("$N������������룬����������һ"
			       "����...��\n", me);
		paper = new("/clone/book/yunu_book");
		paper->move(__FILE__);
		set("had_yunu", 1);
		return 1;
	}

	message_vision("$N������������룬��������ɶ��"
		       "û��...\n", me);
	return 1;
}

int do_pick(string arg)
{
	object sword;
	object yue;
	object me = this_player();

	if (arg != "sword")
		return 0;

	yue = present("yue wife", environment(me));
	if (! objectp(yue) || ! living(yue))
		return 0;

	if (me->query("family/master_id") != yue->query("id"))
	{
		write("�����˺ȵ�����λ" + RANK_D->query_respect(me) +
		      "���㲻����㷭�˼Ҷ�����\n");
		return 1;
	}

	if (me->query("combat_exp") < 20000)
	{
		write("�����˿��˿��㣬��ü��������úø���"
		      "����ȥ���Ҷ�ʲô����\n");
		return 1;
	}

	if (! query("had_sword"))
	{
		message_vision("$N�����ժ�±�������������"
			       "����...\n", me);
		sword = new(__DIR__"obj/longquan");
		sword->move(me, 1);
		set("had_sword", 1);
		return 1;
	}

	message_vision("$N����ȥժ�������ŷ���ֻʣ�����ˣ��������"
		       "������ȡ����...��\n", me);
	return 1;
}

void reset()
{
	::reset();
	delete("had_sword");
	delete("has_yunu");
}
