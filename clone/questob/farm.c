// farm.c

inherit COMBINED_ITEM;

void create()
{
	set_name("ũ��", ({ "farm tool", "nong ju", "tool" }));
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ��ľ�Ƶ�ũ�ߡ�\n");
		set("base_unit", "��");
		set("base_weight", 8000);
		set("no_sell", 1);
		set("unit", "��");
	}

	set_amount(1);
	setup();
}
