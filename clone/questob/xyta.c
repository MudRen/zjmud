// xyta.c

inherit ITEM;

void create()
{
	set_name("������", ({ "xiangya ta", "ta" }));
	set_weight(900);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "�����������߹��Ĺ�Ʒ��������Ʒ��\n");
		set("value", 1);
		set("material", "ivory");
	}
	setup();
}
