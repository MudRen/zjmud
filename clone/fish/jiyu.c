// jiyu.c ����

inherit ITEM;

#include <ansi.h>
#include "fish.h";

void create()
{
	set_name("����", ({ "ji yu", "jiyu" }) );
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "һ����������Ĵ����㡣\n");
		set("unit", "��");
	}

	setup();
}
