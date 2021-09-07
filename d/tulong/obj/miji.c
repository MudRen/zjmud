// xianglong.c

inherit ITEM;
inherit F_UNIQUE;

#include <ansi.h>

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
	set_name(CYN "����ʮ��������" NOR, ({ "xianglong miji", "book", "miji"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "paper");
		set("no_sell", 1);
		set("no_give", 1);
		set("no_put", 1);
		set("long",
	"�˴�����������д��������ؤ��ľ�ѧ����ʮ���ơ�\n"
	"Ϊ�����������ϵ���ѧ��\n", );
	}
}

int do_du(string arg)
{
	object me = this_player();
	object where = environment(me);
	object ob;
	mapping skill;
	int pxlevel; 

	if (! (arg == "xianglong miji" || arg == "book" || arg == "miji"))
		return 0;

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

	if (! id(arg))
	{
		write("��Ҫ��ʲô��\n");
		return 1;
	}

	if ((int)me->query("str") < 31)
		return notify_fail("���������ӹǻ�������ʮ���ƣ�С��Ū���˸첲��\n");

	if ((int)me->query("con") < 24)
		return notify_fail("���˰ɣ���������ǲ��ã���ǿѧ�ˡ�\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹����޷�ѧϰ����ʮ���ơ�\n");

	if ((int)me->query("max_neili") < 1500)
		return notify_fail("���������ô������ڻ��ͨ����ʮ���ƣ�\n");

	if ((int)me->query_skill("strike", 1) < 30)
		return notify_fail("��Ļ����Ʒ���򲻹����޷�ѧϰ����ʮ���ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("dragon-strike", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ľ���ʮ���ơ�\n");

	if (! me->query_skill("literate", 1))
	{
		write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
		return 1;
	}

	if ((me->query("potential") - me->query("learned_points")) < 10)
		return notify_fail("���Ǳ�ܲ��㡣\n");

	message("vision", me->name() + "��ר�ĵ��ж�����ʮ�������š�\n", environment(me), me);

	if ((int)me->query("neili") < 100)
	{
		write("�������������㣬�޷�ר�������ж���֪��\n");
		return 1;
	}

	if ((int)me->query("jing") < 100)
	{
		write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
	      me->force_me("exert regenerate");
		return 1;
	}

	if ((int)me->query("qi") < 100)
	{
		write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
       	me->force_me("exert recover");
		return 1;
	}

	pxlevel = me->query_skill("dragon-strike", 1);

	if ((int)me->query("combat_exp") < 100000)
	{
		write("���ʵս���鲻�㣬�޷���������ʮ���������е����ݡ�\n");
		return 1;
	}

	if (! me->can_improve_skill("dragon-strike"))
	{
		write("���ʵս���鲻�㣬�޷���������ʮ���������е����ݡ�\n");
		return 1;
	}

	if (me->query_skill("dragon-strike", 1) > 199)
	{
		write("���ж���һ��������Ƿ��������е����ݶ�"
		      "����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
		return 1;
	}
/*
	if (me->query_skill("dragon-strike", 1) < 80)
	{
		write("���ж���һ��������Ƿ��������е�������"
		      "���ޱȣ�û��ѧ���κζ�����\n");
		return 1;
	}
*/
	me->receive_damage("qi", 100);
	me->receive_damage("jing", 100);
	me->add("learned_points", 10);
	me->improve_skill("dragon-strike", (1 + random(me->query("str")))*10);
	write("����ϸ�ж�����ʮ�������ţ������ĵá�\n");
	return 1;
}

