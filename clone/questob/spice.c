// spice.c

inherit COMBINED_ITEM;

void create()
{
	set_name("����", ({ "spice", "xiang liao", "liao" }));
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ�����Ƶ����ϡ�\n");
		set("base_unit", "��");
		set("base_weight", 3000);
		set("no_sell", 1);
		set("unit", "��");
	}

	set_amount(1);
	setup();
}

