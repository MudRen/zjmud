// tiegy.c

inherit ITEM;

void create()
{
	set_name("������", ({ "tie guanyin", "guanyin" }));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һ�����ƹ������񣬺�����ģ�����������\n");
		set("value", 1000);
		set("material", "iron");
	}
	setup();
}
