// mantou.c ��ͷ

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("������ͷ", ({ "mantou" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��������İ�����ͷ��\n");
		set("unit", "��");
		set("value", 10);
		set("food_remaining", 4);
		set("food_supply", 30);
	}
}
