// qingcha.c ���

inherit ITEM;

void init();
void do_eat();

void create()
{
	set_name("���",({"tea", "cha", "qing cha"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���Ȳ裬���Ƶ�ð������������\n");
		set("unit", "��");
		set("value", 1000);
		set("remaining", 2);
		set("drink_supply", 25);
		set("can_drink", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	int heal, recover, jing, e_jing, m_jing;

	recover = 5;

	if (me->query("water") >= me->max_water_capacity())
		return notify_fail("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n");

	set("value", 0);
	me->add("water", (int)query("drink_supply"));
	jing = me->query("jing");
	e_jing = me->query("eff_jing");
	m_jing = me->query("max_jing");

	if (jing < e_jing)
	{
		if (jing + recover >= e_jing)
			me->set("jing", e_jing);
		else
			me->set("jing", jing + recover);
	}

	if (me->is_fighting())
		me->start_busy(2);

	add("remaining", -1);
	if (query("remaining"))
	{
		message_vision("$N������裬������ζ��Ʒ�˼��ڡ�\n" +
			       "һ����ˬ�ĸо�ֱ����Ƣ��$N���þ���ö��ˡ�\n", me);
	} else
	{
		message_vision("$N�����λ�С������ʣ�µ����һ��������\n" +
			       "����������Ƣ��$N���þ���ö��ˡ�\n", me);
		destruct(this_object());
	}
	return 1;
}
