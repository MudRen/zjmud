// bsdao.c

inherit ITEM;

void create()
{
	set_name("��ʯ��", ({ "baoshi dao", "dao" }));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "һ��������ʯ��С�����������Ʒ��\n");
		set("value", 1);
		set("material", "jade");
	}
	setup();
}
