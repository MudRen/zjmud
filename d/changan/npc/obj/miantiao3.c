//miantiao3.c

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("�Ź���", ({"paigu mian", "miantiao", "mian"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "һ���������ڵ�������\n");
		set("unit", "��");
		set("value", 200);
		set("food_remaining", 5);
		set("food_supply", 35);
	}
}

