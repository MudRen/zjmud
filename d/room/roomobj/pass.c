// rice.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(YEL "����" NOR, ({ "pass" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", 1);
		set("material", "paper");
	}
	set("long", "һ�����͡�\n");
	setup();
}

