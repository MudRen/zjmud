// metal.c

inherit COMBINED_ITEM;

void create()
{
	set_name("����", ({ "metalware", "tie qi", "metal" }));
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ�����ƵļҾߡ�\n");
		set("base_unit", "��");
		set("base_weight", 15000);
		set("no_sell", 1);
		set("unit", "Щ");
	}

	set_amount(1);
	setup();
}
