// plbi.c

inherit ITEM;

void create()
{
	set_name("������", ({ "panlong bi", "bi" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "һ����赣�����ӡ��һ������ȴ����Ȼ�γɣ�����ԡ�\n");
		set("value", 1);
		set("material", "jade");
	}
	setup();
}
