// wood.c

inherit COMBINED_ITEM;

void create()
{
	set_name("ľ��", ({ "woodware", "mu qi", "wood" }));
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ��ľ�ƵļҾߡ�\n");
		set("base_unit", "��");
		set("base_weight", 8000);
		set("no_sell", 1);
		set("unit", "Щ");
	}

	set_amount(1);
	setup();
}
