//book.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIB"��"HIY+"�ٱ���ͨ"HIB+"��"NOR, ({"book","shu"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("unit", "��");
		set("value", 1000);
		set("material", "paper");
		set("long",
		"һ������ѧϰ���������顣\n");
		set("value", 100);
		set("skill", ([
			"name" : "pretending",
			"exp_required" : 1000,
			"jing_cost" : 20,
			"difficulty" : 30,
			"max_skill" : 200,
		]));
	}
}
