// mian.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("�ִ���", ({ "wan" }));
	set_weight(900);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ������Ҥ���ƵĻ��ߴ��롣\n");
		set("unit", "��");
		set("value", 50);
		set("food_supply", 10);
		set("water_supply", 25);
		set("max_liquid", 10);
		set("only_do_effect", 1);
	}

	set("liquid", ([
		"type": "water",
		"name": "����",
		"remaining": 6,
		"drunk_supply": 10,
	]));

	setup();
}

int do_effect(object me)
{
	if (! (int)query("liquid/remaining") ||
	    query("liquid/name") != "����")
		return 0;

	if (me->query("food") >= me->max_food_capacity())
		return notify_fail("���Ѿ���̫���ˣ���Ҳ�Բ����ˡ�\n");

	me->add("food", query("food_supply"));
	if (me->query("water") < me->max_water_capacity())
		me->add("water", query("water_supply"));

	add("liquid/remaining", -1);
	if (query("liquid/remaining"))
   		 message_vision("$N�����������ͺ��˼����ࡣ\n", me);
	else
   		 message_vision("$N������������ʣ�µ���ȵøɸɾ�����\n", me);

	return 1;
}
