// yulong.c

inherit ITEM;

void create()
{
	set_name("�����i", ({ "yulong jue", "jue" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "����һ����ȱ�ڵ��񻷣���������һ������\n");
		set("value", 1);
		set("material", "jade");
	}
	setup();
}
