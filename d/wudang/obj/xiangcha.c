// xiangcha.c ���
// By Marz 03/29/96

inherit ITEM;

void create()
{
	set_name("���",({"tea", "cha", "xiang cha"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���Ȳ裬���Ƶ�ð������������\n");
		set("unit", "��");
		set("value", 0);
		set("no_sell", 1);
		set("remaining", 2);
		set("drink_supply", 25);
		set("only_do_effect", 1);
		set("can_drink", 1);
	}
	
	setup();
}

int do_effect(object me)
{
	int heal, recover, jing, e_jing, m_jing;
	recover = 5;

	if ((int)me->query("water") >= (int)me->max_water_capacity())
		return notify_fail("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n");

	set("value", 0);
	me->add("water", (int)query("drink_supply"));
	jing = (int)this_player()->query("jing");
	e_jing = (int)this_player()->query("eff_jing");
	m_jing = (int)this_player()->query("max_jing");

	if (me->is_fighting())
		me->start_busy(2);
	add("remaining", -1);
	if (query("remaining"))
	{
		message_vision("$N������裬������ζ��Ʒ�˼��ڡ�\n"+
			       "һ������ֱ����Ƣ��$N���þ���ö��ˡ�\n", me);
	} else 
	{ 
		message_vision("$N�����С������ʣ�µ����һ��������\n" +
			       "һ������ֱ����Ƣ��$N���þ���ö��ˡ�\n", me);
		destruct(this_object());
	}
	return 1;
}

