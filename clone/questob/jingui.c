// jingui.c

inherit ITEM;

void create()
{
	set_name("���", ({ "jin gui", "gui" }));
	set_weight(12000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "һֻ˶���ޱȵĴ����ƳɵĹ��񣬹����ޱȡ�\n");
		set("value", 1);
		set("material", "gold");
	}
	setup();
}
