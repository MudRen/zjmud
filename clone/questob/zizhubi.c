// zizhubi.c

inherit ITEM;

void create()
{
	set_name("�����", ({ "zizhu bi", "bi" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "֧");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "һ֧���������ıʣ����Ϻ�����\n");
		set("value", 1);
		set("material", "bamboo");
	}
	setup();
}
