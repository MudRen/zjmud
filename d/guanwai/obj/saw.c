// saw.c

#include <ansi.h>

inherit ITEM;

int is_saw() { return 1; }

void create()
{
	set_name("�־�", ({ "gang ju", "ju", "saw" }));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("value", 800);
		set("unit", "��");
		set("material", "steel");
		set("long", "����һ��������ĸ־⣬һ��������ľ��\n");
	}
	setup();
}
