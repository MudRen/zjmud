// xia.c ��Ϻ

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("��Ϻ", ({"kao xia", "xia"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һֻ��ͨͨ��������Ŀ�Ϻ��\n");
		set("unit", "ֻ");
		set("food_remaining", 4);
		set("food_supply", 10);
	}
}
