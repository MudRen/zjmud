//bao1.c

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("�������", ({"zhurou baozi", "baozi"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("long", "һ�������硢�����ڵ������������\n");
		set("unit", "��");
		set("value", 25);
		set("food_remaining", 2);
		set("food_supply", 40);
	}
}

