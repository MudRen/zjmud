// mooncake.c �±�

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("�����±�", ({"cake", "mooncake"}));
	set_weight(150);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��������������±���\n");
		set("unit", "��");
		set("value", 50000);
		set("food_remaining", 3);
		set("food_supply", 100);
	}
}

