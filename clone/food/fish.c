// fish.c ����

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("����", ({"kao yu", "yu"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��������Ŀ��㡣\n");
		set("unit", "��");
		set("food_remaining", 4);
		set("food_supply", 30);
	}
}
