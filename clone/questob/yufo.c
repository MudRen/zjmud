// yufo.c

inherit ITEM;

void create()
{
	set_name("���", ({ "yu fo", "fo" }));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "����һ��Ц���е����շ�\n");
		set("value", 1);
		set("material", "jade");
	}
	setup();
}
