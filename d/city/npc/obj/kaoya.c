// kaoya.c ��Ѽ

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("��Ѽ", ({"kaoya", "ya"}));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һֻ�ʵ����͵ı�����Ѽ��\n");
		set("unit", "ֻ");
		set("value", 1500);
		set("food_remaining", 1000);
		set("food_supply", 100);
	}
}