// jinyd.c

inherit ITEM;

void create()
{
	set_name("������", ({ "jin yaodai", "yaodai" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "�����������ص������޷���������������һ������\n");
		set("value", 1);
		set("material", "gold");
	}
	setup();
}
