// lbook1.c
#include <ansi.h>
inherit ITEM;
void create()
{
	set_name(YEL"���־�"NOR, ({ "literateb1", "shu1", "book1" }));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long","�����˱ض������־���\n");
		set("value", 1000);
		set("material", "paper");
		set("skill",
		([
			"name": "literate",      // name of the skill
			"jing_cost":    15,      // jing cost every time study this
			"difficulty":   25,      // the base int to learn this skill
			"max_skill":    29,      // the maximum level you can learn

		]) );
	}
}
