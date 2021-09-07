// mian.c

inherit ITEM;

void create()
{
	set_name("��", ({ "mian" }));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���������ڵ����档\n");
		set("unit", "��");
		set("value", 100);
		set("remaining", 2);
		set("food_supply", 25);
		set("water_supply", 10);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if ((int)me->query("food") >= (int)me->max_food_capacity())
		return notify_fail("���Ѿ���̫���ˣ���Ҳ�Բ����ˡ�\n");

	set("value", 0);
	me->add("food", (int)query("food_supply"));
	if (me->query("water") < (int)me->max_water_capacity()-(int)query("water_supply"))
		me->add("water", (int)query("water_supply"));

	if (me->is_fighting())
		me->start_busy(2);

	add("remaining", -1);
	if (query("remaining"))
		message_vision("$N�������棬���̻��ʵس�������\n", me);
	else 
	{ 
		message_vision("$N������������ʣ�µ����������ˡ�\n"
			       "$N��������һ�ӣ�Ĩ��Ĩ�죬�޵������㣡\n", me);
		destruct(this_object());
	}

	return 1;
}

