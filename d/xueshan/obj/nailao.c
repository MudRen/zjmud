// nailao.c ����

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("����", ({ "nai lao", "nailao" }));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ�����ɫ�����ҡ�\n");
		set("unit", "��");
		set("value", 150);
		set("food_remaining", 5);
		set("food_supply", 60);
	}
}

