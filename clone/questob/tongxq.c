// tongxq.c

inherit ITEM;

void create()
{
	set_name("ͭϲȵ", ({ "tong xique", "xique" }));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һ��ͭϲȵ��������ż������⡣\n");
		set("value", 5000);
		set("material", "copper");
	}
	setup();
}
