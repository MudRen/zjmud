// literateb4.c ����
#include <ansi.h>
inherit ITEM;
void create()
{
	set_name(YEL"����"NOR, ({ "literateb4", "shu4", "book4"}));
	set_weight(300);
	if( clonep() )
	    set_default_object(__FILE__);
	else {
	    set("unit", "��");
	    set("long","һ���׷��ӵġ������\n");
	    set("value", 400);
	    set("no_put", 1);
	    set("material", "paper");
	    set("skill", ([
		"name": "literate",    // name of the skill
		"jing_cost":    55,    // jing cost every time study this
		"difficulty":   35,    // the base int to learn this skill
		"max_skill":   119,    // the maximum level you can learn to
		"min_skill":   100,    // minimun level required
	    ]) );
	}
}
