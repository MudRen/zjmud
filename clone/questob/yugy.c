// yugy.c

inherit ITEM;

void create()
{
	set_name("�����", ({ "yu guanyin", "guanyin" }));
	set_weight(900);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "����һ��Ө��͸���������\n");
		set("value", 1);
		set("material", "jade");
	}
	setup();
}
