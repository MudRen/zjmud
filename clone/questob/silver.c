// silver.c

inherit COMBINED_ITEM;

void create()
{
	set_name("����", ({ "silverware", "yin qi", "silver" }));
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ�����ƵĲ;ߡ�\n");
		set("base_unit", "��");
		set("base_weight", 10000);
		set("no_sell", 1);
		set("unit", "Щ");
	}

	set_amount(1);
	setup();
}
