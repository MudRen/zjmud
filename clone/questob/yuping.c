// yuping.c

inherit ITEM;

void create()
{
	set_name("��ƿ", ({ "yu ping", "ping" }));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һֻ��ƿ�����羫�¡�\n");
		set("value", 1500);
		set("material", "jade");
	}
	setup();
}
