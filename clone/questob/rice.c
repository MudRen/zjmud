// rice.c
// 1000 �������� 1 ��

inherit COMBINED_ITEM;

void create()
{
	set_name("����", ({ "rice", "da mi", "mi" }));
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ�����ƵĴ��ס�\n");
		set("base_unit", "��");
		set("base_weight", 10000);
		set("no_sell", 1);
		set("unit", "Щ");
	}

	set_amount(1);
	setup();
}

