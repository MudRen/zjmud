// longxu.c

inherit ITEM;

void create()
{
	set_name("����", ({ "long xu", "xu" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "һ������ɫ����ë��������׳����˵�����롣\n");
		set("value", 1);
		set("material", "silk");
	}
	setup();
}
