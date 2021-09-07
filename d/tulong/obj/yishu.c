// yishu.c

#include <ansi.h>

inherit ITEM;
inherit F_UNIQUE;

void setup()
{
}

void init()
{
	add_action("do_du", "du");
	add_action("do_du", "study");
}
void create()
{
	set_name(CYN"��������"NOR, ({ "wumu yishu", "book", "yishu"}));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "paper");
		set("no_sell", "����������������\n");
		set("long", "һ�������ľ���˿�������ɹ�ע������Ѫ����׫���ɡ�\n", );
	}
}

int do_du(string arg)
{
	object me = this_player();
	object where = environment(me);
	object ob;
	mapping skill;
	int pxlevel; 

	if (! (arg == "wumu yishu" || arg == "book" || arg == "yishu"))
		return 0;

	if (! arg || ! id(arg))
		return notify_fail("��Ҫ��ʲô��\n");

	if (me->is_busy())
	{
		write("��������æ���ء�\n");
		return 1;
	}

	if (me->is_fighting())
	{
		write("���޷���ս����ר�������ж���֪��\n");
		return 1;
	}

	if (! me->query_skill("literate", 1))
	{
		write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
		return 1;
	}

	if ((me->query("potential") - me->query("learned_points")) < 1)
		return notify_fail("���Ǳ�ܲ��㡣\n");

	message("vision", me->name() + "��ר�ĵ��ж��������顣\n",
		environment(me), me);
	if ((int)me->query("jing") < 200)
	{
		write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
		return 1;
	}

	if ((int)me->query("qi") < 80)
	{
		write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
		return 1;
	}

	pxlevel = me->query_skill("craft-cognize", 1);
	if ((int)me->query_skill("literate", 1) < 200)
	{
		write("���ѧʶ��������޷��������������е����ݡ�\n");
		return 1;
	}

	if (me->query_skill("craft-cognize", 1) > 199)
	{
		write("�㷢�ֶ������������ϵı���Ҫ���Ѿ���Ȼ���أ���ȫ�����ˡ�\n");
		return 1;
	}
	me->receive_damage("qi", 50 + random(30));
	me->receive_damage("jing", 100 + random(100));
	me->add("learned_points", 1);
	me->improve_skill("craft-cognize", 1 + random(me->query("int")/2));
	write("����ϸ�ж����������б����������ĵá�\n");
	return 1;
}

