// caoyu.c ����

inherit ITEM;

#include <ansi.h>
#include "fish.h"

void create()
{
	set_name("����", ({ "caoyu", "cao yu" }) );
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "һ����������Ĳ��㡣\n");
		set("unit", "��");
	}

	setup();
}
