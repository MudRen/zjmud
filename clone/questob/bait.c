// bait.c

inherit COMBINED_ITEM;

void create()
{
	set_name("���", ({ "bait", "yu er", "er" }));
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ�����ʵ������\n");
		set("base_unit", "��");
		set("base_weight", 4000);
		set("no_sell", 1);
		set("unit", "��");
	}

	set_amount(1);
	setup();
}
