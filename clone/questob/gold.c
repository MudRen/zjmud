// gold.c

inherit COMBINED_ITEM;

void create()
{
	set_name("����", ({ "goldware", "jin qi", "gold" }));
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ�����Ƶ����ߡ�\n");
		set("base_unit", "��");
		set("base_weight", 12000);
		set("no_sell", 1);
		set("unit", "Щ");
	}

	set_amount(1);
	setup();
}
