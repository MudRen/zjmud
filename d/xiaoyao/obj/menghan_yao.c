// poison_dust.c

inherit COMBINED_ITEM;

void create()
{

	set_name("�ɺ�ҩ", ({ "menghan yao", "yao" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",
			"���Ǽ���ͨ���ɺ�ҩ\n" );
		set("unit", "��");
		set("base_value", 700);
		set("base_unit", "��");
		set("base_weight", 30);
		set("can_pour", 1);
		set("can_drug", 1);
		set("poison_type", "slumber_drug");
		set("poison", 20);
		set("no_sell", 1);
	}
	set_amount(1);
}
