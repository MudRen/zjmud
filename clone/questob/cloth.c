// cloth.c

inherit COMBINED_ITEM;

void create()
{
	set_name("����", ({ "cloth", "bu liao", "bu" }));
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һƥ˿֯�Ĳ��ϡ�\n");
		set("base_unit", "ƥ");
		set("base_weight", 5000);
		set("no_sell", 1);
		set("unit", "��");
	}

	set_amount(1);
	setup();
}

